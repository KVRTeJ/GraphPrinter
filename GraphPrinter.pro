QT       += core gui sql widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApplicationWindow.cpp \
    DataExtract.cpp \
    DependencyInversion.cpp \
    IOC_Container.cpp \
    JsonParser.cpp \
    MainController.cpp \
    SqlLiteParser.cpp \
    main.cpp

HEADERS += \
    AbstractChartCreator.h \
    AbstractParser.h \
    ApplicationWindow.h \
    AreaChartCreator.h \
    DataExtract.h \
    DataModel.h \
    DependencyInversion.h \
    IChartCreator.h \
    IChartView.h \
    IOC_Contaner.h \
    IParser.h \
    JsonParser.h \
    LineChartCreator.h \
    MainController.h \
    ScatterChartCreator.h \
    SplineChartCreator.h \
    SqlLiteParser.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
