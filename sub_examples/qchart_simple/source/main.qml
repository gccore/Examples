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
                anchors.fill: parent;
                antialiasing: true;

                PieSeries
                {
                        PieSlice
                        {
                                label: "Ghasem";
                                value: 10.0;
                        }
                        PieSlice
                        {
                                label: "Another Ghasem";
                                value: 90.0;
                        }
                }
        }
}
