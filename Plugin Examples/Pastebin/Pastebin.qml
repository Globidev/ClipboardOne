import QtQuick 2.0
import GlobiPlugin 1.0
import "Pastebin.js" as Pastebin

Plugin {
    id      : plugin
    name    : 'Pastebin'
    version : '1.0'
    author  : 'Globinary'
    icon    : Qt.resolvedUrl('Icon.png')

    configurable : false

    Ui {
        id : highlightUi
        file : Qt.resolvedUrl('syntax.ui')
        property variant currentText

        function popup(text) {
            currentText = text
            show()
        }

        Component.onCompleted : {
            highlightUi.mainWindow.windowIcon = plugin.loadedIcon

            loaded.upload.clicked.connect(function() { 
                uploadText(currentText, loaded.syntax.currentText)
                highlightUi.mainWindow.close()
            })
        }
    }

    clipboard : Clipboard {
        autoTrigger : false

        onActivated : {
            if(data.hasText()) {
                highlightUi.popup(data.text())
            }
        }
    }

    function uploadText(text, syntax) {
        var payload = Pastebin.pastePayload(text, syntax)
        var headers = {'Content-type' : 'application/x-www-form-urlencoded;charset=utf-8' }
        SystemTray.alert('Your paste is being uploaded', 'Plug-in Pastebin : uploading')
        var reply = HTTP.post(Pastebin.API_URL, headers, payload)

        reply.finished.connect(function(status) {
            if(status === 200) {
                clipboard.setText(reply.rawData())
                SystemTray.alert('Paste successfully uploaded\nLink is ready', 'Plug-in Pastebin : Success') 
            }
            else
                SystemTray.alert(reply.rawData(), 'Plug-in Pastebin : Network Error ' + String(status))
        })
    }
}