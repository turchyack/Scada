import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "SCADA Lite"

    ListView {
        anchors.fill: parent
        model: tagManager

        delegate: Rectangle {
            width: parent.width
            height: 40
            border.color: "gray"
            Row {
                spacing: 20
                Text { text: name }
                Text { text: value }
                Text { text: address }
                Text { text: type }
            }
        }
    }
}
