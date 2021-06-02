import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Rectangle {
    property alias nic: listViewNic.text
    property alias msg: listViewMsg.text

    color: "#222222"
    height: listViewRect.height + 20
    width: messageList.width * 2/3
    Rectangle {
        id: listViewRect
        color: "#333333"
        radius: 5
        x: 10
        height: listViewNic.height + 30 + listViewMsg.height
        width: messageList.width * 2/3
        Label {
            id: listViewNic
            anchors.top: listViewRect.top
            anchors.left: listViewRect.left
            anchors.margins: 10
            text: model.nic + " : "
        }
        Label {
            id: listViewMsg
            anchors.top: listViewNic.bottom
            anchors.left: listViewRect.left
            anchors.margins: 10
            text: model.msg
        }
    }
}
