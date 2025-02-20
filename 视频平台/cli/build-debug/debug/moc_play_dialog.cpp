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
    QByteArrayData data[60];
    char stringdata0[885];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Play_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Play_Dialog_t qt_meta_stringdata_Play_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Play_Dialog"
QT_MOC_LITERAL(1, 12, 15), // "sig_Uploadfile2"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "Hobby"
QT_MOC_LITERAL(4, 35, 18), // "sig_upload_process"
QT_MOC_LITERAL(5, 54, 14), // "sig_up_success"
QT_MOC_LITERAL(6, 69, 12), // "sig_play_end"
QT_MOC_LITERAL(7, 82, 12), // "sig_Download"
QT_MOC_LITERAL(8, 95, 6), // "FileId"
QT_MOC_LITERAL(9, 102, 19), // "sig_play_media_Name"
QT_MOC_LITERAL(10, 122, 16), // "sig_play_history"
QT_MOC_LITERAL(11, 139, 25), // "sig_comment_media_content"
QT_MOC_LITERAL(12, 165, 7), // "content"
QT_MOC_LITERAL(13, 173, 7), // "file_id"
QT_MOC_LITERAL(14, 181, 24), // "sig_comment_media_sucess"
QT_MOC_LITERAL(15, 206, 15), // "sig_get_comment"
QT_MOC_LITERAL(16, 222, 8), // "m_FileId"
QT_MOC_LITERAL(17, 231, 13), // "sig_close_win"
QT_MOC_LITERAL(18, 245, 14), // "sig_get_recomm"
QT_MOC_LITERAL(19, 260, 14), // "slot_set_Plike"
QT_MOC_LITERAL(20, 275, 20), // "on_pl_button_clicked"
QT_MOC_LITERAL(21, 296, 11), // "sig_sendimg"
QT_MOC_LITERAL(22, 308, 3), // "img"
QT_MOC_LITERAL(23, 312, 20), // "on_pb_resume_clicked"
QT_MOC_LITERAL(24, 333, 14), // "slot_play_auto"
QT_MOC_LITERAL(25, 348, 4), // "path"
QT_MOC_LITERAL(26, 353, 21), // "slot_Download_success"
QT_MOC_LITERAL(27, 375, 19), // "on_pb_pause_clicked"
QT_MOC_LITERAL(28, 395, 12), // "slot_history"
QT_MOC_LITERAL(29, 408, 18), // "on_pb_stop_clicked"
QT_MOC_LITERAL(30, 427, 25), // "slot_comment_media_sucess"
QT_MOC_LITERAL(31, 453, 23), // "slot_PlayerStateChanged"
QT_MOC_LITERAL(32, 477, 5), // "state"
QT_MOC_LITERAL(33, 483, 17), // "slot_getTotalTime"
QT_MOC_LITERAL(34, 501, 4), // "uSec"
QT_MOC_LITERAL(35, 506, 17), // "slot_TimerTimeOut"
QT_MOC_LITERAL(36, 524, 16), // "slot_set_comment"
QT_MOC_LITERAL(37, 541, 4), // "name"
QT_MOC_LITERAL(38, 546, 4), // "time"
QT_MOC_LITERAL(39, 551, 7), // "comment"
QT_MOC_LITERAL(40, 559, 11), // "eventFilter"
QT_MOC_LITERAL(41, 571, 3), // "obj"
QT_MOC_LITERAL(42, 575, 7), // "QEvent*"
QT_MOC_LITERAL(43, 583, 3), // "eve"
QT_MOC_LITERAL(44, 587, 17), // "on_pb_url_clicked"
QT_MOC_LITERAL(45, 605, 22), // "on_pb_recorder_clicked"
QT_MOC_LITERAL(46, 628, 20), // "on_pb_upload_clicked"
QT_MOC_LITERAL(47, 649, 17), // "on_pb_pre_clicked"
QT_MOC_LITERAL(48, 667, 18), // "on_pb_next_clicked"
QT_MOC_LITERAL(49, 686, 18), // "on_pb_play_clicked"
QT_MOC_LITERAL(50, 705, 22), // "on_pb_download_clicked"
QT_MOC_LITERAL(51, 728, 21), // "on_pb_history_clicked"
QT_MOC_LITERAL(52, 750, 21), // "on_pb_comment_clicked"
QT_MOC_LITERAL(53, 772, 23), // "on_pb_recommend_clicked"
QT_MOC_LITERAL(54, 796, 18), // "on_pb_like_clicked"
QT_MOC_LITERAL(55, 815, 10), // "closeEvent"
QT_MOC_LITERAL(56, 826, 12), // "QCloseEvent*"
QT_MOC_LITERAL(57, 839, 5), // "event"
QT_MOC_LITERAL(58, 845, 20), // "on_pb_cllike_clicked"
QT_MOC_LITERAL(59, 866, 18) // "on_pb_icon_clicked"

    },
    "Play_Dialog\0sig_Uploadfile2\0\0Hobby\0"
    "sig_upload_process\0sig_up_success\0"
    "sig_play_end\0sig_Download\0FileId\0"
    "sig_play_media_Name\0sig_play_history\0"
    "sig_comment_media_content\0content\0"
    "file_id\0sig_comment_media_sucess\0"
    "sig_get_comment\0m_FileId\0sig_close_win\0"
    "sig_get_recomm\0slot_set_Plike\0"
    "on_pl_button_clicked\0sig_sendimg\0img\0"
    "on_pb_resume_clicked\0slot_play_auto\0"
    "path\0slot_Download_success\0"
    "on_pb_pause_clicked\0slot_history\0"
    "on_pb_stop_clicked\0slot_comment_media_sucess\0"
    "slot_PlayerStateChanged\0state\0"
    "slot_getTotalTime\0uSec\0slot_TimerTimeOut\0"
    "slot_set_comment\0name\0time\0comment\0"
    "eventFilter\0obj\0QEvent*\0eve\0"
    "on_pb_url_clicked\0on_pb_recorder_clicked\0"
    "on_pb_upload_clicked\0on_pb_pre_clicked\0"
    "on_pb_next_clicked\0on_pb_play_clicked\0"
    "on_pb_download_clicked\0on_pb_history_clicked\0"
    "on_pb_comment_clicked\0on_pb_recommend_clicked\0"
    "on_pb_like_clicked\0closeEvent\0"
    "QCloseEvent*\0event\0on_pb_cllike_clicked\0"
    "on_pb_icon_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Play_Dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  219,    2, 0x06 /* Public */,
       4,    2,  224,    2, 0x06 /* Public */,
       5,    0,  229,    2, 0x06 /* Public */,
       6,    0,  230,    2, 0x06 /* Public */,
       7,    1,  231,    2, 0x06 /* Public */,
       9,    1,  234,    2, 0x06 /* Public */,
      10,    1,  237,    2, 0x06 /* Public */,
      11,    2,  240,    2, 0x06 /* Public */,
      14,    0,  245,    2, 0x06 /* Public */,
      15,    1,  246,    2, 0x06 /* Public */,
      17,    0,  249,    2, 0x06 /* Public */,
      18,    0,  250,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,  251,    2, 0x08 /* Private */,
      20,    0,  252,    2, 0x08 /* Private */,
      21,    1,  253,    2, 0x08 /* Private */,
      23,    0,  256,    2, 0x08 /* Private */,
      24,    2,  257,    2, 0x08 /* Private */,
      26,    0,  262,    2, 0x08 /* Private */,
      27,    0,  263,    2, 0x08 /* Private */,
      28,    0,  264,    2, 0x08 /* Private */,
      29,    0,  265,    2, 0x08 /* Private */,
      30,    0,  266,    2, 0x08 /* Private */,
      31,    1,  267,    2, 0x08 /* Private */,
      33,    1,  270,    2, 0x08 /* Private */,
      35,    0,  273,    2, 0x08 /* Private */,
      36,    3,  274,    2, 0x08 /* Private */,
      40,    2,  281,    2, 0x08 /* Private */,
      44,    0,  286,    2, 0x08 /* Private */,
      45,    0,  287,    2, 0x08 /* Private */,
      46,    0,  288,    2, 0x08 /* Private */,
      47,    0,  289,    2, 0x08 /* Private */,
      48,    0,  290,    2, 0x08 /* Private */,
      49,    0,  291,    2, 0x08 /* Private */,
      50,    0,  292,    2, 0x08 /* Private */,
      51,    0,  293,    2, 0x08 /* Private */,
      52,    0,  294,    2, 0x08 /* Private */,
      53,    0,  295,    2, 0x08 /* Private */,
      54,    0,  296,    2, 0x08 /* Private */,
      55,    1,  297,    2, 0x08 /* Private */,
      58,    0,  300,    2, 0x08 /* Private */,
      59,    0,  301,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   25,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::LongLong,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   37,   38,   39,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 42,   41,   43,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Play_Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Play_Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_Uploadfile2((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< Hobby(*)>(_a[2]))); break;
        case 1: _t->sig_upload_process((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->sig_up_success(); break;
        case 3: _t->sig_play_end(); break;
        case 4: _t->sig_Download((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sig_play_media_Name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sig_play_history((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->sig_comment_media_content((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->sig_comment_media_sucess(); break;
        case 9: _t->sig_get_comment((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->sig_close_win(); break;
        case 11: _t->sig_get_recomm(); break;
        case 12: _t->slot_set_Plike(); break;
        case 13: _t->on_pl_button_clicked(); break;
        case 14: _t->sig_sendimg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 15: _t->on_pb_resume_clicked(); break;
        case 16: _t->slot_play_auto((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->slot_Download_success(); break;
        case 18: _t->on_pb_pause_clicked(); break;
        case 19: _t->slot_history(); break;
        case 20: _t->on_pb_stop_clicked(); break;
        case 21: _t->slot_comment_media_sucess(); break;
        case 22: _t->slot_PlayerStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->slot_getTotalTime((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 24: _t->slot_TimerTimeOut(); break;
        case 25: _t->slot_set_comment((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 26: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->on_pb_url_clicked(); break;
        case 28: _t->on_pb_recorder_clicked(); break;
        case 29: _t->on_pb_upload_clicked(); break;
        case 30: _t->on_pb_pre_clicked(); break;
        case 31: _t->on_pb_next_clicked(); break;
        case 32: _t->on_pb_play_clicked(); break;
        case 33: _t->on_pb_download_clicked(); break;
        case 34: _t->on_pb_history_clicked(); break;
        case 35: _t->on_pb_comment_clicked(); break;
        case 36: _t->on_pb_recommend_clicked(); break;
        case 37: _t->on_pb_like_clicked(); break;
        case 38: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 39: _t->on_pb_cllike_clicked(); break;
        case 40: _t->on_pb_icon_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Play_Dialog::*)(QString , Hobby );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_Uploadfile2)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_upload_process)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_up_success)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_play_end)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_Download)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_play_media_Name)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_play_history)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_comment_media_content)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_comment_media_sucess)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_get_comment)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_close_win)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Play_Dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Play_Dialog::sig_get_recomm)) {
                *result = 11;
                return;
            }
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
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void Play_Dialog::sig_Uploadfile2(QString _t1, Hobby _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Play_Dialog::sig_upload_process(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Play_Dialog::sig_up_success()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Play_Dialog::sig_play_end()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Play_Dialog::sig_Download(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Play_Dialog::sig_play_media_Name(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Play_Dialog::sig_play_history(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Play_Dialog::sig_comment_media_content(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Play_Dialog::sig_comment_media_sucess()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Play_Dialog::sig_get_comment(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Play_Dialog::sig_close_win()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void Play_Dialog::sig_get_recomm()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
