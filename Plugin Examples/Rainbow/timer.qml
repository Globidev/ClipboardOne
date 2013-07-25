import QtQuick 2.0

Timer {
	interval : 500
	running  : false
	repeat   : true

	onTriggered : {
		changerFunction()
		applyColor()
	}
}