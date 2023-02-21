import QtQuick 2.0
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Controls 2.12
import "forms"
import "menus"
import "map"
import "helper.js" as Helper

Rectangle{
    property double oldLat: 40.00000000
    property double oldLng: 0.17621700
    property double toLat: 51.49905
    property double toLng: 0.176217
    property string street_now: "Cromwell Road 116"
    property string city_now: "London"
    property string coutry_now: "United Kingdom"
    property string postcode_now: "SW7 4XL"
    property variant fromCoordinate: QtPositioning.coordinate(51.5007, 0.1246)
    property variant toCoordinate: QtPositioning.coordinate(toLat, toLng)

    Plugin{
        id: mapPlugin
        name: "osm"

    }

    Map{
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(oldLat, oldLng);
        zoomLevel: 15
        //property alias routeQuery: routeQuery
        //property alias routeModel: routeModel
        signal showRouteList()
        signal routeError()

        gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.FlickGesture | MapGestureArea.PinchGesture | MapGestureArea.RotationGesture | MapGestureArea.TiltGesture
        gesture.flickDeceleration: 3000
        gesture.enabled: true
    //! [mapnavigation]
        focus: true
        //onCopyrightLinkActivated: Qt.openUrlExternally(link)

        Keys.onPressed: {
            if (event.key === Qt.Key_Plus) {
                mapView.zoomLevel++;
            } else if (event.key === Qt.Key_Minus) {
                mapView.zoomLevel--;
            } else if (event.key === Qt.Key_Left || event.key === Qt.Key_Right ||
                       event.key === Qt.Key_Up   || event.key === Qt.Key_Down) {
                var dx = 0;
                var dy = 0;

                switch (event.key) {

                case Qt.Key_Left: dx = mapView.width / 4; break;
                case Qt.Key_Right: dx = -mapView.width / 4; break;
                case Qt.Key_Up: dy = mapView.height / 4; break;
                case Qt.Key_Down: dy = -mapView.height / 4; break;

                }

                var mapCenterPoint = Qt.point(mapView.width / 2.0 - dx, mapView.height / 2.0 - dy);
                mapView.center = mapView.toCoordinate(mapCenterPoint);
            }
        }


        RouteModel {
            id: routeModel
            plugin : mapPlugin
            query:  RouteQuery {
                id: routeQuery
            }
            onStatusChanged: {
                if (status == RouteModel.Ready) {
                    switch (count) {
                    case 0:
                        // technically not an error
                        mapView.routeError()
                        break
                    case 1:
                        mapView.showRouteList()
                        break
                    }
                } else if (status == RouteModel.Error) {
                    mapView.routeError()
                }
            }
        }

        /*Component {
            id: routeDelegate

            MapRoute {
                id: route
                route: routeData
                //line.color: "#46a2da"
                line.color: "#e18946"
                line.width: 10
                smooth: true
                opacity: 0.8
            }
        }*/
        Component {
            id: routeDelegate

            MapRoute {
                id: route
                route: routeData
                line.color: "#e18946"
                line.width: 5
                smooth: true
                opacity: 0.8
         //! [routedelegate0]
                MouseArea {
                    id: routeMouseArea
                    anchors.fill: parent
                    hoverEnabled: false
                    property variant lastCoordinate

                    onPressed : {
                        mapView.lastX = mouse.x + parent.x
                        mapView.lastY = mouse.y + parent.y
                        mapView.pressX = mouse.x + parent.x
                        mapView.pressY = mouse.y + parent.y
                        lastCoordinate = mapView.toCoordinate(Qt.point(mouse.x, mouse.y))
                    }

                    onPositionChanged: {
                        if (mouse.button == Qt.LeftButton) {
                            mapView.lastX = mouse.x + parent.x
                            mapView.lastY = mouse.y + parent.y
                        }
                    }

                    onPressAndHold:{
                        if (Math.abs(mapView.pressX - parent.x- mouse.x ) < mapView.jitterThreshold
                                && Math.abs(mapView.pressY - parent.y - mouse.y ) < mapView.jitterThreshold) {
                            showRouteMenu(lastCoordinate);
                        }
                    }

                }
        //! [routedelegate1]
            }
        }

        MapSliders {
            id: sliders
            z: mapView.z + 3
            mapSource: mapView
            edge: Qt.LeftEdge
        }


        MapItemView {
            model: routeModel
            delegate: routeDelegate
        }

        // clear away any old data in the query
        /*routeQuery.clearWaypoints()

        // add the start and end coords as waypoints on the route
        routeQuery.addWaypoint(startCoordinate)
        routeQuery.addWaypoint(endCoordinate)
        routeQuery.travelModes = RouteQuery.CarTravel
        routeQuery.routeOptimizations = RouteQuery.FastestRoute

        routeModel.update();

        // center the map on the start coord
        map.center = startCoordinate;*/

        /*ListView {
            interactive: true
            model: List { id: routeInfoModel }
            header: RouteListHeader {}
            delegate:  RouteListDelegate{
                routeIndex.text: index + 1
                routeInstruction.text: instruction
                routeDistance.text: distance
            }
        }*/
        /*ListView {
        //! [routeinfomodel0]
            property variant routeModel
            property string totalTravelTime
            property string totalDistance
            signal closeForm()
        //! [routeinfomodel1]
            interactive: true
            model: ListModel { id: routeInfoModel }
            header: RouteListHeader {}
            delegate:  RouteListDelegate{
                routeIndex.text: index + 1
                routeInstruction.text: instruction
                routeDistance.text: distance
            }
        //! [routeinfomodel1]
            footer: Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Close")
                onClicked: {
                    closeForm()
                }
            }*/
            /*Component.onCompleted: {
                //! [routeinfomodel2]
                routeInfoModel.clear()
                if (routeModel.count > 0) {
                    for (var i = 0; i < routeModel.get(0).segments.length; i++) {
                        routeInfoModel.append({
                            "instruction": routeModel.get(0).segments[i].maneuver.instructionText,
                             "distance": Helper.formatDistance(routeModel.get(0).segments[i].maneuver.distanceToNextInstruction)
                        });
                    }
                }
                //! [routeinfomodel2]
                totalTravelTime = routeModel.count == 0 ? "" : Helper.formatTime(routeModel.get(0).travelTime)
                totalDistance = routeModel.count == 0 ? "" : Helper.formatDistance(routeModel.get(0).distance)
            }
        //! [routeinfomodel3]
        }*/

        /*Button {
              id: button
              text: qsTr("View Guide")

              anchors.top: parent.verticalCenter
              anchors.horizontalCenter: parent.horizontalCenter

              Component.onCompleted: {
                  // When the button is created, then connect the click signal on the button
                  // to the method for increasing the counter in the application window
                  button.clicked.connect(showRouteListPage())
              }
          }*/
        MouseArea {
            id: mouseArea
            property variant lastCoordinate
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onPressed : {
                mapView.lastX = mouse.x
                mapView.lastY = mouse.y
                mapView.pressX = mouse.x
                mapView.pressY = mouse.y
                lastCoordinate = mapView.toCoordinate(Qt.point(mouse.x, mouse.y))
            }

            onPositionChanged: {
                if (mouse.button == Qt.LeftButton) {
                    mapView.lastX = mouse.x
                    mapView.lastY = mouse.y
                }
            }

            onDoubleClicked: {
                var mouseGeoPos = mapView.toCoordinate(Qt.point(mouse.x, mouse.y));
                var preZoomPoint = mapView.fromCoordinate(mouseGeoPos, false);
                if (mouse.button === Qt.LeftButton) {
                    mapView.zoomLevel = Math.floor(mapView.zoomLevel + 1)
                } else if (mouse.button === Qt.RightButton) {
                    mapView.zoomLevel = Math.floor(mapView.zoomLevel - 1)
                }
                var postZoomPoint = mapView.fromCoordinate(mouseGeoPos, false);
                var dx = postZoomPoint.x - preZoomPoint.x;
                var dy = postZoomPoint.y - preZoomPoint.y;

                var mapCenterPoint = Qt.point(mapView.width / 2.0 + dx, mapView.height / 2.0 + dy);
                mapView.center = mapView.toCoordinate(mapCenterPoint);

                lastX = -1;
                lastY = -1;
            }

            onPressAndHold:{
                if (Math.abs(mapView.pressX - mouse.x ) < mapView.jitterThreshold
                        && Math.abs(mapView.pressY - mouse.y ) < mapView.jitterThreshold) {
                    showMainMenu(lastCoordinate);
                }
            }
        }




    /*function setCenter(lat, lng){
        mapView.pan(oldLat - lat, oldLng - lng)
        oldLat = lat
        oldLng = lng
    }*/



    /*RouteModel {
        id: routeModel
        plugin : mapPlugin
        query:  RouteQuery {
            id: routeQuery
        }
        onStatusChanged: {
            if (status == RouteModel.Ready) {
                switch (count) {
                case 0:
                    // technically not an error
                    mapView.routeError()
                    break
                case 1:
                    mapView.showRouteList()
                    break
                }
            } else if (status == RouteModel.Error) {
                mapView.routeError()
            }
        }
    }

    Component {
        id: routeDelegate

        MapRoute {
            id: route
            route: routeData
            //line.color: "#46a2da"
            line.color: "#e18946"
            line.width: 10
            smooth: true
            opacity: 0.8
        }
    }

    MapItemView {
        model: routeModel
        delegate: routeDelegate
    }*/

    // clear away any old data in the query
    /*routeQuery.clearWaypoints()

    // add the start and end coords as waypoints on the route
    routeQuery.addWaypoint(startCoordinate)
    routeQuery.addWaypoint(endCoordinate)
    routeQuery.travelModes = RouteQuery.CarTravel
    routeQuery.routeOptimizations = RouteQuery.FastestRoute

    routeModel.update();

    // center the map on the start coord
    map.center = startCoordinate;*/

    /*ItemPopupMenu {
        id: itemPopupMenu

        function show(type,coordinate)
        {
            //stackView.pop(page)
            itemPopupMenu.type = type
            itemPopupMenu.update()
            itemPopupMenu.popup()
        }

        onItemClicked: {
            //stackView.pop(page)
            switch (item) {
            case "showRouteInfo":
                //stackView.showRouteListPage()
                break;
            case "deleteRoute":
                mapView.routeModel.reset();
                break;
            case "showPointInfo":
                mapView.showGeocodeInfo()
                break;
            case "deletePoint":
                mapView.geocodeModel.reset()
                break;
            default:
                console.log("Unsupported operation")
            }
        }
    }*/
    }
    function showRoute() {
        routeQuery.clearWaypoints();

        // add the start and end coords as waypoints on the route
        routeQuery.addWaypoint(fromCoordinate)
        routeQuery.addWaypoint(toCoordinate)
        routeQuery.travelModes = RouteQuery.CarTravel
        routeQuery.routeOptimizations = RouteQuery.FastestRoute

        for (var i=0; i<9; i++) {
                   routeQuery.setFeatureWeight(i, 0)
               }

        routeModel.update();

        // center the map on the start coord
        mapView.center = fromCoordinate;
    }

    function clearRoute(){
        //routeQuery.clearWayPoints();
        routeModel.update();
    }

    /*function viewList(){
        routeInfoModel.clear()
        if (routeModel.count > 0) {
            for (var i = 0; i < routeModel.get(0).segments.length; i++) {
                routeInfoModel.append({
                    "instruction": routeModel.get(0).segments[i].maneuver.instructionText,
                     "distance": Helper.formatDistance(routeModel.get(0).segments[i].maneuver.distanceToNextInstruction)
                });
            }
        }
    }*/
    /*function showRouteListPage()
    {
        push({ item: Qt.resolvedUrl("forms/RouteList.qml") ,
                           properties: {
                               "routeModel" : mapView.routeModel
                           }})
        currentItem.closeForm.connect(closeForm)
    }*/


}
