import QtQuick 2.0
import GlobiPlugin 1.0
import "Dropbox.js" as Dropbox

Plugin {
    id : plugin

    name    : 'Dropbox'
    version : '1.3'
    author  : 'Globinatif'
    icon    : Qt.resolvedUrl('Icon.png')

    onConfigure : {
        configUi.show()

        withToken(getAccountInfo)
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
        }
    }

    Ui {
        id : dateTimeHelper
        file : Qt.resolvedUrl('DateTimeHelper.ui')
    }

    clipboard : Clipboard {
        autoTrigger : false

        onActivated : {
            if(data.hasImage()) {
                var extension = configUi.loaded.fileExtension.currentText
                var image     = data.rawImageData(extension)
                var baseName  = Qt.formatDateTime(new Date, configUi.loaded.filenamePattern.text)
                var fileName  = baseName + '.' + extension

                withToken(function(token) {
                    SystemTray.alert('Uploading image to your Dropbox', 'Plug-in Dropbox : uploading')
                    upload(fileName, image, token)
                })
            } else if(data.hasHtml()) {
                var html      = data.html()
                var baseName  = Qt.formatDateTime(new Date, configUi.loaded.filenamePattern.text)
                var fileName  = baseName + '.html'

                withToken(function(token) {
                    SystemTray.alert('Uploading HTML to your Dropbox', 'Plug-in Dropbox : uploading')
                    upload(fileName, html, token)
                })
            }
        }
    }

    function withToken(func) {
        var accessToken = conf.value('access_token')
        if(accessToken == undefined)
            retrieveCode(func)
        else
            func(accessToken)
    }

    function retrieveCode(callback) {
        var localServer = HTTP.newLocalServer(1337) // TODO : listen check, response timeout
        if(!localServer.isListening()) 
            return onLocalServerError()

        localServer.newQuery.connect(function(query) {
            if('code' in query)
                retrieveToken(query['code'], callback)
            else
                onAccessDenied()
        })

        Qt.openUrlExternally(Dropbox.AUTH_URL)
    }

    function retrieveToken(code, callback) {
        var payload = Dropbox.tokenRequestParameters(code)
        var reply   = HTTP.post(Dropbox.TOKEN_URL, {}, payload)

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                var accessToken = json['access_token']
                conf.setValue('access_token', accessToken)
                callback(accessToken)
            } else {
                onNetworkError(status, json)
            }
        })
    }

    function upload(fileName, data, token) {
        var headers = { 'Authorization' : 'Bearer ' + token } // no url-encoded here
        var reply = HTTP.put(Dropbox.UPLOAD_URL + fileName, 
                             headers, 
                             data)

        reply.finished.connect(function(status) {
            if(status === 200) 
                getLink(fileName, token)
            else
                onNetworkError(status, reply.json())
        })
    }

    function getLink(fileName, token) {
        var withPreview = configUi.loaded.previewUrls.checked
        var payload     = withPreview ? { 'short_url' : configUi.loaded.shortUrls.checked } : {}
        var reply       = HTTP.post(Dropbox.linkUrl(withPreview) + fileName,
                                    Dropbox.OAuthHeaders(token),
                                    payload)

        reply.finished.connect(function(status) {
            var json = reply.json()

            if(status === 200) {
                clipboard.setText(json['url'])
                SystemTray.alert('File successfully uploaded\nLink is ready', 'Plug-in Dropbox : Success')    
            } else {
                onNetworkError(status, json)
            }
        })
    }

    function getAccountInfo(token) {
        var reply = HTTP.get(Dropbox.ACCOUNT_INFO_URL, 
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
        SystemTray.alert(json['error'], 'Plug-in Dropbox : ' + String(status))
    }
}