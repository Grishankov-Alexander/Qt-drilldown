QT += sql widgets
requires(qtConfig(combobox))

HEADERS += \
    connection.h \
    imageitem.h \
    informationwindow.h \
    view.h

SOURCES += \
    imageitem.cpp \
    informationwindow.cpp \
    main.cpp \
    view.cpp

RESOURCES += \
    drilldown.qrc
