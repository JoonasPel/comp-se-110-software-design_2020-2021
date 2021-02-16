import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3

Window {
    width: 640*2
    height: 480*2
    visible: true
    title: qsTr("Weathercast")

    Row {
        anchors.top: parent.top

        // Chart for weather data
        ChartView {
            id: weatherGraph

            // List of actual data points in graph
            //LineSeries: {}
        }

        // Chart for power consumption data
        ChartView {
            id: consumptionGraph

            // List of actual data points in graph
            //LineSeries: {}
        }

        // Chart for separation between power production types
        ChartView {
            id: productionGraph

            // List of actual data points in graph
            //LineSeries: {}
        }
    }
}
