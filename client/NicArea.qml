import QtQuick 2.6
import QtQuick.Controls 2.12

Item {
    id: root
    property alias errorVisible: nicErrorArea.visible
    property alias errorText: nicError.text
    property alias text: nicInput.text
    signal startChat();


    Rectangle {
        color: "#222222"
        anchors.fill:parent


        Label {
            id: nicLabel
            text: qsTr("Nicname")
            color: "#EEEEEE"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
        }

        TextField {
            id: nicInput
            focus: true
            placeholderText: qsTr("Nicname")
            anchors.top: nicLabel.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            padding: 10
            onAccepted: root.startChat()
        }

        Button {
            id: nicButton
            text: qsTr("Start Chat")
            anchors.top: nicInput.bottom
            anchors.right: parent.right
            anchors.margins: 10
            padding: 10
            onClicked: root.startChat()
        }

        Rectangle {
            id: nicErrorArea
            color: "red"
            visible: false
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: nicError.height + 20

            Label {
                id: nicError
                color: "#FFFFFF"
                text: "hhhmmm..."
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 10
            }
        }
    }
}
