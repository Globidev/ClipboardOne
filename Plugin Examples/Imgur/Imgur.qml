import QtQuick 2.0
import GlobiPlugin 1.0
import "Imgur.js" as Imgur

Plugin {
    id : plugin

    name    : 'Imgur'
    version : '1.6'
    author  : 'Globitch'
    icon    : Qt.resolvedUrl('Icon.png')

    onConfigure : {
        withToken(function(token) {
            getAccountInfo(token)
            getUserStats(token)
        })

        uiConfig.show()
    }

    settings : Settings {
        id     : conf
        prefix : 'Imgur'

        function addFromJson(value, json) { 
            setValue(value, json[value]) 
        }

        function setter(key) { 
            return function(value) { 
                setValue(key, value) 
            } 
        }
    }

    Ui {
        id : uiConfig
        file : Qt.resolvedUrl('Imgur.ui')

        property variant thumbList

        Component.onCompleted : {
            uiConfig.mainWindow.windowIcon = plugin.loadedIcon

            loaded.fileExtension.setCurrentText(conf.value('file_extension', 'png'))
            loaded.fileExtension.currentTextChanged.connect(conf.setter('file_extension'))
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
                var extension = uiConfig.loaded.fileExtension.currentText
                var imageData = Encoding.percentEncode(data.rawImageData(extension))

                withToken(function(token) {
                    SystemTray.alert('Uploading image to Imgur', 'Plug-in Imgur : uploading')
                    upload(imageData, token)
                })
            }
        }
    }

// OAuth 2.0
    function withToken(callback) {
        var accessToken = conf.value('access_token')
        if(accessToken === undefined)
            retrieveCode(callback)
        else {
            var tokenExpires = conf.value('token_expiration_date')
            var userName     = conf.value('account_username')
            if(userName === undefined || new Date > tokenExpires) {
                var refreshToken = conf.value('refresh_token')
                retrieveToken(refreshToken, callback)
            }
            else
                callback(accessToken)
        }
    }

    function retrieveCode(callback) {
        var localServer = HTTP.newLocalServer(Imgur.REDIRECT_PORT) // TODO, response timeout
        if(!localServer.isListening()) 
            return onLocalServerError()

        localServer.newQuery.connect(function(query) {
            if('code' in query)
                retrieveRefreshTokenFromCode(query['code'], callback)
            else
                onAccessDenied()
        })

        Qt.openUrlExternally(Imgur.AUTH_URL)
    }

    function retrieveRefreshTokenFromCode(code, callback) {
        var headers = { 'Content-type' : 'application/x-www-form-urlencoded' }
        var request = Functional.bind(HTTP.post, Imgur.TOKEN_URL, headers, Imgur.CODE_PAYLOAD(code))

        var onTokenRetrieved = function(json) {
            retrieveToken(json['refresh_token'], callback)
        }

        imgurAPICall(request, onTokenRetrieved)
    }

    function retrieveToken(refreshToken, callback) {
        var headers = { 'Content-type' : 'application/x-www-form-urlencoded' }
        var request = Functional.bind(HTTP.post, Imgur.TOKEN_URL, headers, Imgur.REFRESH_PAYLOAD(refreshToken))

        var onTokenRetrieved = function(json) {
            var expirationDate = new Date()
            expirationDate.setSeconds(expirationDate.getSeconds() + json['expires_in'])
            conf.setValue('token_expiration_date', expirationDate)

            conf.addFromJson('account_username', json)
            conf.addFromJson('refresh_token', json)
            conf.addFromJson('access_token', json)
            callback(json['access_token'])
        }

        imgurAPICall(request, onTokenRetrieved)
    }

