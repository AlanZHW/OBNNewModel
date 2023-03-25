/****************************************************************************
** Meta object code from reading C++ file 'rnmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rnmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rnmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RNManager_t {
    QByteArrayData data[22];
    char stringdata0[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RNManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RNManager_t qt_meta_stringdata_RNManager = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RNManager"
QT_MOC_LITERAL(1, 10, 20), // "slotSetSearchIpScope"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "slotQuit"
QT_MOC_LITERAL(4, 41, 10), // "slotLimits"
QT_MOC_LITERAL(5, 52, 21), // "slotSetUpdateInterval"
QT_MOC_LITERAL(6, 74, 8), // "interval"
QT_MOC_LITERAL(7, 83, 19), // "slotStartStopUpdate"
QT_MOC_LITERAL(8, 103, 5), // "start"
QT_MOC_LITERAL(9, 109, 18), // "slotNodeFtpManager"
QT_MOC_LITERAL(10, 128, 22), // "slotShowAllOrConnected"
QT_MOC_LITERAL(11, 151, 4), // "show"
QT_MOC_LITERAL(12, 156, 9), // "slotAbout"
QT_MOC_LITERAL(13, 166, 22), // "slotPrintWarningEnable"
QT_MOC_LITERAL(14, 189, 6), // "enable"
QT_MOC_LITERAL(15, 196, 20), // "slotShowStatusReport"
QT_MOC_LITERAL(16, 217, 18), // "slotDisplayFilters"
QT_MOC_LITERAL(17, 236, 19), // "slotAtomicClockTame"
QT_MOC_LITERAL(18, 256, 8), // "slotSetD"
QT_MOC_LITERAL(19, 265, 8), // "slotGetD"
QT_MOC_LITERAL(20, 274, 28), // "slotStartCalibrationFunction"
QT_MOC_LITERAL(21, 303, 26) // "slotEndCalibrationFunction"

    },
    "RNManager\0slotSetSearchIpScope\0\0"
    "slotQuit\0slotLimits\0slotSetUpdateInterval\0"
    "interval\0slotStartStopUpdate\0start\0"
    "slotNodeFtpManager\0slotShowAllOrConnected\0"
    "show\0slotAbout\0slotPrintWarningEnable\0"
    "enable\0slotShowStatusReport\0"
    "slotDisplayFilters\0slotAtomicClockTame\0"
    "slotSetD\0slotGetD\0slotStartCalibrationFunction\0"
    "slotEndCalibrationFunction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RNManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    1,   97,    2, 0x08 /* Private */,
       7,    1,  100,    2, 0x08 /* Private */,
       9,    0,  103,    2, 0x08 /* Private */,
      10,    1,  104,    2, 0x08 /* Private */,
      12,    0,  107,    2, 0x08 /* Private */,
      13,    1,  108,    2, 0x08 /* Private */,
      15,    0,  111,    2, 0x08 /* Private */,
      16,    1,  112,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,
      20,    0,  118,    2, 0x08 /* Private */,
      21,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RNManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RNManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotSetSearchIpScope(); break;
        case 1: _t->slotQuit(); break;
        case 2: _t->slotLimits(); break;
        case 3: _t->slotSetUpdateInterval((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->slotStartStopUpdate((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 5: _t->slotNodeFtpManager(); break;
        case 6: _t->slotShowAllOrConnected((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 7: _t->slotAbout(); break;
        case 8: _t->slotPrintWarningEnable((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 9: _t->slotShowStatusReport(); break;
        case 10: _t->slotDisplayFilters((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 11: _t->slotAtomicClockTame(); break;
        case 12: _t->slotSetD(); break;
        case 13: _t->slotGetD(); break;
        case 14: _t->slotStartCalibrationFunction(); break;
        case 15: _t->slotEndCalibrationFunction(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RNManager::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_RNManager.data,
    qt_meta_data_RNManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RNManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RNManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RNManager.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RNManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
