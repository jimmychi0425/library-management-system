/****************************************************************************
** Meta object code from reading C++ file 'librarymain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../librarymain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'librarymain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_libraryMain_t {
    QByteArrayData data[17];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_libraryMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_libraryMain_t qt_meta_stringdata_libraryMain = {
    {
QT_MOC_LITERAL(0, 0, 11), // "libraryMain"
QT_MOC_LITERAL(1, 12, 10), // "click_load"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 15), // "clickLoadCancel"
QT_MOC_LITERAL(4, 40, 16), // "clickLoadConfirm"
QT_MOC_LITERAL(5, 57, 7), // "process"
QT_MOC_LITERAL(6, 65, 16), // "changeSearchbook"
QT_MOC_LITERAL(7, 82, 15), // "clearSearchbook"
QT_MOC_LITERAL(8, 98, 14), // "findBorrowBook"
QT_MOC_LITERAL(9, 113, 13), // "addBorrowBook"
QT_MOC_LITERAL(10, 127, 14), // "findreturnBook"
QT_MOC_LITERAL(11, 142, 13), // "addreturnBook"
QT_MOC_LITERAL(12, 156, 14), // "addLibraryCard"
QT_MOC_LITERAL(13, 171, 17), // "deleteLibraryCard"
QT_MOC_LITERAL(14, 189, 7), // "addBook"
QT_MOC_LITERAL(15, 197, 10), // "deleteBook"
QT_MOC_LITERAL(16, 208, 11) // "addBookList"

    },
    "libraryMain\0click_load\0\0clickLoadCancel\0"
    "clickLoadConfirm\0process\0changeSearchbook\0"
    "clearSearchbook\0findBorrowBook\0"
    "addBorrowBook\0findreturnBook\0addreturnBook\0"
    "addLibraryCard\0deleteLibraryCard\0"
    "addBook\0deleteBook\0addBookList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_libraryMain[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void libraryMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        libraryMain *_t = static_cast<libraryMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->click_load(); break;
        case 1: _t->clickLoadCancel(); break;
        case 2: _t->clickLoadConfirm(); break;
        case 3: _t->process(); break;
        case 4: _t->changeSearchbook(); break;
        case 5: _t->clearSearchbook(); break;
        case 6: _t->findBorrowBook(); break;
        case 7: _t->addBorrowBook(); break;
        case 8: _t->findreturnBook(); break;
        case 9: _t->addreturnBook(); break;
        case 10: _t->addLibraryCard(); break;
        case 11: _t->deleteLibraryCard(); break;
        case 12: _t->addBook(); break;
        case 13: _t->deleteBook(); break;
        case 14: _t->addBookList(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject libraryMain::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_libraryMain.data,
      qt_meta_data_libraryMain,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *libraryMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *libraryMain::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_libraryMain.stringdata0))
        return static_cast<void*>(const_cast< libraryMain*>(this));
    return QObject::qt_metacast(_clname);
}

int libraryMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
