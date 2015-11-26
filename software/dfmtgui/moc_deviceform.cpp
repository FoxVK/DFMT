/****************************************************************************
** Meta object code from reading C++ file 'deviceform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "deviceform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deviceform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DeviceForm_t {
    QByteArrayData data[25];
    char stringdata[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DeviceForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DeviceForm_t qt_meta_stringdata_DeviceForm = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 6),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 4),
QT_MOC_LITERAL(4, 24, 14),
QT_MOC_LITERAL(5, 39, 11),
QT_MOC_LITERAL(6, 51, 5),
QT_MOC_LITERAL(7, 57, 2),
QT_MOC_LITERAL(8, 60, 18),
QT_MOC_LITERAL(9, 79, 18),
QT_MOC_LITERAL(10, 98, 12),
QT_MOC_LITERAL(11, 111, 5),
QT_MOC_LITERAL(12, 117, 12),
QT_MOC_LITERAL(13, 130, 12),
QT_MOC_LITERAL(14, 143, 4),
QT_MOC_LITERAL(15, 148, 3),
QT_MOC_LITERAL(16, 152, 5),
QT_MOC_LITERAL(17, 158, 15),
QT_MOC_LITERAL(18, 174, 9),
QT_MOC_LITERAL(19, 184, 8),
QT_MOC_LITERAL(20, 193, 11),
QT_MOC_LITERAL(21, 205, 6),
QT_MOC_LITERAL(22, 212, 16),
QT_MOC_LITERAL(23, 229, 6),
QT_MOC_LITERAL(24, 236, 6)
    },
    "DeviceForm\0tune_A\0\0freq\0seek_forward_A\0"
    "seek_back_A\0sound\0on\0freq_chk_trm_fired\0"
    "freq_chg_tmr_fired\0slider_moved\0value\0"
    "freq_changed\0freq_cangedB\0rssi\0snr\0"
    "valid\0metrics_changed\0multipath\0"
    "is_valid\0freq_offset\0stereo\0"
    "metrics_changedB\0task_A\0task_B\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08,
       4,    0,   87,    2, 0x08,
       5,    0,   88,    2, 0x08,
       6,    1,   89,    2, 0x08,
       6,    0,   92,    2, 0x28,
       8,    0,   93,    2, 0x08,
       9,    0,   94,    2, 0x08,
      10,    1,   95,    2, 0x08,
      12,    1,   98,    2, 0x08,
      13,    4,  101,    2, 0x08,
      17,    6,  110,    2, 0x08,
      22,    6,  123,    2, 0x08,
      23,    0,  136,    2, 0x08,
      24,    0,  137,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool,    3,   14,   15,   16,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool, QMetaType::Int, QMetaType::UInt,   14,   15,   18,   19,   20,   21,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool, QMetaType::Int, QMetaType::UInt,   14,   15,   18,   19,   20,   21,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DeviceForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeviceForm *_t = static_cast<DeviceForm *>(_o);
        switch (_id) {
        case 0: _t->tune_A((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->seek_forward_A(); break;
        case 2: _t->seek_back_A(); break;
        case 3: _t->sound((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->sound(); break;
        case 5: _t->freq_chk_trm_fired(); break;
        case 6: _t->freq_chg_tmr_fired(); break;
        case 7: _t->slider_moved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->freq_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->freq_cangedB((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 10: _t->metrics_changed((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 11: _t->metrics_changedB((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 12: _t->task_A(); break;
        case 13: _t->task_B(); break;
        default: ;
        }
    }
}

const QMetaObject DeviceForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DeviceForm.data,
      qt_meta_data_DeviceForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *DeviceForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceForm.stringdata))
        return static_cast<void*>(const_cast< DeviceForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int DeviceForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
