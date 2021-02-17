import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQuick.Controls 2.2

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
            width: 600
            height: 400
            title: qsTr("Weather")
            theme: ChartView.ChartThemeDark
            antialiasing: true

            // List of actual data points in graph
            LineSeries {
                id: weatherSeries
                XYPoint { x: 1; y: 2}
                XYPoint { x: 3; y: 4}
            }
        }

        // Chart for power consumption data
        ChartView {
            id: consumptionGraph
            width: 600
            height: 400
            title: qsTr("Power Consumption")
            theme: ChartView.ChartThemeDark
            antialiasing: true

            // List of actual data points in graph
            LineSeries {
                id: consumptionSeries
            }
        }

        // Chart for separation between power production types
        ChartView {
            id: productionGraph
            width: 600
            height: 400
            title: qsTr("Power production by method")
            theme: ChartView.ChartThemeDark
            antialiasing: true

            // List of actual data points in graph
            LineSeries {
                id: productionSeries
            }
        }
    }
    // Row for graph settings controllers
    Row {
        id: controlRow

        Button {
            font.pointSize: 20
            text: "Click To Fetch Data From FMI"
            anchors.top: parent.bottom

            onClicked: {
                downloader.load("http://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place=Pirkkala&timestep=30&parameters=t2m,ws_10min,n_man");
                }
        }
    }
}
