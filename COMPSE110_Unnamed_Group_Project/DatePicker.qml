import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    width: 100
    height: 50
    property alias buttonText: button.text
    property alias text: textDate.text
    TextField {
        id: textDate
        width: 100
        height: 40
        //placeholderText: qsTr("Text Field")
        text:Qt.formatDate(cal.selectedDate, "yyyy-MM-dd")
        font.family:"times new roman"
        font.pointSize: 14
    }

    Button {
        id: button
        anchors.bottom: textDate.top
        text: qsTr("placeHolder")
        width: 100
        height: 29

        onClicked:{
            cal.visible=true
        }
    }
    Calendar{
               id:cal
               x: -300
               y: -400
               width: 340
               height: 310
               visible: false
               selectedDate: new Date()
               onClicked:  {
                   cal.visible=false
                   textDate.text=Qt.formatDate(cal.selectedDate, "yyyy-MM-dd");

               }
    }
}
