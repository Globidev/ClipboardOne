import QtQuick 2.0
import GlobiPlugin 1.0
import "Youtube.js" as Youtube

Plugin {
    id : plugin

    name    : 'Youtube'
    version : '1.3'
    author  : 'Globinette'
    icon    : Qt.resolvedUrl('Icon.png')

    activable : false

    function setActivable(isActivable) {
        activable = isActivable
        conf.setValue('activable', isActivable)
    }

    settings : Settings {
        id : conf
        prefix : 'Youtube'

        function setter(key) { return function(value) { setValue(key, value) }; }
    }

    uis : [
        Ui {
            id : configUi
            file : Qt.resolvedUrl('YoutubeConfig.ui')

            Component.onCompleted : {
                mainWindow.windowIcon = ImageLoader.loadIcon(Qt.resolvedUrl('Youtube_icon.svg'))

                loaded.activable.checked     = conf.value('activable', 'false').toBool()
                loaded.openInBrowser.checked = conf.value('open_in_browser', 'true').toBool()
                loaded.openInPlayer.checked  = conf.value('open_in_player', 'false').toBool()
                loaded.mediaPlayer.text      = conf.value('media_player_path', '')

                loaded.activable.toggled.connect(setActivable)
                setActivable(loaded.activable.checked)
                loaded.openInBrowser.toggled.connect(conf.setter('open_in_browser'))
                loaded.openInPlayer.toggled.connect(conf.setter('open_in_player'))
                loaded.mediaPlayer.textChanged.connect(conf.setter('media_player_path'))
            }
        }
    ]

    onConfigure : {
        configUi.show()
    }

    clipboard : Clipboard {
        autoTrigger : true

        onActivated : {
            if(data.hasText()) {
                var text = data.text()

                if(Youtube.isVideo(text)) {
                    if(autoTriggered)
                        setShortlinkToClipboard(text)
                    else
                        actOnLink(text)
                }
            }
        }
    }

    function setShortlinkToClipboard(youtubeUrl) {
        var doShorten = function() {
            var shortLink = Youtube.shortenLink(youtubeUrl)
            clipboard.setText(shortLink)
        };
        if(Youtube.isPlayList(youtubeUrl))
            SystemTray.alert('The link was not shorten because it refers to a playlist\nClick to shorten it anyway', 
                             'Plug-in Youtube : playlist', doShorten)
        else
            doShorten()
    }

    function actOnLink(youtubeUrl) {
        if(configUi.loaded.openInBrowser.checked)
            Qt.openUrlExternally(youtubeUrl)
        else
            playInMediaPlayer(youtubeUrl)
    }

    function playInMediaPlayer(url) {
        var vlcPath = conf.value('media_player_path')
        if(vlcPath != undefined) 
            Process.startDetached(vlcPath, ['--one-instance', '--playlist-enqueue', url])
    }
}