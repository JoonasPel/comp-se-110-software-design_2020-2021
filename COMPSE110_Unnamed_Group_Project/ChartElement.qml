import QtQuick 2.6
import QtQuick.Window 2.2
import QtCharts 2.3
import QtQuick.Controls 2.2

// Chart for weather data
ChartView {
    width: chartWidth
    height: chartHeight
    theme: ChartView.ChartThemeDark
    antialiasing: true

    onSeriesAdded: {
        console.log("points changed");
        setAxisX(series.axisX);
        setAxisY(series.axisY);
    }
}
