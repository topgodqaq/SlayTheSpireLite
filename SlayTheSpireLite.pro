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
    src/battle/battlecontroller.cpp \
    src/core/card.cpp \
    src/core/enemy.cpp \
    src/core/player.cpp

HEADERS += \
    src/battle/battlecontroller.h \
    src/core/card.h \
    src/core/enemy.h \
    src/core/player.h

# 资源文件（可选）
RESOURCES += \
    resources.qrc

# 使用图片资源，创建目录
DESTDIR = $$OUT_PWD/bin
MOC_DIR = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
RCC_DIR = $$OUT_PWD/rcc
UI_DIR = $$OUT_PWD/ui