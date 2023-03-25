/****************************************************************************
** Meta object code from reading C++ file 'nodeftp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nodeftp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodeftp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NodeFtp_t {
    QByteArrayData data[21];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NodeFtp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NodeFtp_t qt_meta_stringdata_NodeFtp = {
    {
QT_MOC_LITERAL(0, 0, 7), // "NodeFtp"
QT_MOC_LITERAL(1, 8, 13), // "memoryChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "memory"
QT_MOC_LITERAL(4, 30, 16), // "frequencyChanged"
QT_MOC_LITERAL(5, 47, 9), // "frequency"
QT_MOC_LITERAL(6, 57, 22), // "downloadPercentChanged"
QT_MOC_LITERAL(7, 80, 7), // "percent"
QT_MOC_LITERAL(8, 88, 15), // "finishedFtpWork"
QT_MOC_LITERAL(9, 104, 7), // "ftpWork"
QT_MOC_LITERAL(10, 112, 5), // "error"
QT_MOC_LITERAL(11, 118, 11), // "noteChanged"
QT_MOC_LITERAL(12, 130, 4), // "note"
QT_MOC_LITERAL(13, 135, 9), // "startWork"
QT_MOC_LITERAL(14, 145, 5), // "ftpWk"
QT_MOC_LITERAL(15, 151, 3), // "arg"
QT_MOC_LITERAL(16, 155, 8), // "stopWork"
QT_MOC_LITERAL(17, 164, 14), // "startTimerInfo"
QT_MOC_LITERAL(18, 179, 19), // "slotCommandFinished"
QT_MOC_LITERAL(19, 199, 12), // "slotListInfo"
QT_MOC_LITERAL(20, 212, 8) // "QUrlInfo"

    },
    "NodeFtp\0memoryChanged\0\0memory\0"
    "frequencyChanged\0frequency\0"
    "downloadPercentChanged\0percent\0"
    "finishedFtpWork\0ftpWork\0error\0noteChanged\0"
    "note\0startWork\0ftpWk\0arg\0stopWork\0"
    "startTimerInfo\0slotCommandFinished\0"
    "slotListInfo\0QUrlInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NodeFtp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       8,    2,   78,    2, 0x06 /* Public */,
       8,    1,   83,    2, 0x26 /* Public | MethodCloned */,
      11,    1,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    2,   89,    2, 0x0a /* Public */,
      16,    0,   94,    2, 0x0a /* Public */,
      17,    3,   95,    2, 0x0a /* Public */,
      18,    2,  102,    2, 0x08 /* Private */,
      19,    1,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    9,   10,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, 0x80000000 | 20,    2,

       0        // eod
};

void NodeFtp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NodeFtp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->memoryChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->frequencyChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->downloadPercentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->finishedFtpWork((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->finishedFtpWork((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->noteChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->startWork((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 7: _t->stopWork(); break;
        case 8: _t->startTimerInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 9: _t->slotCommandFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->slotListInfo((*reinterpret_cast< QUrlInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NodeFtp::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeFtp::memoryChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NodeFtp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeFtp::frequencyChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NodeFtp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeFtp::downloadPercentChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NodeFtp::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeFtp::finishedFtpWork)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NodeFtp::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NodeFtp::noteChanged)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NodeFtp::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_NodeFtp.data,
    qt_meta_data_NodeFtp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NodeFtp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NodeFtp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NodeFtp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NodeFtp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void NodeFtp::memoryChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NodeFtp::frequencyChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NodeFtp::downloadPercentChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NodeFtp::finishedFtpWork(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 5
void NodeFtp::noteChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
