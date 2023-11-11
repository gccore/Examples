import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import idiot.validator 1.0

ApplicationWindow
{
    visible: true;
    width: 800;
    height: 400;

    GridLayout {
	anchors.centerIn: parent
	
	rows: 3
	columns: 2
	
	Label {
	    Layout.row: 0
	    Layout.column: 0
	    
	    text: "Top: "
	} // Label
	SpinBox {
	    Layout.row: 0
	    Layout.column: 1
	    
	    id: top_value
	    
	    value: 100
	    editable: true
	    from: -1000
	    to: +1000
	} // SpinBox
	
	Label {
	    Layout.row: 1
	    Layout.column: 0
	    
	    text: "Bottom: "
	} // Label
	SpinBox {
	    Layout.row: 1
	    Layout.column: 1
	    
	    id: bottom_value

	    value: 0
	    editable: true
	    from: -1000
	    to: +1000
	} // SpinBox

	Label {
	    Layout.row: 2
	    Layout.column: 0

	    text: "Value: "
	} // Label
	TextInput {
	    Layout.row: 2
	    Layout.column: 1

	    font.pixelSize: 120
	    focus: true

	    validator: IdiotValidator {
		top: top_value.value
		bottom: bottom_value.value
	    } // IdiotValidator
	} // TextInput
    } // GridLayout
} // ApplicationWindow
