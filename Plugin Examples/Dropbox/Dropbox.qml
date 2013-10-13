import QtQuick 2.0
import GlobiPlugin 1.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "Dropbox.js" as Dropbox

Plugin {
    id : plugin

    name    : 'Dropbox'
    version : '1.51'
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
                upload(imageData, 'Images', extension, 'image')
            } else if(data.hasHtml()) {
                var htmlData = data.html()
                upload(htmlData, 'HTML', 'html', 'HTML')
            }
        }
    }

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
        var payload = Dropbox.tokenRequestParameters(code)
        var reply   = HTTP.post(Dropbox.URL_TOKEN, {}, payload)

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                var accessToken = json['access_token']
                conf.setValue('access_token', accessToken)
                callback(accessToken)
            } else
                onNetworkError(status, json)
        })
    }

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
        var headers = { 'Authorization' : 'Bearer ' + token } // no url-encoded here
        var reply = HTTP.put(Dropbox.URL_UPLOAD + filePath, 
                             headers, 
                             data)

        reply.finished.connect(function(status) {
            if(status === 200) {
                fileLinkToClipboard(filePath, token)
                if(filePath.startsWith('Images'))
                    getThumbnailForImage(token, filePath, true)
            } else
                onNetworkError(status, reply.json())
        })
    }

    function fileLinkToClipboard(filePath, token, upload) {
        var withPreview = configUi.loaded.previewUrls.checked
        var payload     = withPreview ? { 'short_url' : configUi.loaded.shortUrls.checked } : {}
        var reply       = HTTP.post(Dropbox.linkUrl(withPreview) + filePath,
                                    Dropbox.OAuthHeaders(token),
                                    payload)

        reply.finished.connect(function(status) {
            var json = reply.json()

            if (status === 200) {
                clipboard.setText(json['url'])
                var text = (upload ? 'File successfully uploaded\n' : '') + 'Link is ready\n' + 'Expires : ' + json['expires']
                SystemTray.alert(text, 'Plug-in Dropbox : Success')
            } else
                onNetworkError(status, json)
        })
    }

    function getAccountInfo(token) {
        var reply = HTTP.get(Dropbox.URL_ACCOUNT_INFO, 
                             Dropbox.OAuthHeaders(token))

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                configUi.loaded.userName.text = json['display_name']
                configUi.loaded.userUid.text  = json['uid']

                var bytesInfo = function(value) { 
                    return Dropbox.bytesToHumanReadable(json['quota_info'][value]) 
                }
                configUi.loaded.shared.text = bytesInfo('shared')
                configUi.loaded.quota.text  = bytesInfo('quota')
                configUi.loaded.normal.text = bytesInfo('normal')
            } else
                onNetworkError(status, json)
        })
    }

    function getImageList(token) {
        var reply = HTTP.get(Dropbox.URL_METADATA_BASE + '/Images', 
                             Dropbox.OAuthHeaders(token))

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                var contents = json['contents']
                for(var i = 0; i < contents.length; ++ i) {
                    if(contents[i]['mime_type'].startsWith('image')) {
                        getThumbnailForImage(token, contents[i]['path'])
                    }
                }
            } else
                onNetworkError(status, json)
        })
    }

    function getThumbnailForImage(token, path) {
        var payload  = { 'size' : 'm' }
        var thumbUrl = HTTP.url(Dropbox.URL_THUMBNAIL_BASE + path, payload)
        var reply    = HTTP.get(thumbUrl, Dropbox.OAuthHeaders(token))

        reply.finished.connect(function(status) {
            if(status === 200) {
                configUi.thumbList.addImage({
                    'imageData' : Encoding.base64(reply.rawData()),
                    'imagePath' : path
                })
            } else
                onNetworkError(status, reply.json())
        })
    }

    function getFile(filePath, token, callback) {
        var reply = HTTP.get(Dropbox.URL_FILE_GET + filePath, Dropbox.OAuthHeaders(token))
        SystemTray.alert('Fetching file\nPlease wait', 'Plug-in Dropbox : Fetching')

        reply.finished.connect(function(status) {
            if(status === 200)
                callback(reply.rawData())
            else
                onNetworkError(status, reply.json())
        })
    }

    function deleteFile(filePath, token) {
        var payload = {
            'root' : 'sandbox',
            'path' : filePath
        }
        var reply    = HTTP.post(Dropbox.URL_DELETE_FILE, 
                                 Dropbox.OAuthHeaders(token), 
                                 payload)
        reply.finished.connect(function(status) {
            if(status === 200)
            {
                if (reply.json()['is_deleted'] === true)
                    SystemTray.alert('File successfully deleted', 'Plug-in Dropbox : Success')
                else
                    SystemTray.alert('File could not be deleted', 'Plug-in Dropbox : Error')
            }
            else
                onNetworkError(status, reply.json())
        })
    }

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