import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Item {
    id: root
    property alias text: messageInput.text
    property alias inputFocus: messageInput.focus
    signal send

    Rectangle {
        id: inputArea
        color: "#333333";
        anchors.fill: parent

        TextField {
            id: messageInput
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: sendButton.left
            anchors.rightMargin: 4
            placeholderText: qsTr("Message text")
            text: ""
            font.pixelSize: 12
            padding: 10
            onAccepted: root.send()
        }

        Button {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 4
            padding: 10
            id: sendButton
            text: qsTr("Send")
            onClicked: root.send()
        }
    }
}
