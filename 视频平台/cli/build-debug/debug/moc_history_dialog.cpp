/****************************************************************************
** Meta object code from reading C++ file 'history_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../history_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'history_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_history_dialog_t {
    QByteArrayData data[14];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_history_dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_history_dialog_t qt_meta_stringdata_history_dialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "history_dialog"
QT_MOC_LITERAL(1, 15, 13), // "sig_play_Name"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "name"
QT_MOC_LITERAL(4, 35, 22), // "on_pb_history1_clicked"
QT_MOC_LITERAL(5, 58, 24), // "on_pb_history1_2_clicked"
QT_MOC_LITERAL(6, 83, 24), // "on_pb_history1_3_clicked"
QT_MOC_LITERAL(7, 108, 24), // "on_pb_history1_4_clicked"
QT_MOC_LITERAL(8, 133, 24), // "on_pb_history1_5_clicked"
QT_MOC_LITERAL(9, 158, 24), // "on_pb_history1_6_clicked"
QT_MOC_LITERAL(10, 183, 12), // "slot_history"
QT_MOC_LITERAL(11, 196, 4), // "Name"
QT_MOC_LITERAL(12, 201, 2), // "id"
QT_MOC_LITERAL(13, 204, 20) // "on_pb_upgrad_clicked"

    },
    "history_dialog\0sig_play_Name\0\0name\0"
    "on_pb_history1_clicked\0on_pb_history1_2_clicked\0"
    "on_pb_history1_3_clicked\0"
    "on_pb_history1_4_clicked\0"
    "on_pb_history1_5_clicked\0"
    "on_pb_history1_6_clicked\0slot_history\0"
    "Name\0id\0on_pb_upgrad_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_history_dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   62,    2, 0x08 /* Private */,
       5,    0,   63,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    2,   68,    2, 0x08 /* Private */,
      13,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   11,   12,
    QMetaType::Void,

       0        // eod
};

void history_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<history_dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_play_Name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_pb_history1_clicked(); break;
        case 2: _t->on_pb_history1_2_clicked(); break;
        case 3: _t->on_pb_history1_3_clicked(); break;
        case 4: _t->on_pb_history1_4_clicked(); break;
        case 5: _t->on_pb_history1_5_clicked(); break;
        case 6: _t->on_pb_history1_6_clicked(); break;
        case 7: _t->slot_history((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->on_pb_upgrad_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (history_dialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&history_dialog::sig_play_Name)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject history_dialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_history_dialog.data,
    qt_meta_data_history_dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *history_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *history_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_history_dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int history_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void history_dialog::sig_play_Name(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
