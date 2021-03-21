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
            objectName: "weatherGraph"
            title: "Weather"

            // Temperature
            LineSeries {
                id: temperature;
                objectName: "temperature"
                axisX: ValueAxis {
                    min: 0
                    max: graph_scale_h
                }
                axisY: ValueAxis {
                    min: -30
                    max: graph_scale_v
                }
            }

            // Windspeed
            LineSeries {
                id: windSpeed;
                objectName: "windSpeed"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }
        }

        // Chart for power consumption data
        ChartElement {
            id: consumptionGraph
            objectName: "consumptionGraph"
            title: "Power consumption"

            // General consumption
            LineSeries {
                id: totalConsumption;
                objectName: "totalConsumption"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }
        }

        // Chart for separation between power production types
        ChartElement {
            id: productionGraph
            objectName: "productionGraph"
            title: "Power production"

            // General production
            LineSeries {
                id: totalProduction;
                objectName: "totalProduction"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }
            LineSeries {
                id: nuclearProduction;
                objectName: "nuclearProduction"
            }
            LineSeries {
                id: windProduction;
                objectName: "windProduction"
            }
            LineSeries {
                id: waterProduction;
                objectName: "waterProduction"
            }
            StackedBarSeries {
                property var waterAmo: []
                property var windAmo: []
                property var nuclAmo: []
                id: productionPercentages
                objectName: "productionPercentages"
                BarSet { id: waterBar; label: "Water"; values: productionPercentages.waterAmo}
                BarSet { id: windBar; label: "Wind"; values: productionPercentages.windAmo}
                BarSet { id: nuclBar; label: "Nuclear"; values: productionPercentages.nuclAmo}
            }
        }
    }
    Row {
        id: graphSelectors
        objectName: "graphSelectors"
        anchors.top: graphRow.bottom

        /* ============================
         * Left graph: Weather elements
         */
        GraphCheckBox {
            id: temperatureBox
            text: qsTr("Temperature")
            checked: true
            linkedSeries: temperature
        }
        GraphCheckBox {
            id: windBox
            text: qsTr("Wind speed")
            checked: false
            linkedSeries: windSpeed
        }

        /* ================================
         * Middle graph: Consumption values
         */
        GraphCheckBox {
            id: consumptionBox
            text: qsTr("Total Consumption")
            checked: true
            linkedSeries: totalConsumption
        }

        /* ==============================
         * Right graph: Production values
         */
        GraphCheckBox {
            id: productionBox
            text: qsTr("Total Production")
            checked: true
            linkedSeries: totalProduction
        }
        GraphCheckBox {
            id: productionNuclearBox
            text: qsTr("Nuclear Power")
            checked: false
            linkedSeries: nuclearProduction
        }
        GraphCheckBox {
            id: productionWaterBox
            text: qsTr("Water Power")
            checked: false
            linkedSeries: waterProduction
        }
        GraphCheckBox {
            id: productionWindBox
            text: qsTr("Wind Power")
            checked: false
            linkedSeries: windProduction
        }
        GraphCheckBox {
            id: productionPercentagesBox
            text: qsTr("Production Percentages")
            checked: false
            linkedSeries: productionPercentages
            /*
            onCheckedChanged: {
                waterBar.visible = checkState
                windBar.visible = checkState
                nuclBar.visible = checkState
            }
            */
        }

    }
    ControlRow {
        id: controlRow
    }
}
