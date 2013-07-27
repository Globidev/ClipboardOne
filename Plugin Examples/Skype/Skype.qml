import QtQuick 2.0
import GlobiPlugin 1.0
import "Skype.js" as Skype

Plugin 
{
    id : plugin

    name    : 'Skype quotes'
    version : '1.0'
    author  : 'Globinou'
    icon    : Qt.resolvedUrl('Icon.png')

    activable    : true
    configurable : false

    settings : Settings {
        id : conf
        prefix : 'Skype quotes'
    }

    Ui {
        id : ui
        file : Qt.resolvedUrl('Skype.ui')

        function popup(currentText) { // Init fields
            loaded.message.plainText = currentText
            loaded.timeStamp.setDateTime(new Date)
            show()
        }

        /*function saveCurrentAuthorToCache(skypeName, fullName) {
            var skypeNames = conf.value('skype_names', [])
            var fullNames  = conf.value('full_names', [])
            
            if(skypeName.length && !skypeNames.contains(skypeName)) skypeNames.push(skypeName)
            if(fullName.length && !fullNames.contains(fullName))    fullNames.push(fullName)
            
            conf.setValue('skype_names', skypeNames)
            conf.setValue('full_names', fullNames)
        }*/ // Waiting for completers

        Component.onCompleted : {
            ui.mainWindow.windowIcon    = plugin.loadedIcon
            loaded.copyToClipboard.icon = plugin.loadedIcon
            loaded.now.icon             = ImageLoader.loadIcon(Qt.resolvedUrl('Refresh.svg'))

            loaded.copyToClipboard.clicked.connect(function() {
                var author     = loaded.skypeName.text
                var authorName = loaded.fullName.text
                var text       = loaded.message.plainText
                var timeStamp  = Math.floor(loaded.timeStamp.dateTime.getTime() / 1000)

                clipboard.setQuote(author, authorName, text, timeStamp)
                //saveCurrentAuthorToCache(author, authorName) // Waiting for completers
            })
            loaded.now.clicked.connect(function() { loaded.timeStamp.dateTime = new Date })
        }
    }

    clipboard : Clipboard {
        autoTrigger : false

        onActivated : {
            ui.popup(data.text())
        }

        function setQuote(author, authorName, text, timeStamp) {
            var quote = Skype.quote(author, authorName, text, timeStamp)
            setData({
                'text/plain'           : text,
                'SkypeMessageFragment' : quote
            })
        }
    }
}