import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Item {
    id: root
    property alias text: reconnectLabel.text
    Rectangle {
        id: reconnectArea
        color: "#333333"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        z: 10
        height: reconnectLabel.height + 20
        Label {
            id: reconnectLabel
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10
            text: "Connection to server lost, reconnecting..."
        }
    }
}
