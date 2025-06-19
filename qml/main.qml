// import QtQuick 2.15
// import QtQuick.Controls 2.15

// ApplicationWindow {
//     visible: true
//     width: 600
//     height: 400
//     title: "SCADA Lite"

//     ListView {
//         anchors.fill: parent
//         model: tagManager

//         delegate: Rectangle {
//             width: parent.width
//             height: 40
//             border.color: "gray"
//             Row {
//                 spacing: 20
//                 Text { text: name }
//                 Text { text: value }
//                 Text { text: address }
//                 Text { text: type }
//             }
//         }
//     }
// }


// import QtQuick 2.15
// import QtQuick.Controls 2.15

// ApplicationWindow {
//     visible: true
//     width: 400
//     height: 200
//     title: "SCADA Lite - Один тег"

//     Column {
//         anchors.centerIn: parent
//         spacing: 10

//         Text { text: "Name: " + tag.name }
//         Text { text: "Value: " + tag.value }
//         Text { text: "Address: " + tag.address }
//         Text { text: "Type: " + tag.type }
//     }
// }




import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "SCADA Lite - Теги"

    ListView {
        anchors.fill: parent
        model: tagManager

        delegate: Rectangle {
            width: parent.width
            height: 50
            color: index % 2 === 0 ? "#f0f0f0" : "#ffffff" // Чередование цвета строк
            anchors.margins: 5
            border.color: "#cccccc"
            radius: 5

            Row {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 20

                Text { text: name; font.bold: true; width: 150 }
                Text { text: value; width: 100 }
                Text { text: address; width: 100 }
                Text { text: type; width: 100 }
            }
        }
    }
}

