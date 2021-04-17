import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

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

            // Cloudiness
            LineSeries {
                id: cloudiness;
                objectName: "cloudiness"
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
            title: "Power consumption and production"

            // General consumption
            LineSeries {
                id: totalConsumption;
                objectName: "totalConsumption"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }

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

        // Chart for separation between power production types
        ChartElement {
            id: historyGraph
            objectName: "historyGraph"
            title: "Saved history"

            // General consumption
            LineSeries {
                id: totalConsumptionHistory;
                objectName: "totalConsumptionHistory"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }

            // General production
            LineSeries {
                id: totalProductionHistory;
                objectName: "totalProductionHistory"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
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
            objectName: "temperatureBox"
            text: qsTr("Temperature")
            checked: true
            linkedSeries: temperature
        }
        GraphCheckBox {
            id: cloudBox
            objectName: "cloudBox"
            text: qsTr("Cloudiness")
            checked: false
            linkedSeries: cloudiness
        }
        GraphCheckBox {
            id: windBox
            objectName: "windBox"
            text: qsTr("Wind speed")
            checked: false
            linkedSeries: windSpeed
        }

        /* ================================
         * Middle graph: Consumption and production values
         */
        GraphCheckBox {
            id: consumptionBox
            objectName: "consumptionBox"
            text: qsTr("Total Consumption")
            checked: true
            linkedSeries: totalConsumption
        }

        GraphCheckBox {
            id: productionBox
            objectName: "productionBox"
            text: qsTr("Total Production")
            checked: true
            linkedSeries: totalProduction
        }
        GraphCheckBox {
            id: productionNuclearBox
            objectName: "productionNuclearBox"
            text: qsTr("Nuclear Power")
            checked: false
            linkedSeries: nuclearProduction
        }
        GraphCheckBox {
            id: productionWaterBox
            objectName: "productionWaterBox"
            text: qsTr("Water Power")
            checked: false
            linkedSeries: waterProduction
        }
        GraphCheckBox {
            id: productionWindBox
            objectName: "productionWindBox"
            text: qsTr("Wind Power")
            checked: false
            linkedSeries: windProduction
        }
        GraphCheckBox {
            id: productionPercentagesBox
            objectName: "productionPercentagesBox"
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

        /* ==============================
         * Right graph: History
         */
        GraphCheckBox {
            id: consumptionHistoryBox
            objectName: "consumptionHistoryBox"
            text: qsTr("Consumption history")
            checked: false
            linkedSeries: totalConsumptionHistory
        }

        GraphCheckBox {
            id: productionHistoryBox
            objectName: "productionHistoryBox"
            text: qsTr("Production history")
            checked: false
            linkedSeries: totalProductionHistory
        }

    }
    ControlRow {
        id: controlRow
        anchors.top: graphSelectors.bottom
    }
    Row {
        id: historyQuery
        anchors.top: controlRow.bottom
        Button {
            text: qsTr("Fetch history")
            anchors.top: parent.bottom
        }
        TextField {
            id: startTimeSelector
            anchors.top: parent.bottom
            placeholderText: qsTr("Starting time")
        }
        TextField {
            id: endTimeSelector
            anchors.top: parent.bottom
            placeholderText: qsTr("Ending time")
        }
    }
    Row {
        id: preferenceSettings
        anchors.top: historyQuery.bottom
        Button {
            id: savePreferences
            anchors.top: parent.bottom
            text: qsTr("Save preferences")

            // Save element values to Settings element
            onClicked: {

                for( var checkBox in graphSelectors.children ) {
                    var current = graphSelectors.children[checkBox];

                    controller.editSettingsValue(current.objectName + "Checked", current.checked);
                }

            // Save place, start date and end date to Settings
                for( var child in controlRow.children) {
                    var currentChild = controlRow.children[child];

                    if( currentChild.objectName === "placeSelector") {
                        controller.editSettingsValue(currentChild.objectName,
                                                     currentChild.currentIndex)
                    } else if ( currentChild.objectName === "DatePicker") {
                        controller.editSettingsValue("startDate",
                                                     currentChild.startDate);
                        controller.editSettingsValue("endDate",
                                                     currentChild.endDate)
                    }
                }
            }
        }
        Button {
            id: loadPreferences
            anchors.top: parent.bottom
            text: qsTr("Load preferences")

            // Load values to elements from Settings
            onClicked: {
                console.log("====Settings==========")
                for( let checkBox in graphSelectors.children ) {
                    var current = graphSelectors.children[checkBox];

                    console.log("Result " + controller.fetchSettingsValue(current.objectName + "Checked"));
                    current.checked = controller.fetchSettingsValue(current.objectName + "Checked");
                }

                // Load place and dates from Settings
                for( var child in controlRow.children) {
                    var currentChild = controlRow.children[child];

                    if( currentChild.objectName === "placeSelector") {
                        currentChild.currentIndex = controller.fetchSettingsValue(currentChild.objectName);
                        // update place to parameters_ in model
                        controller.setParameter("place", currentChild.currentText);
                    } else if (currentChild.objectName === "DatePicker") {
                        // endDate loaded twice to bypass calendar min/max value
                        currentChild.endDate = controller.fetchSettingsValue("endDate");
                        currentChild.startDate = controller.fetchSettingsValue("startDate");
                        currentChild.endDate = controller.fetchSettingsValue("endDate");
                    }
                }

            }
        }
    }

    Settings {
        id: settings

        // Checkbox values
        property bool tempChecked: false
        property bool windChecked: false
        property bool prodChecked: false
        property bool consumpChecked: false
        property bool prodNuclearChecked: false
        property bool prodWaterChecked: false
        property bool prodWindChecked: false
        property bool prodPercChecked: false

        // Starting - ending times
        property string currentStartTime: ""
        property string currentEndTime: ""
        property string historyStartTime: ""
        property string historyEndTime: ""
    }
}
