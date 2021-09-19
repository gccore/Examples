import QtQuick.Controls 2.0
import QtQuick 2.0

import qml.pass.id 1.0

ApplicationWindow
{
        visible: true;
        width: 800;
        height: 400;

        TestItem
        {
                objectName: "testItem";
        }
}
