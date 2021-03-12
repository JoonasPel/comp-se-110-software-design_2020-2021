import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQuick.Controls 2.2

// Chart for weather data
ChartView {
    property string typeName: "";
    property LineSeries childSeries: seriesChild;

    width: chartWidth
    height: chartHeight
    theme: ChartView.ChartThemeDark
    antialiasing: true

    // List of actual data points in graph
    LineSeries {
        id: seriesChild
        objectName: typeName + "Series"
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
        setAxisX(seriesChild.axisX);
        setAxisY(seriesChild.axisY);

    }
}
