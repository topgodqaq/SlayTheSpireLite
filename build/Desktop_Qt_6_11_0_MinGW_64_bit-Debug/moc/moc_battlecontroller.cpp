/****************************************************************************
** Meta object code from reading C++ file 'battlecontroller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/battle/battlecontroller.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'battlecontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16BattleControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto BattleController::qt_create_metaobjectdata<qt_meta_tag_ZN16BattleControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BattleController",
        "battleStateChanged",
        "",
        "BattleState",
        "newState",
        "battleStarted",
        "QList<Enemy>",
        "enemies",
        "battleEnded",
        "playerWon",
        "playerHealthChanged",
        "current",
        "max",
        "playerEnergyChanged",
        "playerBlockChanged",
        "block",
        "playerStatusChanged",
        "status",
        "enemyHealthChanged",
        "index",
        "enemyIntentChanged",
        "intent",
        "value",
        "cardPlayed",
        "cardIndex",
        "targetIndex",
        "handChanged",
        "QList<Card>",
        "hand",
        "deckInfoChanged",
        "deckSize",
        "discardSize",
        "drawPileSize",
        "playerTurnStarted",
        "enemyTurnStarted",
        "turnEnded",
        "battleLog",
        "message"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'battleStateChanged'
        QtMocHelpers::SignalData<void(enum BattleState)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'battleStarted'
        QtMocHelpers::SignalData<void(const QVector<Enemy> &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'battleEnded'
        QtMocHelpers::SignalData<void(bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'playerHealthChanged'
        QtMocHelpers::SignalData<void(int, int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
        }}),
        // Signal 'playerEnergyChanged'
        QtMocHelpers::SignalData<void(int, int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
        }}),
        // Signal 'playerBlockChanged'
        QtMocHelpers::SignalData<void(int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 15 },
        }}),
        // Signal 'playerStatusChanged'
        QtMocHelpers::SignalData<void(const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Signal 'enemyHealthChanged'
        QtMocHelpers::SignalData<void(int, int, int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 19 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
        }}),
        // Signal 'enemyIntentChanged'
        QtMocHelpers::SignalData<void(int, const QString &, int)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 19 }, { QMetaType::QString, 21 }, { QMetaType::Int, 22 },
        }}),
        // Signal 'cardPlayed'
        QtMocHelpers::SignalData<void(int, int)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 24 }, { QMetaType::Int, 25 },
        }}),
        // Signal 'handChanged'
        QtMocHelpers::SignalData<void(const QVector<Card> &)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 27, 28 },
        }}),
        // Signal 'deckInfoChanged'
        QtMocHelpers::SignalData<void(int, int, int)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 30 }, { QMetaType::Int, 31 }, { QMetaType::Int, 32 },
        }}),
        // Signal 'playerTurnStarted'
        QtMocHelpers::SignalData<void()>(33, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'enemyTurnStarted'
        QtMocHelpers::SignalData<void()>(34, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'turnEnded'
        QtMocHelpers::SignalData<void()>(35, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'battleLog'
        QtMocHelpers::SignalData<void(const QString &)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 37 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<BattleController, qt_meta_tag_ZN16BattleControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject BattleController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16BattleControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16BattleControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16BattleControllerE_t>.metaTypes,
    nullptr
} };

void BattleController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BattleController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->battleStateChanged((*reinterpret_cast<std::add_pointer_t<enum BattleState>>(_a[1]))); break;
        case 1: _t->battleStarted((*reinterpret_cast<std::add_pointer_t<QList<Enemy>>>(_a[1]))); break;
        case 2: _t->battleEnded((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->playerHealthChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->playerEnergyChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->playerBlockChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->playerStatusChanged((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->enemyHealthChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 8: _t->enemyIntentChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 9: _t->cardPlayed((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->handChanged((*reinterpret_cast<std::add_pointer_t<QList<Card>>>(_a[1]))); break;
        case 11: _t->deckInfoChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3]))); break;
        case 12: _t->playerTurnStarted(); break;
        case 13: _t->enemyTurnStarted(); break;
        case 14: _t->turnEnded(); break;
        case 15: _t->battleLog((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(BattleState )>(_a, &BattleController::battleStateChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(const QVector<Enemy> & )>(_a, &BattleController::battleStarted, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(bool )>(_a, &BattleController::battleEnded, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(int , int )>(_a, &BattleController::playerHealthChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(int , int )>(_a, &BattleController::playerEnergyChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(int )>(_a, &BattleController::playerBlockChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(const QString & )>(_a, &BattleController::playerStatusChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(int , int , int )>(_a, &BattleController::enemyHealthChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(int , const QString & , int )>(_a, &BattleController::enemyIntentChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(int , int )>(_a, &BattleController::cardPlayed, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(const QVector<Card> & )>(_a, &BattleController::handChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(int , int , int )>(_a, &BattleController::deckInfoChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)()>(_a, &BattleController::playerTurnStarted, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)()>(_a, &BattleController::enemyTurnStarted, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)()>(_a, &BattleController::turnEnded, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (BattleController::*)(const QString & )>(_a, &BattleController::battleLog, 15))
            return;
    }
}

const QMetaObject *BattleController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BattleController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16BattleControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BattleController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void BattleController::battleStateChanged(BattleState _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void BattleController::battleStarted(const QVector<Enemy> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void BattleController::battleEnded(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void BattleController::playerHealthChanged(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void BattleController::playerEnergyChanged(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void BattleController::playerBlockChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void BattleController::playerStatusChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void BattleController::enemyHealthChanged(int _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}

// SIGNAL 8
void BattleController::enemyIntentChanged(int _t1, const QString & _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2, _t3);
}

// SIGNAL 9
void BattleController::cardPlayed(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2);
}

// SIGNAL 10
void BattleController::handChanged(const QVector<Card> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void BattleController::deckInfoChanged(int _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2, _t3);
}

// SIGNAL 12
void BattleController::playerTurnStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void BattleController::enemyTurnStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void BattleController::turnEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void BattleController::battleLog(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1);
}
QT_WARNING_POP
