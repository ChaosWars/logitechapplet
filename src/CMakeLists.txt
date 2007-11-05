FIND_PACKAGE( Qt4 REQUIRED )
FIND_PACKAGE( DBUS REQUIRED )
INCLUDE_DIRECTORIES( ${QT_INCLUDES}
					${QT_QTDBUS_INCLUDE_DIR}
					${QT_GUI_INCLUDE_DIR}
					${CMAKE_CURRENT_BINARY_DIR}
					${CMAKE_CURRENT_SOURCE_DIR} )
SET( SRC main.cpp logitechapplet.cpp )
SET( UI_SRC logitechapplet.ui )
SET( DBUSXML applet.xml )
QT4_ADD_DBUS_INTERFACE( DBUSSRC ${DBUSXML} appletinterface LogitechApplet )
QT4_ADD_RESOURCES( QRC applet.qrc )
QT4_WRAP_UI( UI_SRC_H ${UI_SRC} )
QT4_AUTOMOC( ${SRC} )
ADD_DEFINITIONS( ${QT_DEFINITIONS} )
ADD_EXECUTABLE( logitechapplet ${SRC} ${DBUSSRC} ${UI_SRC} ${QRC} )
TARGET_LINK_LIBRARIES( logitechapplet ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTDBUS_LIBRARY} )
INSTALL( TARGETS logitechapplet RUNTIME DESTINATION /usr/bin )
INSTALL( FILES pics/logitech_logo.png pics/Logitech_logo.png DESTINATION /usr/share/pixmaps )
INSTALL( FILES logitechapplet.desktop DESTINATION /usr/share/applications )
