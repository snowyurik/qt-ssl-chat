import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Rectangle {
    id: root
    property alias text: searchInput.text
    signal search;

    color: "#333333"
//    anchors.top: parent.top
//    anchors.left: parent.left
//    anchors.right: parent.right
    height: searchInput.height + 20
    z: 100
    TextField {
        id: searchInput
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        color: "#FFFFFF"
        placeholderText: "Search messages"
        onAccepted: root.search()
    }
}
