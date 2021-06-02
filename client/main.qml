import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Simple Chat, SSL & Qt 6")

    NicArea {
        id:nicArea
        anchors.fill:parent;
        z: 1
        onStartChat: root.startChat()
    }

    Rectangle {
        id: messagesArea
        color: "#222222"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: inputArea.top

        SearchArea {
            id: searchArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            onSearch: root.search()
        }

        ListModel {
            id: messageModel
        }

        ListView {
            id: messageList
            anchors.top: searchArea.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.topMargin: 10
            model: messageModel
            highlightFollowsCurrentItem: true
            ScrollBar.vertical: ScrollBar {
                    width: 10
                    policy: ScrollBar.AlwaysOn
                }
            delegate: MessageListDelegate {
                nic: model.nic + " : "
                msg: model.msg
            }
        }
    }

    ReconnectArea {
        id: reconnectArea
        visible: false
        anchors.bottom: inputArea.top
        anchors.left: parent.left
        anchors.right: parent.right
        text:  "Connection to server lost, reconnecting..."
    }

    MessageInput {
        id: inputArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 40
        onSend: root.send()
    }

    function startChat() {
        console.log("start chat");
        chat.connectToChat(nicArea.text);
    }

    function send() {
        console.log("Send func");
        chat.send(inputArea.text);
        inputArea.text = "";
    }

    function search() {
        let what = searchArea.text
        console.log('search:' + what);
        for(let i=messageList.count-1; i>=0; i--) { // search from last message
            let message = messageModel.get(i);
            if( substringOf(message.nic, what)
                    || substringOf(message.msg, what)
                    ) {
                messageList.currentIndex = i
                return
            }
        }
    }

    function substringOf(where, what) {
        return where.indexOf(what) !== -1
    }

    Connections {
        target: chat
        function onMessageReceived(msgSender, msg) {
            messageModel.append( {
                                    nic: msgSender,
                                    msg: msg
                                } );
            console.log("Items count:" + messageList.count);
            if(messageList.count > 1) {
                messageList.currentIndex = messageList.count - 1
                }
        }

        function onConnected() {
            console.log("connected");
            nicArea.visible = false;
            inputArea.inputFocus = true;
            reconnectArea.visible = false;
        }
        function onNicError(msg) {
            console.log(msg)
            nicArea.errorVisible = true
            nicArea.errorText = msg
        }
        function onReconnecting() {
            reconnectArea.visible = true;
            if(nicArea.visible) {
                reconnectArea.text = "Connection to server failed, trying again.."
                return
            }
            reconnectArea.text = "Connection lost, reconnecting.."
        }
    }
}
