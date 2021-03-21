import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQuick.Controls 2.2

// Row for graph settings controllers
Row {
    objectName: "controlRow"
    anchors.top: graphSelectors.bottom

    /*
     * Original button for fetching data

    Button {
        font.pointSize: 20
        text: "Click To Fetch Data From FMI"
        anchors.top: parent.bottom

        onClicked: {
            controller.fetchData("http://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place=Pirkkala&starttime=2021-02-14T09:00:00Z&endtime=2021-02-21T09:00:00Z&timestep=60&parameters=t2m,ws_10min,n_man", placeSelector.currentText);
            }
    }
    */

    Button {
        font.pointSize: 20
        text: "Fetch from FMI and Render"
        anchors.top: parent.bottom

        onClicked: {
            controller.fetchData("http://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place=Pirkkala&starttime=2021-02-14T09:00:00Z&endtime=2021-02-21T09:00:00Z&timestep=60&parameters=t2m,ws_10min,n_man", placeSelector.currentText);
            controller.renderData(weatherGraph.objectName, temperature.objectName);
            controller.renderData(weatherGraph.objectName, windSpeed.objectName);
            // controller.renderData(consumptionGraph.objectName, consumptionGraph.childSeries.objectName);
            // controller.renderData(productionGraph.objectName, productionGraph.childSeries.objectName);
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
