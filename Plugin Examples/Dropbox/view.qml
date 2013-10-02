import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

RowLayout {
    id : layout

    ListView {
        id : listView
        width : 512
        height : 128

        orientation : ListView.Horizontal

        model : ListModel { 
            id : model
        }

        delegate: Rectangle {
            width : 128
            height : 128

            Image {
                id : img
                source : "data:image/png;base64," + imageData
                property variant path : imagePath
            }

            MouseArea {
                anchors.fill : parent
                acceptedButtons : Qt.RightButton

                onClicked : contextMenu.show(img.path)
            }

            MouseArea {
                anchors.fill : parent
                acceptedButtons : Qt.LeftButton

                onDoubleClicked : withToken(function(token) {
                    getFile(img.path, token, imageViewer.load)
                })
            }
        }
    }

    Menu {
        id : contextMenu
        property string currentImagePath

        MenuItem {
            id : deleteItem

            text : 'Delete'
            onTriggered : withToken(function(token) {
                removeImage(contextMenu.currentImagePath)
                deleteFile(contextMenu.currentImagePath, token)
            })
        }

        MenuItem {
            id : pathToClipboardItem

            text : 'Copy link to clipboard'
            onTriggered : withToken(function(token) {
                fileLinkToClipboard(contextMenu.currentImagePath, token)
            })
        }

        function show(imgPath) {
            currentImagePath = imgPath
            popup()
        }
    }

    function addImage(imgData) {
        model.append(imgData)
    }

    function removeImage(imgPath) {
        for (var i = 0; i < model.count; ++ i)
        {
            if (model.get(i).imagePath === imgPath)
            {
                model.remove(i)
                break
            }
        }
    }

    function list() { 
        return listView 
    }
}