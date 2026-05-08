# SlayTheSpireLite.pro
QT += core gui widgets

CONFIG += c++17
CONFIG += warn_on

TARGET = SlayTheSpireLite
TEMPLATE = app

# 启用C++14以上特性
QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
    main.cpp \
    src/battlecontroller.cpp \
    src/player.cpp \
    src/enemy.cpp \
    src/card.cpp \
    src/carddatabase.cpp \
    ui/cardwidget.cpp \
    ui/battleview.cpp

HEADERS += \
    src/battlecontroller.h \
    src/player.h \
    src/enemy.h \
    src/card.h \
    src/carddatabase.h \
    ui/cardwidget.h \
    ui/battleview.h

# 资源文件（可选）
RESOURCES += \
    resources.qrc

# 如果使用图片资源，创建目录
DESTDIR = $$OUT_PWD/bin
MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
RCC_DIR = $$OUT_PWD/rcc
UI_DIR = $$OUT_PWD/ui