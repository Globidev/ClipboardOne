import QtQuick 2.0
import GlobiPlugin 1.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Dropbox.js" as Dropbox

Plugin {
    id : plugin

    name    : 'Dropbox'
    version : '1.6'
    author  : 'Globinatif'
    icon    : Qt.resolvedUrl('Icon.png')

    onConfigure : {
        withToken(getAccountInfo) // Refresh account infos
        configUi.show()
    }

    settings : Settings {
        id     : conf
        prefix : 'Dropbox'

        function setter(key) { 
            return function(value) { 
                setValue(key, value)
            } 
        }
    }

    Ui {
        id : configUi
        file : Qt.resolvedUrl('DBXConfig.ui')

        property variant thumbList

        Component.onCompleted : { // Init ui state and interactions
            configUi.mainWindow.windowIcon = plugin.loadedIcon 

            loaded.previewUrls.checked = parseInt(conf.value('preview_urls', true))
            loaded.shortUrls.checked   = parseInt(conf.value('short_urls', true))
            loaded.shortUrls.enabled   = loaded.previewUrls.checked

            loaded.fileExtension.currentText = conf.value('file_extension', 'png')
            loaded.filenamePattern.text      = conf.value('filename_pattern', 'yyyy.MM.dd.hh.mm.ss.zzz')

            loaded.shortUrls.stateChanged          .connect(conf.setter('short_urls')      )
            loaded.previewUrls.stateChanged        .connect(conf.setter('preview_urls')    )
            loaded.filenamePattern.textEdited      .connect(conf.setter('filename_pattern'))
            loaded.fileExtension.currentTextChanged.connect(conf.setter('file_extension')  )
            loaded.patternHelp.clicked             .connect(dateTimeHelper.show            )

            loadListView()
        }

        function loadListView() {
            var thumbListComponent = Qt.createComponent(Qt.resolvedUrl('view.qml'), Component.Asynchronous)
            thumbListComponent.statusChanged.connect(function() {
                if(thumbListComponent.status == Component.Ready)
                {
                    thumbList = thumbListComponent.createObject()
                    var thumbListWidget = UiTools.qmlWidget(thumbList.list())
                    UiTools.layWidget(loaded.thumbLayout, thumbListWidget)
                    withToken(getImageList)
                }
                else
                    Logger.error(thumbListComponent.errorString())
            })
        }
    }

    Ui {
        id : dateTimeHelper
        file : Qt.resolvedUrl('DateTimeHelper.ui')

        Component.onCompleted : dateTimeHelper.mainWindow.windowIcon = plugin.loadedIcon 
    }

    Ui {
        id : imageViewer
        file : Qt.resolvedUrl('ImageViewer.ui')

        function load(imgData) {
            loaded.imageLabel.pixmap = ImageLoader.loadPixmapFromData(imgData)
            show()
        }

        Component.onCompleted : imageViewer.mainWindow.windowIcon = plugin.loadedIcon
    }

    clipboard : Clipboard {
        autoTrigger : false

        onActivated : {
            if(data.hasImage()) {
                var extension = configUi.loaded.fileExtension.currentText
                var imageData = data.rawImageData(extension)
                upload(imageData, Dropbox.IMAGE_FOLDER, extension, Dropbox.IMAGE_TYPE)
            } 
            else if(data.hasHtml()) {
                var htmlData = data.html()
                upload(htmlData, Dropbox.HTML_FOLDER, 'html', Dropbox.HTML_TYPE)
            }
        }
    }

// OAuth 2.0 functions
    function withToken(func) {
        var accessToken = conf.value('access_token')
        accessToken == undefined ?
            retrieveCode(func) :
            func(accessToken)
    }

    function retrieveCode(callback) {
        var localServer = HTTP.newLocalServer(Dropbox.REDIRECT_PORT) // TODO : response timeout
        if(!localServer.isListening()) 
            return onLocalServerError()

        localServer.newQuery.connect(function(query) {
            'code' in query ?
                retrieveToken(query['code'], callback) :
                onAccessDenied()
        })

        Qt.openUrlExternally(Dropbox.URL_AUTH)
    }

    function retrieveToken(code, callback) {
        var request = Functional.bind(HTTP.post, Dropbox.URL_TOKEN, {},
                                                 Dropbox.TOKEN_REQUEST_PAYLOAD(code))

        var onTokenReceived = function(json) {
            var accessToken = json['access_token']
            conf.setValue('access_token', accessToken)
            callback(accessToken)
        }

        dropboxAPICall(request, onTokenReceived)
    }

// API calls
    function upload(data, folder, fileExtension, fileType) {
        var baseName = Qt.formatDateTime(new Date, configUi.loaded.filenamePattern.text)
        var fileName = baseName + '.' + fileExtension
        var filePath = folder + '/' + fileName

        withToken(function(token) {
            SystemTray.alert('Uploading ' + fileType + ' to your Dropbox', 'Plug-in Dropbox : uploading')
            uploadImpl(filePath, data, token)
        })
    }

    function uploadImpl(filePath, data, token) {
        var request = Functional.bind(HTTP.put, Dropbox.UPLOAD_URL(filePath), 
                                                Dropbox.OAUTH_HEADERS(token, true), 
                                                data)

        var onUploaded = function() {
            fileLinkToClipboard(filePath, token)
            if(filePath.startsWith('Images'))
                getThumbnailForImage(token, filePath, new Date)
        }

        dropboxAPICall(request, onUploaded)
    }

    function fileLinkToClipboard(filePath, token, upload) {
        var withPreview = configUi.loaded.previewUrls.checked
        var shortUrls   = configUi.loaded.shortUrls.checked
        var request     = Functional.bind(HTTP.post, Dropbox.LINK_URL(withPreview, filePath),
                                                     Dropbox.OAUTH_HEADERS(token),
                                                     Dropbox.LINK_PAYLOAD(withPreview, shortUrls))

        var onLinkReceived = function(json) {
            clipboard.setText(json['url'])
            var text = (upload ? 'File successfully uploaded\n' : '') + 'Link is ready\n' + 'Expires : ' + json['expires']
            SystemTray.alert(text, 'Plug-in Dropbox : Success')
        }

        dropboxAPICall(request, onLinkReceived)
    }

    function getAccountInfo(token) {
        var request = Functional.bind(HTTP.get, Dropbox.URL_ACCOUNT_INFO, 
                                                Dropbox.OAUTH_HEADERS(token))

        var onInfoReceived = function(json) {
            configUi.loaded.userName.text = json['display_name']
            configUi.loaded.userUid.text  = json['uid']

            var bytesInfo = function(value) { 
                return Dropbox.bytesToHumanReadable(json['quota_info'][value]) 
            }
            configUi.loaded.shared.text = bytesInfo('shared')
            configUi.loaded.quota.text  = bytesInfo('quota')
            configUi.loaded.normal.text = bytesInfo('normal')
        }

        dropboxAPICall(request, onInfoReceived)
    }

    function getImageList(token) {
        var request = Functional.bind(HTTP.get, Dropbox.URL_METADATA_IMAGES, 
                                                Dropbox.OAUTH_HEADERS(token))

        var onMetaDataReceived = function(json) {
            var contents = json['contents']
            for(var i = contents.length - 1; i >= 0; -- i) {
                if(contents[i]['mime_type'].startsWith('image')) {
                    getThumbnailForImage(token, contents[i]['path'], contents[i]['modified'])
                }
            }
        }

        dropboxAPICall(request, onMetaDataReceived)
    }

    function getThumbnailForImage(token, path, date) {
        var thumbUrl = HTTP.url(Dropbox.THUMBNAIL_URL(path), Dropbox.THUMBNAIL_PAYLOAD)
        var request  = Functional.bind(HTTP.get, thumbUrl, Dropbox.OAUTH_HEADERS(token))

        var onThumbnailReceived = function(data) {
            configUi.thumbList.addImage({
                'imageData' : Encoding.base64(data),
                'imagePath' : path,
                'imageDate' : new Date(date)
            })
        };

        dropboxAPICall(request, onThumbnailReceived, true)
    }

    function getFile(filePath, token, callback) {
        var request = Functional.bind(HTTP.get, Dropbox.GET_FILE_URL(filePath), 
                                                Dropbox.OAUTH_HEADERS(token))
        SystemTray.alert('Fetching file\nPlease wait', 'Plug-in Dropbox : Fetching')
        dropboxAPICall(request, callback, true)
    }

    function deleteFile(filePath, token) {
        var request = Functional.bind(HTTP.post, Dropbox.URL_DELETE_FILE,
                                                 Dropbox.OAUTH_HEADERS(token),
                                                 Dropbox.DELETE_FILE_PAYLOAD(filePath))

        var onResponse = function(json) {
            var message = json['is_deleted'] ? 'File successfully deleted' : 'File could not be deleted';
            var title   = json['is_deleted'] ? 'Plug-in Dropbox : Success' : 'Plug-in Dropbox : Error';
            SystemTray.alert(message, title)
        }
        
        dropboxAPICall(request, onResponse)
    }

// Proxy API network function
    function dropboxAPICall(requestFunctor, successFunctor, rawData) {
        var reply = requestFunctor()

        reply.finished.connect(function(status) {
            if(status === 200)
                successFunctor(rawData === undefined ? reply.json() : reply.rawData())
            else
                onNetworkError(status, reply.json())
        })
    }

// Error handling
    function onLocalServerError() {
        SystemTray.alert('Could not open a local HTTP server on ' + String(Dropbox.REDIRECT_PORT), 'Plug-in Dropbox : Network Error')
    }

    function onAccessDenied() {
        SystemTray.alert('Okay :\'(', 'Plug-in Dropbox : Access Denied')
    }

    function onNetworkError(status, json) {
        SystemTray.alert(json['error'], 'Plug-in Dropbox : Network Error ' + String(status))
    }
}