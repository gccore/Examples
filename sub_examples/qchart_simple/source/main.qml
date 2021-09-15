import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtCharts 2.3
import QtQuick 2.0

ApplicationWindow
{
        visible: true;
        width: 800;
        height: 600;

        ChartView
        {
                id: chartView
                anchors.fill: parent;
                antialiasing: true;

                ValueAxis { id: axisY1; min: -1; max: 4; }
                ValueAxis { id: axisY2; min: -10; max: 5; }
                ValueAxis { id: axisY3; min: -100; max: 15; }
                ValueAxis { id: axisX; min: 0; max: 1024; }

                LineSeries
                {
                        id: lineSeries1
                        name: "signal 1"
                        axisX: axisX
                        axisY: axisY1
                        useOpenGL: true
                }
                LineSeries
                {
                        id: lineSeries2
                        name: "signal 2"
                        axisX: axisX
                        axisYRight: axisY2
                        useOpenGL: true
                }

                Timer
                {
                        id: refreshTimer
                        interval: 1
                        running: true
                        repeat: true
                        onTriggered:
                        {
                                dataSource.update(chartView.series(0));
                                dataSource.update(chartView.series(1));
                        }
                }

                Component.onCompleted:
                {
                        var series1 = chartView.createSeries(ChartView.SeriesTypeScatter,
                                                             "signal 1", axisX, axisY1);
                        series1.markerSize = 2;
                        series1.borderColor = "transparent";

                        var series2 = chartView.createSeries(ChartView.SeriesTypeScatter,
                                                             "signal 2", axisX, axisY2);
                        series2.markerSize = 2;
                        series2.borderColor = "transparent";
                }
        }
}
