import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQuick.Controls 2.2

CheckBox {
    property LineSeries linkedSeries
    onCheckedChanged: {
        linkedSeries.visible = checkState
    }
}
