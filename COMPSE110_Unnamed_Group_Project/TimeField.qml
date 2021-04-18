import QtQuick 2.7
import QtQuick.Controls 2.7

Item {
    property alias timeText : textEditTD.text
    width: 100
    height: 20

    TextField{
                id:textEditTD
                text : "00-00-00"
                inputMask: "99-99-99"
                inputMethodHints: Qt.ImhDigitsOnly
                //validator: RegExpValidator { regExp: /^([0-1]?[0-9]|2[0-3])-([0-5][0-9])-[0-5][0-9]$ / }
                validator: RegExpValidator { regExp: /^([0-1\s]?[0-9\s]|2[0-3\s])-([0-5\s][0-9\s])-([0-5\s][0-9\s])$ / }

                width:100
                height:50
                background:Rectangle{
                    color:"transparent"
                    border.color: "grey"
                    border.width:1
                    //radius:(width * 0.05)
                }
            }



}
