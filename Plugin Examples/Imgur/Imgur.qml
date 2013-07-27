import QtQuick 2.0
import GlobiPlugin 1.0
import "Imgur.js" as Imgur

Plugin {
    id : plugin

    name    : 'Imgur'
    version : '1.2'
    author  : 'Globitch'
    icon    : Qt.resolvedUrl('Icon.png')

    onConfigure : {
        uiConfig.show()

        withToken(getAccountInfo)
        withToken(getUserStats)
    }

    settings : Settings {
        id     : conf
        prefix : 'Imgur'

        function addFromJson(value, json) { setValue(value, json[value]) }
        function setter(key) { return function(value) { setValue(key, value) } }
    }

    Ui {
        id : uiConfig
        file : Qt.resolvedUrl('Imgur.ui')

        Component.onCompleted : {
            uiConfig.mainWindow.windowIcon = plugin.loadedIcon

            loaded.fileExtension.setCurrentText(conf.value('file_extension', 'png'))
            loaded.fileExtension.currentTextChanged.connect(conf.setter('file_extension'))
        }
    }

    clipboard : Clipboard {
        autoTrigger : false

        onActivated : {
            if(data.hasImage()) {
                var extension = uiConfig.loaded.fileExtension.currentText
                var image     = data.percentEncodedData(extension)

                withToken(function(token) {
                    SystemTray.alert('Uploading image to Imgur', 'Plug-in Imgur : uploading')
                    upload(image, token)
                })
            }
        }
    }

    function withToken(callback) { // TODO : Maybe add a timer to be able to use the access token until it expires and not refresh it every time
        var refreshToken = conf.value('refresh_token')
        if(refreshToken == undefined)
            retrieveCode(callback)
        else
            retrieveToken(Imgur.refreshPayload(refreshToken), callback)
    }

    function retrieveCode(callback) {
        var localServer = HTTP.newLocalServer(1337)
        if(!localServer.isListening()) 
            return onLocalServerError()

        localServer.newQuery.connect(function(query) {
            if('code' in query) {
                var payload = Imgur.codePayload(query['code'])
                retrieveToken(payload, callback)
            } else {
                onAccessDenied()
            }
        })

        Qt.openUrlExternally(Imgur.AUTH_URL)
    }

    function retrieveToken(payload, callback) {
        var headers = { 'Content-type' : 'application/x-www-form-urlencoded' }
        var reply   = HTTP.post(Imgur.TOKEN_URL, headers, payload)

        reply.finished.connect(function(status) {
            var json = reply.json()
            if(status === 200) {
                conf.addFromJson('account_username', json)
                conf.addFromJson('refresh_token',    json)
                callback(json['access_token'])
            } else {
                onNetworkError(status, json)
            }
        })
    }

    function upload(data, token) {
        var payload = { 'image' : data }
        var reply   = HTTP.post(Imgur.UPLOAD_URL, 
                                Imgur.OAuthHeaders(token), 
                                payload)

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                clipboard.setText(json['data']['link'])
                SystemTray.alert('Image successfully uploaded\nLink is ready', 'Plug-in Imgur : Success')
            } else {
                onNetworkError(status, json)
            }
        })
    }

    function getAccountInfo(token) {
        var url   = Imgur.accountInfoUrl(conf.value('account_username'))
        var reply = HTTP.get(url, Imgur.OAuthHeaders(token))

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                var data = json['data']

                uiConfig.loaded.userName.text = data['url']
                uiConfig.loaded.userId.text   = data['id']
                uiConfig.loaded.userBio.text  = String(data['bio'])
                uiConfig.loaded.userRep.text  = String(data['reputation'])
                uiConfig.loaded.userAge.text  = Imgur.daysFrom(new Date(data['created'] * 1000))
            } else {
                onNetworkError(status, json)
            }
        })
    }

    function getUserStats(token) {
        var url   = Imgur.accountStatsUrl(conf.value('account_username'))
        var reply = HTTP.get(url, Imgur.OAuthHeaders(token))

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                var data = json['data']

                uiConfig.loaded.imageCount.text = String(data['total_images'])
                uiConfig.loaded.albumCount.text = String(data['total_albums'])
                uiConfig.loaded.diskSpace.text  = data['disk_used']
                uiConfig.loaded.bandwidth.text  = data['bandwidth_used']
            } else {
                onNetworkError(status, json)
            }
        })
    }

    function onLocalServerError() {

    }

    function onAccessDenied() {

    }

    function onNetworkError(status, json) {
        SystemTray.alert(json['data']['error'], 'Plug-in Imgur : ' + String(status))
    }
}