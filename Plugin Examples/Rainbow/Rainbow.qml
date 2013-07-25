import QtQuick 2.0
import GlobiPlugin 1.0
import "Rainbow.js" as RainbowUtils

Plugin {
    id : plugin
    property variant timer

    property var r
    property var g
    property var b
    property var changerFunction

    property int step : 25

    name    : 'Rainbow & Unicorns'
    version : 'Rose Bonbon'
    author  : 'Globimulticolored'
    icon    : Qt.resolvedUrl('Icon.png')

    activable : false

    settings : Settings {
        id : conf
        prefix : 'Rainbow & Unicorns'
    }

    uis : [
        Ui {
            id   : configUi
            file : Qt.resolvedUrl('unicorn.ui')

            function init() {
                var enabled  = conf.value('enabled', 'false').toBool()
                var interval = conf.value('timer_interval', 500)
                var step     = conf.value('component_step', 25)

                enable(enabled)
                changeInterval(interval)
                changeStep(step)

                loaded.enabled.checked = enabled
                loaded.interval.value  = interval
                loaded.step.value      = step

                loaded.enabled.toggled.connect(enable)
                loaded.interval.valueChanged.connect(changeInterval)
                loaded.step.valueChanged.connect(changeStep)
            }

            function enable(enabled) {
                timer.running = enabled
                conf.setValue('enabled', enabled)
            }

            function changeInterval(value) {
                timer.interval = value
                loaded.intervalLabel.text = String(value) + ' ms'
                conf.setValue('timer_interval', value)
            }

            function changeStep(value) {
                step = value
                loaded.stepLabel.text = String(value)
                conf.setValue('component_step', value)
            }
        }
    ]

    onConfigure : configUi.show()

    function redify() {
        r = Math.min(r + step, 255)
        if(r == 255) changerFunction = unBlueify
    }

    function greenify() {
        g = Math.min(g + step, 255)
        if(g == 255) changerFunction = unRedify
    }

    function blueify() {
        b = Math.min(b + step, 255)
        if(b == 255) changerFunction = unGreenify
    }

    function unRedify() {
        r = Math.max(r - step, 0)
        if(r == 0) changerFunction = blueify
    }
    
    function unGreenify() {
        g = Math.max(g - step, 0)
        if(g == 0) changerFunction = redify
    }

    function unBlueify() {
        b = Math.max(b - step, 0)
        if(b == 0) changerFunction = greenify
    }

    function applyColor() {
        ImageEngine.setMaskColor(Qt.rgba(r / 255, g / 255, b / 255))
    }

    function initRainbowState() {
        r = 255
        g = 0
        b = 0
        changerFunction = greenify
    }

    function createDynamicTimer() {
        var timerComponent = Qt.createComponent(Qt.resolvedUrl('timer.qml'), Component.Asynchronous)
        timerComponent.statusChanged.connect(function() {
            if(timerComponent.status == Component.Ready)
            {
                timer = timerComponent.createObject(plugin)
                configUi.init()
            }
            else
                console.log('component creation error')
        })
    }

    Component.onCompleted : {
        initRainbowState()
        createDynamicTimer()
    }
}