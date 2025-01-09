TARGET = CleanroomSim

QT += gui           # interfaccia grafica
QT += charts        # grafici
QT += svgwidgets    # icone


HEADERS += \
    Charts/chartsvisitor.h \
    Sensors/Converter/convertervisitor.h \
    Sensors/Converter/parser.h \
    Sensors/Storage/archive.h \
    Sensors/Storage/archiveobserver.h \
    Sensors/abstractsensor.h \
    Sensors/hygrometer.h \
    Sensors/manometer.h \
    Sensors/particlecounter.h \
    Sensors/particles.h \
    Sensors/sensorobserver.h \
    Sensors/sensorvisitor.h \
    View/Dialogs/addsensorwindow.h \
    View/Dialogs/deletesensorwindow.h \
    View/Dialogs/edithygrometerwindow.h \
    View/Dialogs/editmanometerwindow.h \
    View/Dialogs/editparticlecounterwindow.h \
    View/mainwindow.h \
    View/sensordetails.h \
    View/sensorslist.h \
    View/sensorview.h \
    View/sensorviewer.h \
    View/sensorwidget.h \
    View/toolbar.h \

SOURCES += \
    Charts/chartsvisitor.cpp \
    Sensors/Converter/convertervisitor.cpp \
    Sensors/Converter/parser.cpp \
    Sensors/Storage/archive.cpp \
    Sensors/abstractsensor.cpp \
    Sensors/hygrometer.cpp \
    Sensors/manometer.cpp \
    Sensors/particlecounter.cpp \
    Sensors/particles.cpp \
    View/Dialogs/addsensorwindow.cpp \
    View/Dialogs/deletesensorwindow.cpp \
    View/Dialogs/edithygrometerwindow.cpp \
    View/Dialogs/editmanometerwindow.cpp \
    View/Dialogs/editparticlecounterwindow.cpp \
    View/mainwindow.cpp \
    View/sensordetails.cpp \
    View/sensorslist.cpp \
    View/sensorview.cpp \
    View/sensorviewer.cpp \
    View/sensorwidget.cpp \
    View/toolbar.cpp \
    main.cpp

RESOURCES += \
    Resources.qrc