// API calls
    function upload(data, token) {
        var payload = { 'image' : data }
        var request = Functional.bind(HTTP.post, Imgur.UPLOAD_URL, Imgur.OAUTH_HEADERS(token), payload)

        var onSuccess = function(json) {
            clipboard.setText(json['data']['link'])
            SystemTray.alert('Image successfully uploaded\nLink is ready', 'Plug-in Imgur : Success')
        }

        imgurAPICall(request, onSuccess)
    }

    function getAccountInfo(token) {
        var url     = Imgur.ACCOUNT_INFO_URL(conf.value('account_username'))
        var request = Functional.bind(HTTP.get, url, Imgur.OAUTH_HEADERS(token))

        var onInfoRetrieved = function(json) {
            var data = json['data']
            uiConfig.loaded.userName.text = data['url']
            uiConfig.loaded.userId.text   = data['id']
            uiConfig.loaded.userBio.text  = String(data['bio'])
            uiConfig.loaded.userRep.text  = String(data['reputation'])
            uiConfig.loaded.userAge.text  = Imgur.daysFrom(new Date(data['created'] * 1000)) + ' days'
        }
        
        imgurAPICall(request, onInfoRetrieved)
    }

    function getUserStats(token) {
        var url     = Imgur.ACCOUNT_STATS_URL(conf.value('account_username'))
        var request = Functional.bind(HTTP.get, url, Imgur.OAUTH_HEADERS(token))

        var onStatsRetrieved = function(json) {
            var data = json['data']
            uiConfig.loaded.imageCount.text = String(data['total_images'])
            uiConfig.loaded.albumCount.text = String(data['total_albums'])
            uiConfig.loaded.diskSpace.text  = data['disk_used']
            uiConfig.loaded.bandwidth.text  = data['bandwidth_used']
        }

        imgurAPICall(request, onStatsRetrieved)
    }

    function getImagesIds(token, callback) {
        var url     = Imgur.ACCOUNT_IMAGES_IDS_URL(conf.value('account_username'), 0)
        var request = Functional.bind(HTTP.get, url, Imgur.OAUTH_HEADERS(token))

        var onIdsReceived = function(json) {
            callback(json['data'])
        }

        imgurAPICall(request, onIdsReceived)
    }

    function getImageList(token) {
        getImagesIds(token, function(ids) {
            for(var i = ids.length - 1; i >= 0; -- i)
                fetchThumbnail(token, ids[i])
        })
    }

    function fetchThumbnail(token, id) {
        var request = Functional.bind(HTTP.get, 'http://i.imgur.com/' + id + Imgur.THUMBNAIL_SIZE_SUFFIX + '.jpg')

        var onImageReceived = function(data) {
            uiConfig.thumbList.addImage({
                'imageData' : Encoding.base64(data),
                'imageId'   : id
            })
        }

        imgurAPICall(request, onImageReceived, true)
    }

    function imageLink(token, id, callback) {
        var request = Functional.bind(HTTP.get, Imgur.IMAGE_URL(id), Imgur.OAUTH_HEADERS(token))

        imgurAPICall(request, function(json) {
            callback(json['data']['link'])
        })
    }

    function deleteImage(token, id) {
        var request = Functional.bind(HTTP.del, Imgur.IMAGE_URL(id), Imgur.OAUTH_HEADERS(token))

        imgurAPICall(request, function(json) {
            var message = json['is_deleted'] ? 'Image successfully deleted' : 'Image could not be deleted';
            var title   = json['is_deleted'] ? 'Plug-in Imgur : Success' : 'Plug-in Imgur : Error';
            SystemTray.alert(message, title)
        })
    }

    function getImage(token, id, callback) {
        SystemTray.alert('Fetching file\nPlease wait', 'Plug-in Imgur : Fetching')

        imageLink(token, id, function(link) {
            var request = Functional.bind(HTTP.get, link)
            imgurAPICall(request, callback, true)
        })
    }

// Proxy API network function
    function imgurAPICall(requestFunctor, successFunctor, rawData) {
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
        SystemTray.alert('Could not open a local HTTP server on ' + String(Imgur.REDIRECT_PORT), 'Plug-in Imgur : Network Error')
    }

    function onAccessDenied() {
        SystemTray.alert('Okay :\'(', 'Plug-in Imgur : Access Denied')
    }

    function onNetworkError(status, json) {
        SystemTray.alert(json['data']['error'], 'Plug-in Imgur : Network Error ' + String(status))
    }
}