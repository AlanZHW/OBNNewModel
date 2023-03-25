/****************************************************************************
** Meta object code from reading C++ file 'rnftpmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rnftpmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rnftpmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RNFtpManager_t {
    QByteArrayData data[16];
    char stringdata0[310];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RNFtpManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RNFtpManager_t qt_meta_stringdata_RNFtpManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RNFtpManager"
QT_MOC_LITERAL(1, 13, 22), // "on_downloadBtn_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 25), // "on_stopCurrentBtn_clicked"
QT_MOC_LITERAL(4, 63, 22), // "on_clearMemBtn_clicked"
QT_MOC_LITERAL(5, 86, 27), // "on_setSampleFreqBtn_clicked"
QT_MOC_LITERAL(6, 114, 21), // "on_refreshBtn_clicked"
QT_MOC_LITERAL(7, 136, 19), // "on_closeBtn_clicked"
QT_MOC_LITERAL(8, 156, 20), // "on_brwserBtn_clicked"
QT_MOC_LITERAL(9, 177, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(10, 197, 7), // "checked"
QT_MOC_LITERAL(11, 205, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(12, 229, 4), // "arg1"
QT_MOC_LITERAL(13, 234, 24), // "on_timePeriodCbx_toggled"
QT_MOC_LITERAL(14, 259, 30), // "on_comboBox_currentTextChanged"
QT_MOC_LITERAL(15, 290, 19) // "on_clearBtn_clicked"

    },
    "RNFtpManager\0on_downloadBtn_clicked\0"
    "\0on_stopCurrentBtn_clicked\0"
    "on_clearMemBtn_clicked\0"
    "on_setSampleFreqBtn_clicked\0"
    "on_refreshBtn_clicked\0on_closeBtn_clicked\0"
    "on_brwserBtn_clicked\0on_checkBox_clicked\0"
    "checked\0on_spinBox_valueChanged\0arg1\0"
    "on_timePeriodCbx_toggled\0"
    "on_comboBox_currentTextChanged\0"
    "on_clearBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RNFtpManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    1,   81,    2, 0x08 /* Private */,
      11,    1,   84,    2, 0x08 /* Private */,
      13,    1,   87,    2, 0x08 /* Private */,
      14,    1,   90,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,

       0        // eod
};

void RNFtpManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RNFtpManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_downloadBtn_clicked(); break;
        case 1: _t->on_stopCurrentBtn_clicked(); break;
        case 2: _t->on_clearMemBtn_clicked(); break;
        case 3: _t->on_setSampleFreqBtn_clicked(); break;
        case 4: _t->on_refreshBtn_clicked(); break;
        case 5: _t->on_closeBtn_clicked(); break;
        case 6: _t->on_brwserBtn_clicked(); break;
        case 7: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_timePeriodCbx_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_comboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_clearBtn_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RNFtpManager::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_RNFtpManager.data,
    qt_meta_data_RNFtpManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RNFtpManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RNFtpManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RNFtpManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RNFtpManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
