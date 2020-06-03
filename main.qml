import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import downloader 1.0

ApplicationWindow {
    visible: true
    width: 480
    height: 720
    title: qsTr("Hello World")

property string st
property real a: 0

    DLoader{
        id: dl
    }
    Timer{
        id: timer
        interval: 1000
        repeat: false
        running: false
        onTriggered: {
            txt.text = dl.getResponse()
            initList()
            timer.stop()
        }
    }

    Rectangle{
        id: mrect
        anchors.fill: parent
        color: "black"
        TextArea{
            id: txt
            height: parent.height/4
            width: parent.width
            anchors.top: parent.top
            color: "cyan"
            wrapMode: Text.WordWrap
            background: Rectangle{
                anchors.fill: parent
                color: "darkslategrey"
            }
             BusyIndicator{
                 id: busy
                 width: parent.width/7
                 height: width
                 anchors.top: parent.top
                 anchors.right: parent.right
                 running: false
                 visible: false
             }
         }
         MouseArea{
            id: mouz
            height: parent.height/4
            width: parent.width
            anchors.top: txt.bottom
            onClicked: {
                busy.visible = true
                busy.running = true
                txt.clear()
                dl.getData()
                timer.start()
            }
        }
         ListView{
             id: list
             height: parent.height/2
             width: parent.width
             anchors.top: mouz.bottom
             spacing: 4
             clip: true
             maximumFlickVelocity: 16000
             boundsBehavior: Flickable.StopAtBounds
             model: ListModel{
                 id: listmod
                 ListElement{
                     nam1: "DEFAULT_NAME1"
                     nam2: "DEFAULT_NAME2"
                     mail: "DEFAULT@MAIL"
                     avtr: "qrc:/default.png"
                 }
                 ListElement{
                     nam1: "DEFAULT_NAME1"
                     nam2: "DEFAULT_NAME2"
                     mail: "DEFAULT@MAIL"
                     avtr: "qrc:/default.png"
                 }
                 ListElement{
                     nam1: "DEFAULT_NAME1"
                     nam2: "DEFAULT_NAME2"
                     mail: "DEFAULT@MAIL"
                     avtr: "qrc:/default.png"
                 }
                 ListElement{
                     nam1: "DEFAULT_NAME1"
                     nam2: "DEFAULT_NAME2"
                     mail: "DEFAULT@MAIL"
                     avtr: "qrc:/default.png"
                 }
                 ListElement{
                     nam1: "DEFAULT_NAME1"
                     nam2: "DEFAULT_NAME2"
                     mail: "DEFAULT@MAIL"
                     avtr: "qrc:/default.png"
                 }
                 ListElement{
                     nam1: "DEFAULT_NAME1"
                     nam2: "DEFAULT_NAME2"
                     mail: "DEFAULT@MAIL"
                     avtr: "qrc:/default.png"
                 }
             }
             delegate: Rectangle{
                 id: listdlg
                 width: list.width
                 height: list.height/6-4
                 color: "#99444444"
                 Rectangle{
                     id: avatar
                     height: parent.height-10
                     width: height
                     anchors.left: parent.left
                     anchors.verticalCenter: parent.verticalCenter
                     anchors.leftMargin: 5
                     color: "transparent"
                     border.color: "black"
                     Image{
                         id: avatar_img
                         anchors.fill: parent
                         source: avtr
                         fillMode: Image.PreserveAspectCrop
                     }
                 }
                 Rectangle{
                     id: txtr1
                     width: parent.width-avatar.width-10
                     height: parent.height/3
                     anchors.top: parent.top
                     anchors.right: parent.right
                     anchors.rightMargin: 5
                     anchors.topMargin: 5
                     color: "transparent"
                     Text{
                         id: txt1
                         anchors.centerIn: parent
                         text: nam1+" "+nam2
                         color: "white"
                     }
                 }
                 Rectangle{
                     id: txtr2
                     width: parent.width-avatar.width-10
                     height: parent.height/3
                     anchors.top: txtr1.bottom
                     anchors.right: parent.right
                     anchors.rightMargin: 5
                     anchors.topMargin: 5
                     color: "transparent"
                     Text{
                         id: txt2
                         anchors.centerIn: parent
                         text: mail
                         color: "white"
                     }
                 }
             }
         }
    }
    function initList(){
        listmod.clear()
        for(var i = 0; i < dl.getCount(); i++){
            listmod.append({"avtr": dl.getAvatar(i), "nam1": dl.getName1(i), "nam2": dl.getName2(i), "mail": dl.getMail(i)})
        }
        busy.running = false
        busy.visible = false
    }
}
