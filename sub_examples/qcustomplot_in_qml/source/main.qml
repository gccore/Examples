import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtCharts 2.3
import QtQuick 2.0

import CustomPlot 1.0

ApplicationWindow
{
        visible: true;
        width: 800;
        height: 600;

        CustomPlotItem
        {
                id: customPlot
                anchors.fill: parent
                Component.onCompleted: initCustomPlot()
        }
}
