/****************************************************************************
** Meta object code from reading C++ file 'vedio_play.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vedio_play.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vedio_play.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Vedio_play_t {
    QByteArrayData data[10];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vedio_play_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vedio_play_t qt_meta_stringdata_Vedio_play = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Vedio_play"
QT_MOC_LITERAL(1, 11, 11), // "sig_sendimg"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "img"
QT_MOC_LITERAL(4, 28, 22), // "SIG_PlayerStateChanged"
QT_MOC_LITERAL(5, 51, 4), // "flag"
QT_MOC_LITERAL(6, 56, 13), // "SIG_TotalTime"
QT_MOC_LITERAL(7, 70, 4), // "uSec"
QT_MOC_LITERAL(8, 75, 15), // "SendGetOneImage"
QT_MOC_LITERAL(9, 91, 7) // "QImage&"

    },
    "Vedio_play\0sig_sendimg\0\0img\0"
    "SIG_PlayerStateChanged\0flag\0SIG_TotalTime\0"
    "uSec\0SendGetOneImage\0QImage&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vedio_play[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::LongLong,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,    3,

       0        // eod
};

void Vedio_play::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Vedio_play *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_sendimg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->SIG_PlayerStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SIG_TotalTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->SendGetOneImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Vedio_play::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vedio_play::sig_sendimg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Vedio_play::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vedio_play::SIG_PlayerStateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Vedio_play::*)(qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vedio_play::SIG_TotalTime)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Vedio_play::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_Vedio_play.data,
    qt_meta_data_Vedio_play,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Vedio_play::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vedio_play::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Vedio_play.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Vedio_play::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Vedio_play::sig_sendimg(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Vedio_play::SIG_PlayerStateChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Vedio_play::SIG_TotalTime(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
