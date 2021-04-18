import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    width: 210
    height: 40
    //property alias startDateText : textStartDate.text
    //property alias endDateText : textEndDate.text
    property alias startDate: startCal.selectedDate
    property alias endDate: endCal.selectedDate
    property alias startClock: startTimeField.text
    property alias endClock: endTimeField.text

    TextField {
        id: textStartDate
        width: 100
        height: 40
        text:Qt.formatDate(startCal.selectedDate, "yyyy-MM-dd")
        font.family:"times new roman"
        font.pointSize: 14
        readOnly: true

        MouseArea {
            anchors.fill: parent
            onClicked:{
                startCal.visible=true
            }
        }
    }

    Button {
        id: leftButton
        anchors.bottom: textStartDate.top
        text: qsTr("Start Date")
        width: 100
        height: 29

        onClicked:{
            startCal.visible=true
        }
    }
    Calendar{
               id:startCal
               x: -200
               y: -400
               width: 340
               height: 310
               visible: false
               selectedDate: new Date()
               minimumDate: "1900-01-01"
               maximumDate: endCal.selectedDate

               onClicked: {
                   startCal.visible=false
                   textStartDate.text=Qt.formatDate(startCal.selectedDate, "dd-MM-yyyy")
                   controller.setParameter("starttime", Qt.formatDate
                                           (startCal.selectedDate, "yyyy-MM-dd")+"T"+startTimeField.timeText+"Z");
               }

               onSelectedDateChanged:  {

                   textStartDate.text=Qt.formatDate(startCal.selectedDate, "dd-MM-yyyy")
                   controller.setParameter("starttime", Qt.formatDate
                                           (startCal.selectedDate, "yyyy-MM-dd")+"T"+startTimeField.timeText+"Z");

               }
               // Add initial value to parameters_ in model
               Component.onCompleted: {
                   controller.setParameter("starttime", Qt.formatDate
                                           (startCal.selectedDate, "yyyy-MM-dd")+"T"+startTimeField.timeText+"Z");
               }
    }

    TimeField{
        id: startTimeField
        anchors.top: textStartDate.bottom
        onTimeTextChanged: {
            controller.setParameter("starttime", Qt.formatDate
                                    (startCal.selectedDate, "yyyy-MM-dd")+"T"+startTimeField.timeText+"Z");
        }
    }

    TextField {
        id: textEndDate
        width: 100
        height: 40
        anchors.left: textStartDate.right
        text:Qt.formatDate(endCal.selectedDate, "yyyy-MM-dd")
        font.family:"times new roman"
        font.pointSize: 14
        readOnly: true

        MouseArea {
            anchors.fill: parent
            onClicked:{
                endCal.visible=true
            }
        }
    }

    Button {
        id: rightButton
        anchors.bottom: textEndDate.top
        anchors.left: leftButton.right
        text: qsTr("End Date")
        width: 100
        height: 29

        onClicked:{
            endCal.visible=true
        }
    }
    Calendar{
               id:endCal
               x: 140
               y: -400
               width: 340
               height: 310
               visible: false
               selectedDate: new Date()
               minimumDate: startCal.selectedDate
               maximumDate: new Date().toLocaleString(Qt.locale("fi_FI"), "yyyy-MM-dd")

               onClicked: {
                   endCal.visible=false
                   textEndDate.text=Qt.formatDate(endCal.selectedDate, "dd-MM-yyyy")
                   controller.setParameter("endtime", Qt.formatDate
                                           (endCal.selectedDate, "yyyy-MM-dd")+"T"+endTimeField.timeText+"Z")
               }

               onSelectedDateChanged:  {
                   textEndDate.text=Qt.formatDate(endCal.selectedDate, "dd-MM-yyyy")
                   controller.setParameter("endtime", Qt.formatDate
                                           (endCal.selectedDate, "yyyy-MM-dd")+"T"+endTimeField.timeText+"Z");

               }
               // Add initial value to parameters_ in model
               Component.onCompleted: {
                   controller.setParameter("endtime", Qt.formatDate
                                           (endCal.selectedDate, "yyyy-MM-dd")+"T"+endTimeField.timeText+"Z");
               }
    }

    TimeField{
        id: endTimeField
        anchors.left: startTimeField.right
        anchors.top: textEndDate.bottom
        onTimeTextChanged: {
            controller.setParameter("endtime", Qt.formatDate
                                    (endCal.selectedDate, "yyyy-MM-dd")+"T"+endTimeField.timeText+"Z");
        }
    }
}
