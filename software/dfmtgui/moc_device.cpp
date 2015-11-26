/****************************************************************************
** Meta object code from reading C++ file 'device.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "device.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'device.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Device_t {
    QByteArrayData data[22];
    char stringdata[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Device_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Device_t qt_meta_stringdata_Device = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 17),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 4),
QT_MOC_LITERAL(4, 31, 17),
QT_MOC_LITERAL(5, 49, 4),
QT_MOC_LITERAL(6, 54, 3),
QT_MOC_LITERAL(7, 58, 5),
QT_MOC_LITERAL(8, 64, 12),
QT_MOC_LITERAL(9, 77, 9),
QT_MOC_LITERAL(10, 87, 8),
QT_MOC_LITERAL(11, 96, 11),
QT_MOC_LITERAL(12, 108, 6),
QT_MOC_LITERAL(13, 115, 12),
QT_MOC_LITERAL(14, 128, 4),
QT_MOC_LITERAL(15, 133, 5),
QT_MOC_LITERAL(16, 139, 5),
QT_MOC_LITERAL(17, 145, 8),
QT_MOC_LITERAL(18, 154, 4),
QT_MOC_LITERAL(19, 159, 2),
QT_MOC_LITERAL(20, 162, 13),
QT_MOC_LITERAL(21, 176, 10)
    },
    "Device\0freq_tunA_changed\0\0freq\0"
    "freq_tunB_changed\0rssi\0snr\0valid\0"
    "tunA_metrics\0multipath\0is_valid\0"
    "freq_offset\0stereo\0tunB_metrics\0tune\0"
    "Tuner\0tuner\0freq_mhz\0seek\0up\0check_metrics\0"
    "check_freq\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Device[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06,
       4,    4,   67,    2, 0x06,
       8,    6,   76,    2, 0x06,
      13,    6,   89,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      14,    2,  102,    2, 0x0a,
      18,    2,  107,    2, 0x0a,
      20,    1,  112,    2, 0x0a,
      20,    0,  115,    2, 0x2a,
      21,    1,  116,    2, 0x0a,
      21,    0,  119,    2, 0x2a,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool,    3,    5,    6,    7,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool, QMetaType::Int, QMetaType::UInt,    5,    6,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool, QMetaType::Int, QMetaType::UInt,    5,    6,    9,   10,   11,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15, QMetaType::Double,   16,   17,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Bool,   16,   19,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,

       0        // eod
};

void Device::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Device *_t = static_cast<Device *>(_o);
        switch (_id) {
        case 0: _t->freq_tunA_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->freq_tunB_changed((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: _t->tunA_metrics((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 3: _t->tunB_metrics((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 4: _t->tune((*reinterpret_cast< Tuner(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->seek((*reinterpret_cast< Tuner(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->check_metrics((*reinterpret_cast< Tuner(*)>(_a[1]))); break;
        case 7: _t->check_metrics(); break;
        case 8: _t->check_freq((*reinterpret_cast< Tuner(*)>(_a[1]))); break;
        case 9: _t->check_freq(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Device::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Device::freq_tunA_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (Device::*_t)(double , unsigned  , unsigned  , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Device::freq_tunB_changed)) {
                *result = 1;
            }
        }
        {
            typedef void (Device::*_t)(unsigned  , unsigned  , unsigned  , bool , int , unsigned  );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Device::tunA_metrics)) {
                *result = 2;
            }
        }
        {
            typedef void (Device::*_t)(unsigned  , unsigned  , unsigned  , bool , int , unsigned  );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Device::tunB_metrics)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject Device::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Device.data,
      qt_meta_data_Device,  qt_static_metacall, 0, 0}
};


const QMetaObject *Device::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Device::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Device.stringdata))
        return static_cast<void*>(const_cast< Device*>(this));
    return QObject::qt_metacast(_clname);
}

int Device::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Device::freq_tunA_changed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Device::freq_tunB_changed(double _t1, unsigned  _t2, unsigned  _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Device::tunA_metrics(unsigned  _t1, unsigned  _t2, unsigned  _t3, bool _t4, int _t5, unsigned  _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Device::tunB_metrics(unsigned  _t1, unsigned  _t2, unsigned  _t3, bool _t4, int _t5, unsigned  _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
