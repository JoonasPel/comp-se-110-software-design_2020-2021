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
        ChartView {
            id: weatherGraph
            objectName: "weatherGraph"
            width: chartWidth
            height: chartHeight
            title: qsTr("Weather")
            theme: ChartView.ChartThemeDark
            antialiasing: true

            // List of actual data points in graph
            LineSeries {
                id: weatherSeries
                objectName: "weatherSeries"
                axisX: ValueAxis {
                    min: 0
                    max: graph_scale_h
                }
                axisY: ValueAxis {
                    min: -30
                    max: graph_scale_v
                }
            }
            onSeriesAdded: {
                console.log("points changed");
                setAxisX(weatherSeries.axisX);
                setAxisY(weatherSeries.axisY);

            }
        }

        // Chart for power consumption data
        ChartView {
            id: consumptionGraph
            objectName: "consumptionGraph"
            width: chartWidth
            height: chartHeight
            title: qsTr("Power Consumption")
            theme: ChartView.ChartThemeDark
            antialiasing: true


            // List of actual data points in graph
            LineSeries {
                id: consumptionSeries
                objectName: "consumptionSeries"
                axisX: ValueAxis {
                    min: 0
                    max: graph_scale_h
                }
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }

            onSeriesAdded: {
                setAxisX(consumptionSeries.axisX);
                setAxisY(consumptionSeries.axisY);
            }
        }

        // Chart for separation between power production types
        ChartView {
            id: productionGraph
            objectName: "productionGraph"
            width: chartWidth
            height: chartHeight
            title: qsTr("Power production by method")
            theme: ChartView.ChartThemeDark
            antialiasing: true

            // List of actual data points in graph
            LineSeries {
                id: productionSeries
                objectName: "productionSeries"
                axisX: ValueAxis {
                    min: 0
                    max: graph_scale_h
                }
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }

            onSeriesAdded: {
                setAxisX(productionSeries.axisX);
                setAxisY(productionSeries.axisY);
            }
        }
    }
    // Row for graph settings controllers
    Row {
        id: controlRow
        objectName: "controlRow"
        anchors.top: graphRow.bottom

        Button {
            font.pointSize: 20
            text: "Click To Fetch Data From FMI"
            anchors.top: parent.bottom

            onClicked: {
                controller.fetchData("http://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place=Pirkkala&starttime=2021-02-14T09:00:00Z&endtime=2021-02-21T09:00:00Z&timestep=60&parameters=t2m,ws_10min,n_man", placeSelector.currentText);
                }
        }
        Button {
            font.pointSize: 20
            text: "Test Render Charts"
            anchors.top: parent.bottom

            onClicked: {
                controller.renderData(weatherGraph.objectName, weatherSeries.objectName);
                controller.renderData(consumptionGraph.objectName, consumptionSeries.objectName);
                controller.renderData(productionGraph.objectName, productionSeries.objectName);
            }
        }
        Slider {
            from: 0
            to: 1
            anchors.top: parent.bottom
            onValueChanged: {
                if (value < 0.5) { graph_scale_h = day_hours }
                else { graph_scale_h = week_hours }
            }
        }
        ComboBox {
            id: placeSelector
            anchors.top: parent.bottom
            width: 200
            model: [ "Tampere", "Rovaniemi", "Helsinki" ]
        }
    }
}
