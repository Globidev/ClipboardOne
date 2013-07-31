ClipboardOne
============

Customize your clipboard thanks to an advanced plug-in system

### Build Instructions

You will need the following libraries :

* Qt 5.1.0 or higher
* Boost

As this project uses [Redis](http://redis.io/), it is also required to have the redis-server executable and a client library installed. The one used here is [hiredis](https://github.com/redis/hiredis) (see [hiredis win32](https://github.com/texnician/hiredis-win32) for Windows)

### Developing Plug-ins

Plugins are written in [QML](http://qt-project.org/doc/qt-4.8/gettingstartedqml.html), the markup language of Qt which is based on JavaScript.

They can be imported in the application with an url. This url can either be a local path to a file or a web url.

#### Hello World

Here is an example of a minimal plug-in : 

    import QtQuick 2.0
    import GlobiPlugin 1.0

    Plugin {
        name    : 'Hello world'
        version : '1.42.1337'
        author  : 'A handsome nerd'
        icon    : Qt.resolvedUrl('Icon.png')
    }

After adding it to the application, it will be visible in the plug-in table like so :

![plugin table](https://dl.dropboxusercontent.com/u/3427186/ClipboardOne_plugin_table.png)

Our plug-in is not really useful at this stage. Let us make it react to clipboard events.  
The plugin component has a `clipboard` property which can be customized :

    Plugin {
        ...
        clipboard : Clipboard {
            // Shortcut is not needed to react to clipboard events
            autoTrigger : true 
    
            onActivated : {
                if(data.hasText())
                    SystemTray.alert(data.text(), 'text copied')
            }
        }
    }

With this snippet, the plugin will make the system tray icon display a popup with the clipboard's current text (if any) every time its content changes.
