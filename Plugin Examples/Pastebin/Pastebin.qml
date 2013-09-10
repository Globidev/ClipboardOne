import QtQuick 2.0
import GlobiPlugin 1.0
import "Pastebin.js" as Pastebin

Plugin {
    name    : 'Pastebin'
    version : '0.42'
    author  : 'Globinary'
    icon    : Qt.resolvedUrl('Icon.png')

    clipboard : Clipboard {
        autoTrigger : false

        onActivated : {
            if(data.hasText()) {
                uploadText(data.text())
            }
        }
    }

    function uploadText(text) {
        var payload = Pastebin.pastePayload(text)
        var headers = {'Content-type' : 'application/x-www-form-urlencoded;charset=utf-8' }
        var reply = HTTP.post(Pastebin.API_URL, headers, payload)

        reply.finished.connect(function(status) {
            if(status === 200) {
                clipboard.setText(reply.rawData())
            } else
                SystemTray.alert('Unknown Error', 'Plug-in Pastebin : Network Error ' + String(status))
        })
    }
}