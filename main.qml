import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import TCPLinkClient 1.0
Window {
    width: 400
    height: 480
    visible: true
    title: qsTr("Client")

    TCPLinkClient{
        id: linkManager
    }

    Rectangle{
        id:  root
        width: parent.width * 0.9
        height: parent.height * 0.9
        anchors.centerIn:  parent
        Row{

            Rectangle{
                height:root.height * 0.9
                width: root.width / 2
                border.color: "black"
                Column{
                    Repeater{
                        model: linkManager.serverMessages
                        delegate:Text{
                            text: modelData
                        }
                    }
                }
            }
            Rectangle{
                id:    cMsg
                height:root.height * 0.9
                width: root.width / 2
                border.color: "black"
                Column{
                    Repeater{
                        model: linkManager.clientMessages
                        delegate: Rectangle{
                            height: msgText.height * 1.2
                            width:  cMsg.width * 0.9
                            border.color: "green"
                            Text{
                                id:  msgText
                                text: modelData
                                width: parent.width
                                wrapMode: Text.wrapMode
                            }
                        }
                    }
                }
            }

        }
        Row{
            anchors.bottom:  parent.bottom
            TextField{
                id:    messageTF
                placeholderText: "Enter Message"
            }
            Button{
                text: "Send"
                onClicked:{
                    linkManager.sendNotification(messageTF.text)
                }
            }
        }
    }
}
