/****************************************************************************
** Meta object code from reading C++ file 'logindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../logindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoginDialog_t {
    QByteArrayData data[79];
    char stringdata0[1155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginDialog_t qt_meta_stringdata_LoginDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LoginDialog"
QT_MOC_LITERAL(1, 12, 13), // "sig_close_dio"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "sig_send_upInfo"
QT_MOC_LITERAL(4, 43, 4), // "name"
QT_MOC_LITERAL(5, 48, 3), // "dir"
QT_MOC_LITERAL(6, 52, 17), // "sig_download_file"
QT_MOC_LITERAL(7, 70, 7), // "file_id"
QT_MOC_LITERAL(8, 78, 19), // "sig_download_folder"
QT_MOC_LITERAL(9, 98, 14), // "sig_add_Folder"
QT_MOC_LITERAL(10, 113, 4), // "path"
QT_MOC_LITERAL(11, 118, 12), // "sig_changDir"
QT_MOC_LITERAL(12, 131, 17), // "sig_upload_folder"
QT_MOC_LITERAL(13, 149, 14), // "sig_share_info"
QT_MOC_LITERAL(14, 164, 12), // "QVector<int>"
QT_MOC_LITERAL(15, 177, 3), // "res"
QT_MOC_LITERAL(16, 181, 13), // "sig_Send_Link"
QT_MOC_LITERAL(17, 195, 4), // "code"
QT_MOC_LITERAL(18, 200, 15), // "sig_delete_file"
QT_MOC_LITERAL(19, 216, 13), // "sig_down_attr"
QT_MOC_LITERAL(20, 230, 9), // "timestamp"
QT_MOC_LITERAL(21, 240, 6), // "result"
QT_MOC_LITERAL(22, 247, 11), // "sig_up_attr"
QT_MOC_LITERAL(23, 259, 18), // "on_pb_file_clicked"
QT_MOC_LITERAL(24, 278, 18), // "on_pb_tram_clicked"
QT_MOC_LITERAL(25, 297, 19), // "on_pb_share_clicked"
QT_MOC_LITERAL(26, 317, 21), // "on_pb_addfile_clicked"
QT_MOC_LITERAL(27, 339, 18), // "add_folder_trigger"
QT_MOC_LITERAL(28, 358, 2), // "op"
QT_MOC_LITERAL(29, 361, 19), // "upload_file_trigger"
QT_MOC_LITERAL(30, 381, 18), // "upload_dir_trigger"
QT_MOC_LITERAL(31, 400, 10), // "share_file"
QT_MOC_LITERAL(32, 411, 4), // "flag"
QT_MOC_LITERAL(33, 416, 11), // "delete_file"
QT_MOC_LITERAL(34, 428, 13), // "download_file"
QT_MOC_LITERAL(35, 442, 20), // "act_GetShare_trigger"
QT_MOC_LITERAL(36, 463, 15), // "slot_down_pause"
QT_MOC_LITERAL(37, 479, 16), // "slot_down_presum"
QT_MOC_LITERAL(38, 496, 13), // "slot_up_pause"
QT_MOC_LITERAL(39, 510, 14), // "slot_up_presum"
QT_MOC_LITERAL(40, 525, 15), // "act_PDF_trigger"
QT_MOC_LITERAL(41, 541, 21), // "act_Playvideo_trigger"
QT_MOC_LITERAL(42, 563, 15), // "slot_insertFile"
QT_MOC_LITERAL(43, 579, 9), // "FileInfo*"
QT_MOC_LITERAL(44, 589, 4), // "info"
QT_MOC_LITERAL(45, 594, 13), // "slot_insertOK"
QT_MOC_LITERAL(46, 608, 18), // "slot_uploadProgess"
QT_MOC_LITERAL(47, 627, 3), // "pos"
QT_MOC_LITERAL(48, 631, 15), // "slot_deleteFile"
QT_MOC_LITERAL(49, 647, 3), // "row"
QT_MOC_LITERAL(50, 651, 15), // "slot_insertInfo"
QT_MOC_LITERAL(51, 667, 19), // "slot_deleteDownFile"
QT_MOC_LITERAL(52, 687, 17), // "slot_insertDownOK"
QT_MOC_LITERAL(53, 705, 20), // "slot_insertShareInfo"
QT_MOC_LITERAL(54, 726, 4), // "size"
QT_MOC_LITERAL(55, 731, 4), // "time"
QT_MOC_LITERAL(56, 736, 4), // "Link"
QT_MOC_LITERAL(57, 741, 17), // "slot_DownloadInfo"
QT_MOC_LITERAL(58, 759, 20), // "slot_DownloadProgess"
QT_MOC_LITERAL(59, 780, 10), // "closeEvent"
QT_MOC_LITERAL(60, 791, 12), // "QCloseEvent*"
QT_MOC_LITERAL(61, 804, 5), // "event"
QT_MOC_LITERAL(62, 810, 7), // "setCoin"
QT_MOC_LITERAL(63, 818, 2), // "id"
QT_MOC_LITERAL(64, 821, 15), // "slot_delete_ALL"
QT_MOC_LITERAL(65, 837, 20), // "slot_deleteShare_ALL"
QT_MOC_LITERAL(66, 858, 18), // "slot_getInfoBytime"
QT_MOC_LITERAL(67, 877, 20), // "slot_getUpInfoBytime"
QT_MOC_LITERAL(68, 898, 10), // "clearshare"
QT_MOC_LITERAL(69, 909, 26), // "on_twg_content_cellClicked"
QT_MOC_LITERAL(70, 936, 6), // "column"
QT_MOC_LITERAL(71, 943, 41), // "on_twg_content_customContextM..."
QT_MOC_LITERAL(72, 985, 27), // "on_twg_download_cellClicked"
QT_MOC_LITERAL(73, 1013, 13), // "slot_openPath"
QT_MOC_LITERAL(74, 1027, 32), // "on_twg_content_cellDoubleClicked"
QT_MOC_LITERAL(75, 1060, 17), // "on_pb_pre_clicked"
QT_MOC_LITERAL(76, 1078, 25), // "on_twg_upload_cellClicked"
QT_MOC_LITERAL(77, 1104, 31), // "on_twg_finish_cellDoubleClicked"
QT_MOC_LITERAL(78, 1136, 18) // "on_pb_name_clicked"

    },
    "LoginDialog\0sig_close_dio\0\0sig_send_upInfo\0"
    "name\0dir\0sig_download_file\0file_id\0"
    "sig_download_folder\0sig_add_Folder\0"
    "path\0sig_changDir\0sig_upload_folder\0"
    "sig_share_info\0QVector<int>\0res\0"
    "sig_Send_Link\0code\0sig_delete_file\0"
    "sig_down_attr\0timestamp\0result\0"
    "sig_up_attr\0on_pb_file_clicked\0"
    "on_pb_tram_clicked\0on_pb_share_clicked\0"
    "on_pb_addfile_clicked\0add_folder_trigger\0"
    "op\0upload_file_trigger\0upload_dir_trigger\0"
    "share_file\0flag\0delete_file\0download_file\0"
    "act_GetShare_trigger\0slot_down_pause\0"
    "slot_down_presum\0slot_up_pause\0"
    "slot_up_presum\0act_PDF_trigger\0"
    "act_Playvideo_trigger\0slot_insertFile\0"
    "FileInfo*\0info\0slot_insertOK\0"
    "slot_uploadProgess\0pos\0slot_deleteFile\0"
    "row\0slot_insertInfo\0slot_deleteDownFile\0"
    "slot_insertDownOK\0slot_insertShareInfo\0"
    "size\0time\0Link\0slot_DownloadInfo\0"
    "slot_DownloadProgess\0closeEvent\0"
    "QCloseEvent*\0event\0setCoin\0id\0"
    "slot_delete_ALL\0slot_deleteShare_ALL\0"
    "slot_getInfoBytime\0slot_getUpInfoBytime\0"
    "clearshare\0on_twg_content_cellClicked\0"
    "column\0on_twg_content_customContextMenuRequested\0"
    "on_twg_download_cellClicked\0slot_openPath\0"
    "on_twg_content_cellDoubleClicked\0"
    "on_pb_pre_clicked\0on_twg_upload_cellClicked\0"
    "on_twg_finish_cellDoubleClicked\0"
    "on_pb_name_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  289,    2, 0x06 /* Public */,
       3,    2,  290,    2, 0x06 /* Public */,
       6,    2,  295,    2, 0x06 /* Public */,
       8,    2,  300,    2, 0x06 /* Public */,
       9,    2,  305,    2, 0x06 /* Public */,
      11,    1,  310,    2, 0x06 /* Public */,
      12,    2,  313,    2, 0x06 /* Public */,
      13,    2,  318,    2, 0x06 /* Public */,
      16,    2,  323,    2, 0x06 /* Public */,
      18,    2,  328,    2, 0x06 /* Public */,
      19,    2,  333,    2, 0x06 /* Public */,
      22,    2,  338,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    0,  343,    2, 0x0a /* Public */,
      24,    0,  344,    2, 0x0a /* Public */,
      25,    0,  345,    2, 0x0a /* Public */,
      26,    0,  346,    2, 0x0a /* Public */,
      27,    1,  347,    2, 0x0a /* Public */,
      29,    1,  350,    2, 0x0a /* Public */,
      30,    1,  353,    2, 0x0a /* Public */,
      31,    1,  356,    2, 0x0a /* Public */,
      33,    1,  359,    2, 0x0a /* Public */,
      34,    1,  362,    2, 0x0a /* Public */,
      35,    1,  365,    2, 0x0a /* Public */,
      36,    1,  368,    2, 0x0a /* Public */,
      37,    1,  371,    2, 0x0a /* Public */,
      38,    1,  374,    2, 0x0a /* Public */,
      39,    1,  377,    2, 0x0a /* Public */,
      40,    1,  380,    2, 0x0a /* Public */,
      41,    1,  383,    2, 0x0a /* Public */,
      42,    1,  386,    2, 0x0a /* Public */,
      45,    1,  389,    2, 0x0a /* Public */,
      46,    2,  392,    2, 0x0a /* Public */,
      48,    1,  397,    2, 0x0a /* Public */,
      50,    1,  400,    2, 0x0a /* Public */,
      51,    1,  403,    2, 0x0a /* Public */,
      52,    1,  406,    2, 0x0a /* Public */,
      53,    4,  409,    2, 0x0a /* Public */,
      57,    1,  418,    2, 0x0a /* Public */,
      58,    2,  421,    2, 0x0a /* Public */,
      59,    1,  426,    2, 0x0a /* Public */,
      62,    1,  429,    2, 0x0a /* Public */,
      64,    0,  432,    2, 0x0a /* Public */,
      65,    0,  433,    2, 0x0a /* Public */,
      66,    1,  434,    2, 0x0a /* Public */,
      67,    1,  437,    2, 0x0a /* Public */,
      68,    0,  440,    2, 0x0a /* Public */,
      69,    2,  441,    2, 0x08 /* Private */,
      71,    1,  446,    2, 0x08 /* Private */,
      72,    2,  449,    2, 0x08 /* Private */,
      73,    1,  454,    2, 0x08 /* Private */,
      74,    2,  457,    2, 0x08 /* Private */,
      75,    0,  462,    2, 0x08 /* Private */,
      76,    2,  463,    2, 0x08 /* Private */,
      77,    2,  468,    2, 0x08 /* Private */,
      78,    0,  473,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,    5,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QString,   15,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,   17,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QString,   15,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   47,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::Int,    4,   54,   55,   56,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   47,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, QMetaType::Int,   63,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 43, QMetaType::Int,   20,
    0x80000000 | 43, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   49,   70,
    QMetaType::Void, QMetaType::QPoint,   47,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   49,   70,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   49,   70,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   49,   70,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   49,   70,
    QMetaType::Void,

       0        // eod
};

void LoginDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_close_dio(); break;
        case 1: _t->sig_send_upInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->sig_download_file((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->sig_download_folder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->sig_add_Folder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->sig_changDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sig_upload_folder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->sig_share_info((*reinterpret_cast< QVector<int>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->sig_Send_Link((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->sig_delete_file((*reinterpret_cast< QVector<int>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->sig_down_attr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->sig_up_attr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->on_pb_file_clicked(); break;
        case 13: _t->on_pb_tram_clicked(); break;
        case 14: _t->on_pb_share_clicked(); break;
        case 15: _t->on_pb_addfile_clicked(); break;
        case 16: _t->add_folder_trigger((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->upload_file_trigger((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->upload_dir_trigger((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->share_file((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->delete_file((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->download_file((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->act_GetShare_trigger((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->slot_down_pause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->slot_down_presum((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->slot_up_pause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->slot_up_presum((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->act_PDF_trigger((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->act_Playvideo_trigger((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->slot_insertFile((*reinterpret_cast< FileInfo*(*)>(_a[1]))); break;
        case 30: _t->slot_insertOK((*reinterpret_cast< FileInfo*(*)>(_a[1]))); break;
        case 31: _t->slot_uploadProgess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 32: _t->slot_deleteFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->slot_insertInfo((*reinterpret_cast< FileInfo*(*)>(_a[1]))); break;
        case 34: _t->slot_deleteDownFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->slot_insertDownOK((*reinterpret_cast< FileInfo*(*)>(_a[1]))); break;
        case 36: _t->slot_insertShareInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 37: _t->slot_DownloadInfo((*reinterpret_cast< FileInfo*(*)>(_a[1]))); break;
        case 38: _t->slot_DownloadProgess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 39: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 40: _t->setCoin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->slot_delete_ALL(); break;
        case 42: _t->slot_deleteShare_ALL(); break;
        case 43: { FileInfo* _r = _t->slot_getInfoBytime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< FileInfo**>(_a[0]) = std::move(_r); }  break;
        case 44: { FileInfo* _r = _t->slot_getUpInfoBytime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< FileInfo**>(_a[0]) = std::move(_r); }  break;
        case 45: _t->clearshare(); break;
        case 46: _t->on_twg_content_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 47: _t->on_twg_content_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 48: _t->on_twg_download_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 49: _t->slot_openPath((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->on_twg_content_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 51: _t->on_pb_pre_clicked(); break;
        case 52: _t->on_twg_upload_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 53: _t->on_twg_finish_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 54: _t->on_pb_name_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_close_dio)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_send_upInfo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_download_file)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_download_folder)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_add_Folder)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_changDir)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_upload_folder)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(QVector<int> , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_share_info)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_Send_Link)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(QVector<int> , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_delete_file)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_down_attr)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_up_attr)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LoginDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_LoginDialog.data,
    qt_meta_data_LoginDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LoginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoginDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int LoginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    }
    return _id;
}

// SIGNAL 0
void LoginDialog::sig_close_dio()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LoginDialog::sig_send_upInfo(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LoginDialog::sig_download_file(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LoginDialog::sig_download_folder(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LoginDialog::sig_add_Folder(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LoginDialog::sig_changDir(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LoginDialog::sig_upload_folder(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void LoginDialog::sig_share_info(QVector<int> _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void LoginDialog::sig_Send_Link(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void LoginDialog::sig_delete_file(QVector<int> _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void LoginDialog::sig_down_attr(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void LoginDialog::sig_up_attr(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
