/****************************************************************************
** Meta object code from reading C++ file 'SyntacticAnalyzer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SyntacticAnalyzer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SyntacticAnalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SyntacticAnalyzer_t {
    QByteArrayData data[19];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SyntacticAnalyzer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SyntacticAnalyzer_t qt_meta_stringdata_SyntacticAnalyzer = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SyntacticAnalyzer"
QT_MOC_LITERAL(1, 18, 15), // "send_input_type"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 10), // "input_type"
QT_MOC_LITERAL(4, 46, 15), // "open_expression"
QT_MOC_LITERAL(5, 62, 12), // "open_setting"
QT_MOC_LITERAL(6, 75, 9), // "check_btn"
QT_MOC_LITERAL(7, 85, 17), // "rev_terminal_path"
QT_MOC_LITERAL(8, 103, 17), // "rev_grammars_path"
QT_MOC_LITERAL(9, 121, 9), // "close_cfg"
QT_MOC_LITERAL(10, 131, 11), // "update_info"
QT_MOC_LITERAL(11, 143, 10), // "input_info"
QT_MOC_LITERAL(12, 154, 12), // "input_finish"
QT_MOC_LITERAL(13, 167, 14), // "input_grammars"
QT_MOC_LITERAL(14, 182, 15), // "input_terminals"
QT_MOC_LITERAL(15, 198, 9), // "input_exp"
QT_MOC_LITERAL(16, 208, 12), // "update_input"
QT_MOC_LITERAL(17, 221, 9), // "show_step"
QT_MOC_LITERAL(18, 231, 4) // "link"

    },
    "SyntacticAnalyzer\0send_input_type\0\0"
    "input_type\0open_expression\0open_setting\0"
    "check_btn\0rev_terminal_path\0"
    "rev_grammars_path\0close_cfg\0update_info\0"
    "input_info\0input_finish\0input_grammars\0"
    "input_terminals\0input_exp\0update_input\0"
    "show_step\0link"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SyntacticAnalyzer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   92,    2, 0x08 /* Private */,
       5,    0,   93,    2, 0x08 /* Private */,
       6,    0,   94,    2, 0x08 /* Private */,
       7,    1,   95,    2, 0x08 /* Private */,
       8,    1,   98,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    1,  103,    2, 0x08 /* Private */,
      12,    0,  106,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    0,  108,    2, 0x08 /* Private */,
      15,    0,  109,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    1,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QUrl,   18,

       0        // eod
};

void SyntacticAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SyntacticAnalyzer *_t = static_cast<SyntacticAnalyzer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_input_type((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->open_expression(); break;
        case 2: _t->open_setting(); break;
        case 3: _t->check_btn(); break;
        case 4: _t->rev_terminal_path((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->rev_grammars_path((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->close_cfg(); break;
        case 7: _t->update_info(); break;
        case 8: _t->input_info((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->input_finish(); break;
        case 10: _t->input_grammars(); break;
        case 11: _t->input_terminals(); break;
        case 12: _t->input_exp(); break;
        case 13: _t->update_input(); break;
        case 14: _t->show_step((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SyntacticAnalyzer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SyntacticAnalyzer::send_input_type)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SyntacticAnalyzer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SyntacticAnalyzer.data,
      qt_meta_data_SyntacticAnalyzer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SyntacticAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SyntacticAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SyntacticAnalyzer.stringdata0))
        return static_cast<void*>(const_cast< SyntacticAnalyzer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SyntacticAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SyntacticAnalyzer::send_input_type(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
