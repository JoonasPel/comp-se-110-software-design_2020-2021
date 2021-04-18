import QtQuick 2.7
import QtQuick.Controls 2.7

Item {
    property alias timeText : textEditTD.displayText
    property alias text : textEditTD.text
    width: 100
    height: 20

    TextField{
                id:textEditTD
                text : "00:00:00"
                inputMask: "99:99:99;0"
                inputMethodHints: Qt.ImhDigitsOnly
                //validator: RegExpValidator { regExp: /^([0-1]?[0-9]|2[0-3])-([0-5][0-9])-[0-5][0-9]$ / }
                //validator: RegExpValidator { regExp: /(?:[01]\d|2[0123]):(?:[012345]\d):(?:[012345]\d) / }

                validator: RegExpValidator { regExp: /^(?:(?:([01]?\d|2[0-3]):)?([0-5]?\d):)?([0-5]?\d)$/ }

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
