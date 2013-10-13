import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

RowLayout {
    id : layout

    ListView {
        id : listView
        width : 640
        height : 160

        orientation : ListView.Horizontal

        model : ListModel { 
            id : model
        }

        delegate: Rectangle {
            width : 160
            height : 160

            Image {
                id : img
                source : "data:image/png;base64," + imageData
                property variant imgId : imageId
            }

            MouseArea {
                anchors.fill : parent
                acceptedButtons : Qt.RightButton

                onClicked : contextMenu.show(img.imgId)
            }

            MouseArea {
                anchors.fill : parent
                acceptedButtons : Qt.LeftButton

                onDoubleClicked : withToken(function(token) {
                    getImage(token, img.imgId, imageViewer.load)
                })
            }
        }
    }

    Menu {
        id : contextMenu
        property string currentImageId

        MenuItem {
            id : deleteItem

            text : 'Delete'
            onTriggered : withToken(function(token) {
                removeImage(contextMenu.currentImageId)
                deleteImage(token, contextMenu.currentImageId)
            })
        }

        MenuItem {
            id : pathToClipboardItem

            text : 'Copy link to clipboard'
            onTriggered : withToken(function(token) {
                imageLink(token, contextMenu.currentImageId, function(link) {
                    clipboard.setText(link)
                    SystemTray.alert('Link is ready', 'Plug-in Imgur : Success')
                })
            })
        }

        function show(imgId) {
            currentImageId = imgId
            popup()
        }
    }

    function addImage(imgData) {
        model.append(imgData)
    }

    function removeImage(id) {
        for (var i = 0; i < model.count; ++ i)
        {
            if (model.get(i).imageId === id)
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