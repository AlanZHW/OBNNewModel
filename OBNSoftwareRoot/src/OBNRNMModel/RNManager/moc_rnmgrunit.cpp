/****************************************************************************
** Meta object code from reading C++ file 'rnmgrunit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rnmgrunit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rnmgrunit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RNMMenuManager_t {
    QByteArrayData data[6];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RNMMenuManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RNMMenuManager_t qt_meta_stringdata_RNMMenuManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RNMMenuManager"
QT_MOC_LITERAL(1, 15, 27), // "signalUpdateIntervalChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 8), // "interval"
QT_MOC_LITERAL(4, 53, 25), // "slotUpdateIntervalChanged"
QT_MOC_LITERAL(5, 79, 16) // "QAbstractButton*"

    },
    "RNMMenuManager\0signalUpdateIntervalChanged\0"
    "\0interval\0slotUpdateIntervalChanged\0"
    "QAbstractButton*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RNMMenuManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void RNMMenuManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RNMMenuManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateIntervalChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->slotUpdateIntervalChanged((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RNMMenuManager::*)(const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RNMMenuManager::signalUpdateIntervalChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RNMMenuManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_RNMMenuManager.data,
    qt_meta_data_RNMMenuManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RNMMenuManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RNMMenuManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RNMMenuManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RNMMenuManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void RNMMenuManager::signalUpdateIntervalChanged(const int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_RNMToolManager_t {
    QByteArrayData data[12];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RNMToolManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RNMToolManager_t qt_meta_stringdata_RNMToolManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RNMToolManager"
QT_MOC_LITERAL(1, 15, 27), // "signalUpdateIntervalChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 8), // "interval"
QT_MOC_LITERAL(4, 53, 23), // "signalStartOrStopUpdate"
QT_MOC_LITERAL(5, 77, 5), // "start"
QT_MOC_LITERAL(6, 83, 16), // "signalSearchNode"
QT_MOC_LITERAL(7, 100, 4), // "node"
QT_MOC_LITERAL(8, 105, 21), // "slotSetUpdateInterval"
QT_MOC_LITERAL(9, 127, 4), // "text"
QT_MOC_LITERAL(10, 132, 21), // "slotStartOrStopUpdate"
QT_MOC_LITERAL(11, 154, 14) // "slotSearchNode"

    },
    "RNMToolManager\0signalUpdateIntervalChanged\0"
    "\0interval\0signalStartOrStopUpdate\0"
    "start\0signalSearchNode\0node\0"
    "slotSetUpdateInterval\0text\0"
    "slotStartOrStopUpdate\0slotSearchNode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RNMToolManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   53,    2, 0x08 /* Private */,
      10,    0,   56,    2, 0x08 /* Private */,
      11,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::UInt,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RNMToolManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RNMToolManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalUpdateIntervalChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->signalStartOrStopUpdate((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: _t->signalSearchNode((*reinterpret_cast< const uint(*)>(_a[1]))); break;
        case 3: _t->slotSetUpdateInterval((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slotStartOrStopUpdate(); break;
        case 5: _t->slotSearchNode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RNMToolManager::*)(const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RNMToolManager::signalUpdateIntervalChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RNMToolManager::*)(const bool & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RNMToolManager::signalStartOrStopUpdate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RNMToolManager::*)(const uint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RNMToolManager::signalSearchNode)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RNMToolManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_RNMToolManager.data,
    qt_meta_data_RNMToolManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RNMToolManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RNMToolManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RNMToolManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RNMToolManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void RNMToolManager::signalUpdateIntervalChanged(const int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RNMToolManager::signalStartOrStopUpdate(const bool & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RNMToolManager::signalSearchNode(const uint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_SearchIpDialog_t {
    QByteArrayData data[13];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchIpDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchIpDialog_t qt_meta_stringdata_SearchIpDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SearchIpDialog"
QT_MOC_LITERAL(1, 15, 12), // "displayNodes"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "QVector<Node*>"
QT_MOC_LITERAL(4, 44, 5), // "nodes"
QT_MOC_LITERAL(5, 50, 13), // "checkLcHostIP"
QT_MOC_LITERAL(6, 64, 20), // "slotSearchBtnClicked"
QT_MOC_LITERAL(7, 85, 16), // "slotDisplayNodes"
QT_MOC_LITERAL(8, 102, 16), // "slotSearchedHost"
QT_MOC_LITERAL(9, 119, 5), // "index"
QT_MOC_LITERAL(10, 125, 9), // "available"
QT_MOC_LITERAL(11, 135, 18), // "slotThreadFinished"
QT_MOC_LITERAL(12, 154, 2) // "id"

    },
    "SearchIpDialog\0displayNodes\0\0"
    "QVector<Node*>\0nodes\0checkLcHostIP\0"
    "slotSearchBtnClicked\0slotDisplayNodes\0"
    "slotSearchedHost\0index\0available\0"
    "slotThreadFinished\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchIpDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,
       8,    2,   50,    2, 0x08 /* Private */,
      11,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::Bool,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void SearchIpDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SearchIpDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayNodes((*reinterpret_cast< const QVector<Node*>(*)>(_a[1]))); break;
        case 1: _t->checkLcHostIP(); break;
        case 2: _t->slotSearchBtnClicked(); break;
        case 3: _t->slotDisplayNodes(); break;
        case 4: _t->slotSearchedHost((*reinterpret_cast< const quint32(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 5: _t->slotThreadFinished((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<Node*> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchIpDialog::*)(const QVector<Node*> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchIpDialog::displayNodes)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SearchIpDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SearchIpDialog.data,
    qt_meta_data_SearchIpDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SearchIpDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchIpDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SearchIpDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SearchIpDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SearchIpDialog::displayNodes(const QVector<Node*> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_LimitsDialog_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LimitsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LimitsDialog_t qt_meta_stringdata_LimitsDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LimitsDialog"
QT_MOC_LITERAL(1, 13, 13), // "limitsChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 18), // "QVector<LimitData>"
QT_MOC_LITERAL(4, 47, 16), // "cancelBtnClicked"
QT_MOC_LITERAL(5, 64, 12) // "okBtnClicked"

    },
    "LimitsDialog\0limitsChanged\0\0"
    "QVector<LimitData>\0cancelBtnClicked\0"
    "okBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LimitsDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LimitsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LimitsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->limitsChanged((*reinterpret_cast< const QVector<LimitData>(*)>(_a[1]))); break;
        case 1: _t->cancelBtnClicked(); break;
        case 2: _t->okBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LimitsDialog::*)(const QVector<LimitData> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LimitsDialog::limitsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LimitsDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_LimitsDialog.data,
    qt_meta_data_LimitsDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LimitsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LimitsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LimitsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int LimitsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void LimitsDialog::limitsChanged(const QVector<LimitData> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
