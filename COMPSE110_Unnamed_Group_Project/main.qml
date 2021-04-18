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
    property int chartWidth: mainWindow.width / 4
    property int chartHeight: mainWindow.height / 2

    property int day_hours: 24
    property int week_hours: 24*7
    property int graph_scale_h: day_hours
    property int graph_scale_v: 30
    property int power_graph_scale_h: 2000

    Row {
        id: graphRow
        objectName: "graphRow"
        anchors.top: parent.top

        // Chart for weather data
        ChartElement {
            id: weatherGraph
            objectName: "weatherGraph"
            title: "Weather"

            Slider {
                from: 0
                to: 84
                anchors.top: parent.bottom
                onValueChanged: {
                    graph_scale_h = value * 2;
                }
            }

            // Temperature
            LineSeries {
                id: temperature;
                objectName: "temperature"
                name: "temperature";
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
                name: "windspeed";
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }

            // Cloudiness
            LineSeries {
                id: cloudiness;
                objectName: "cloudiness"
                name: "cloudiness";
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

            Slider {
                id:powerSlider
                from: 0
                to: 2000
                anchors.top: parent.bottom
                onValueChanged: {
                    power_graph_scale_h = value * 2;
                }
            }

            // General consumption
            LineSeries {
                id: totalConsumption;
                objectName: "totalConsumption"
                name: "totalConsumption";
                axisY: ValueAxis {
                    min: 0
                    //max: graph_scale_v
                    max: 13000
                }
                axisX:ValueAxis{
                    min:1
                    max:power_graph_scale_h
                }
            }

            // General production
            LineSeries {
                id: totalProduction;
                objectName: "totalProduction"
                name: "totalProduction";
                /**
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
                **/
            }
            LineSeries {
                id: nuclearProduction;
                objectName: "nuclearProduction"
                name: "nuclear";
            }
            LineSeries {
                id: windProduction;
                objectName: "windProduction"
                name: "wind";
            }
            LineSeries {
                id: waterProduction;
                objectName: "waterProduction"
                name: "water";
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

        // Chart for weather and power forecast for next 24h
        ChartElement {
            id: forecastGraph
            objectName: "forecastGraph"
            title: "FORECAST"
            // Weather forecast
            LineSeries {
                id: weatherForecast;
                objectName: "weatherForecast"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }
            // Production forecast
            LineSeries {
                id: productionForecast;
                objectName: "productionForecast"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }
            // Consumption forecast
            LineSeries {
                id: consumptionForecast;
                objectName: "consumptionForecast"
                axisY: ValueAxis {
                    min: 0
                    max: graph_scale_v
                }
            }
            Button {
                id: fetchForecast
                objectName: "fetchForecast"
                anchors.top: parent.bottom
                text: qsTr("Get forecast for the next 24h")

                signal renderForecast();
                onRenderForecast: {
                    controller.renderData(forecastGraph.objectName, weatherForecast.objectName);
                }

                onClicked: {
                    controller.fetchForecast();
                }
            }
        }
    }

    Row {
        id: graphSelectors
        objectName: "graphSelectors"
        anchors.top: graphRow.bottom
        anchors.topMargin: 40

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
            checked: true
            linkedSeries: cloudiness
        }
        GraphCheckBox {
            id: windBox
            objectName: "windBox"
            text: qsTr("Wind speed")
            checked: true
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
            checked: true
            linkedSeries: nuclearProduction
        }
        GraphCheckBox {
            id: productionWaterBox
            objectName: "productionWaterBox"
            text: qsTr("Water Power")
            checked: true
            linkedSeries: waterProduction
        }
        GraphCheckBox {
            id: productionWindBox
            objectName: "productionWindBox"
            text: qsTr("Wind Power")
            checked: true
            linkedSeries: windProduction
        }
        GraphCheckBox {
            id: productionPercentagesBox
            objectName: "productionPercentagesBox"
            text: qsTr("Production Percentages")
            checked: true
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

            // Save place, date and time to Settings
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
                        controller.editSettingsValue("startClock",
                                                     currentChild.startClock)
                        controller.editSettingsValue("endClock",
                                                     currentChild.endClock)
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

                // Load place, date and time from Settings
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

                        currentChild.startClock = controller.fetchSettingsValue("startClock");
                        currentChild.endClock = controller.fetchSettingsValue("endClock");
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
