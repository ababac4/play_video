/****************************************************************************
** Meta object code from reading C++ file 'play_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../play_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'play_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Play_Dialog_t {
    QByteArrayData data[21];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Play_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Play_Dialog_t qt_meta_stringdata_Play_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Play_Dialog"
QT_MOC_LITERAL(1, 12, 20), // "on_pl_button_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "sig_sendimg"
QT_MOC_LITERAL(4, 46, 3), // "img"
QT_MOC_LITERAL(5, 50, 20), // "on_pb_resume_clicked"
QT_MOC_LITERAL(6, 71, 19), // "on_pb_pause_clicked"
QT_MOC_LITERAL(7, 91, 18), // "on_pb_stop_clicked"
QT_MOC_LITERAL(8, 110, 23), // "slot_PlayerStateChanged"
QT_MOC_LITERAL(9, 134, 5), // "state"
QT_MOC_LITERAL(10, 140, 17), // "slot_getTotalTime"
QT_MOC_LITERAL(11, 158, 4), // "uSec"
QT_MOC_LITERAL(12, 163, 17), // "slot_TimerTimeOut"
QT_MOC_LITERAL(13, 181, 11), // "eventFilter"
QT_MOC_LITERAL(14, 193, 3), // "obj"
QT_MOC_LITERAL(15, 197, 7), // "QEvent*"
QT_MOC_LITERAL(16, 205, 3), // "eve"
QT_MOC_LITERAL(17, 209, 17), // "on_pb_url_clicked"
QT_MOC_LITERAL(18, 227, 10), // "closeEvent"
QT_MOC_LITERAL(19, 238, 12), // "QCloseEvent*"
QT_MOC_LITERAL(20, 251, 5) // "event"

    },
    "Play_Dialog\0on_pl_button_clicked\0\0"
    "sig_sendimg\0img\0on_pb_resume_clicked\0"
    "on_pb_pause_clicked\0on_pb_stop_clicked\0"
    "slot_PlayerStateChanged\0state\0"
    "slot_getTotalTime\0uSec\0slot_TimerTimeOut\0"
    "eventFilter\0obj\0QEvent*\0eve\0"
    "on_pb_url_clicked\0closeEvent\0QCloseEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Play_Dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    1,   70,    2, 0x08 /* Private */,
       5,    0,   73,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
      10,    1,   79,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    2,   83,    2, 0x08 /* Private */,
      17,    0,   88,    2, 0x08 /* Private */,
      18,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::LongLong,   11,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 15,   14,   16,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void Play_Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Play_Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pl_button_clicked(); break;
        case 1: _t->sig_sendimg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->on_pb_resume_clicked(); break;
        case 3: _t->on_pb_pause_clicked(); break;
        case 4: _t->on_pb_stop_clicked(); break;
        case 5: _t->slot_PlayerStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_getTotalTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->slot_TimerTimeOut(); break;
        case 8: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->on_pb_url_clicked(); break;
        case 10: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Play_Dialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Play_Dialog.data,
    qt_meta_data_Play_Dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Play_Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Play_Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Play_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Play_Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
