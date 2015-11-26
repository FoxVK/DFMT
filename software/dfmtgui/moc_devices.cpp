/****************************************************************************
** Meta object code from reading C++ file 'devices.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "devices.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Devices_t {
    QByteArrayData data[9];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Devices_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Devices_t qt_meta_stringdata_Devices = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 13),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 7),
QT_MOC_LITERAL(4, 31, 3),
QT_MOC_LITERAL(5, 35, 15),
QT_MOC_LITERAL(6, 51, 4),
QT_MOC_LITERAL(7, 56, 17),
QT_MOC_LITERAL(8, 74, 4)
    },
    "Devices\0dev_connected\0\0Device*\0dev\0"
    "dev_diconnected\0scan\0set_scan_interval\0"
    "msec\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Devices[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06,
       5,    1,   42,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x0a,
       7,    1,   46,    2, 0x0a,
       7,    0,   49,    2, 0x2a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,

       0        // eod
};

void Devices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Devices *_t = static_cast<Devices *>(_o);
        switch (_id) {
        case 0: _t->dev_connected((*reinterpret_cast< Device*(*)>(_a[1]))); break;
        case 1: _t->dev_diconnected((*reinterpret_cast< Device*(*)>(_a[1]))); break;
        case 2: _t->scan(); break;
        case 3: _t->set_scan_interval((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->set_scan_interval(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Devices::*_t)(Device * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Devices::dev_connected)) {
                *result = 0;
            }
        }
        {
            typedef void (Devices::*_t)(Device * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Devices::dev_diconnected)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Devices::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Devices.data,
      qt_meta_data_Devices,  qt_static_metacall, 0, 0}
};


const QMetaObject *Devices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Devices::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Devices.stringdata))
        return static_cast<void*>(const_cast< Devices*>(this));
    return QObject::qt_metacast(_clname);
}

int Devices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Devices::dev_connected(Device * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Devices::dev_diconnected(Device * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
