/****************************************************************************
** Meta object code from reading C++ file 'savevideothread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../savevideothread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'savevideothread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_savevideothread_t {
    QByteArrayData data[26];
    char stringdata0[345];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_savevideothread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_savevideothread_t qt_meta_stringdata_savevideothread = {
    {
QT_MOC_LITERAL(0, 0, 15), // "savevideothread"
QT_MOC_LITERAL(1, 16, 18), // "SIG_sendVideoFrame"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 3), // "img"
QT_MOC_LITERAL(4, 40, 16), // "SIG_sendPicInPic"
QT_MOC_LITERAL(5, 57, 24), // "Slot_writeVideoFrameData"
QT_MOC_LITERAL(6, 82, 8), // "uint8_t*"
QT_MOC_LITERAL(7, 91, 11), // "picture_buf"
QT_MOC_LITERAL(8, 103, 11), // "buffer_size"
QT_MOC_LITERAL(9, 115, 14), // "slot_openvideo"
QT_MOC_LITERAL(10, 130, 15), // "slot_closevideo"
QT_MOC_LITERAL(11, 146, 7), // "setinfo"
QT_MOC_LITERAL(12, 154, 15), // "STRU_AV_FORMAT&"
QT_MOC_LITERAL(13, 170, 9), // "av_format"
QT_MOC_LITERAL(14, 180, 24), // "Slot_writeaudioFrameData"
QT_MOC_LITERAL(15, 205, 20), // "videoDataQuene_Input"
QT_MOC_LITERAL(16, 226, 6), // "buffer"
QT_MOC_LITERAL(17, 233, 4), // "size"
QT_MOC_LITERAL(18, 238, 7), // "int64_t"
QT_MOC_LITERAL(19, 246, 4), // "time"
QT_MOC_LITERAL(20, 251, 18), // "videoDataQuene_get"
QT_MOC_LITERAL(21, 270, 15), // "BufferDataNode*"
QT_MOC_LITERAL(22, 286, 20), // "audioDataQuene_Input"
QT_MOC_LITERAL(23, 307, 14), // "const uint8_t*"
QT_MOC_LITERAL(24, 322, 18), // "audioDataQuene_get"
QT_MOC_LITERAL(25, 341, 3) // "run"

    },
    "savevideothread\0SIG_sendVideoFrame\0\0"
    "img\0SIG_sendPicInPic\0Slot_writeVideoFrameData\0"
    "uint8_t*\0picture_buf\0buffer_size\0"
    "slot_openvideo\0slot_closevideo\0setinfo\0"
    "STRU_AV_FORMAT&\0av_format\0"
    "Slot_writeaudioFrameData\0videoDataQuene_Input\0"
    "buffer\0size\0int64_t\0time\0videoDataQuene_get\0"
    "BufferDataNode*\0audioDataQuene_Input\0"
    "const uint8_t*\0audioDataQuene_get\0run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_savevideothread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   80,    2, 0x0a /* Public */,
       9,    0,   85,    2, 0x0a /* Public */,
      10,    0,   86,    2, 0x0a /* Public */,
      11,    1,   87,    2, 0x0a /* Public */,
      14,    2,   90,    2, 0x0a /* Public */,
      15,    3,   95,    2, 0x0a /* Public */,
      20,    1,  102,    2, 0x0a /* Public */,
      22,    2,  105,    2, 0x0a /* Public */,
      24,    0,  110,    2, 0x0a /* Public */,
      25,    0,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QImage,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 18,   16,   17,   19,
    0x80000000 | 21, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 23, QMetaType::Int,   16,   17,
    0x80000000 | 21,
    QMetaType::Void,

       0        // eod
};

void savevideothread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<savevideothread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_sendVideoFrame((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->SIG_sendPicInPic((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->Slot_writeVideoFrameData((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_openvideo(); break;
        case 4: _t->slot_closevideo(); break;
        case 5: _t->setinfo((*reinterpret_cast< STRU_AV_FORMAT(*)>(_a[1]))); break;
        case 6: _t->Slot_writeaudioFrameData((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->videoDataQuene_Input((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int64_t(*)>(_a[3]))); break;
        case 8: { BufferDataNode* _r = _t->videoDataQuene_get((*reinterpret_cast< int64_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< BufferDataNode**>(_a[0]) = std::move(_r); }  break;
        case 9: _t->audioDataQuene_Input((*reinterpret_cast< const uint8_t*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 10: { BufferDataNode* _r = _t->audioDataQuene_get();
            if (_a[0]) *reinterpret_cast< BufferDataNode**>(_a[0]) = std::move(_r); }  break;
        case 11: _t->run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (savevideothread::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&savevideothread::SIG_sendVideoFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (savevideothread::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&savevideothread::SIG_sendPicInPic)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject savevideothread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_savevideothread.data,
    qt_meta_data_savevideothread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *savevideothread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *savevideothread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_savevideothread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int savevideothread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void savevideothread::SIG_sendVideoFrame(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void savevideothread::SIG_sendPicInPic(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
