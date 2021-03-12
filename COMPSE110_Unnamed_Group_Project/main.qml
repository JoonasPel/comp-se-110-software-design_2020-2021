import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQuick.Controls 2.2

Window {
    id: mainWindow
    objectName: "mainWindow"
    width: 640*2.5 // 1280
    height: 480*2 // 960
    visible: true
    title: qsTr("Weathercast")

    // Sizing constraints for graphs
    property int chartWidth: mainWindow.width / 3
    property int chartHeight: mainWindow.height / 2

    property int day_hours: 24
    property int week_hours: 24*7
    property int graph_scale_h: day_hours
    property int graph_scale_v: 30

    Row {
        id: graphRow
        objectName: "graphRow"
        anchors.top: parent.top

        // Chart for weather data
        ChartElement {
            id: weatherGraph
            typeName: "weather"
            objectName: "weatherGraph"
        }

        // Chart for power consumption data
        ChartElement {
            id: consumptionGraph
            typeName: "consumption"
            objectName: "consumptionGraph"
        }

        // Chart for separation between power production types
        ChartElement {
            id: productionGraph
            typeName: "production"
            objectName: "productionGraph"

        }

    }
    ControlRow {
        id: controlRow
    }
}
