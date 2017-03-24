/****************************************************************************
** Meta object code from reading C++ file 'chorddisplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../program/src/chorddisplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chorddisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChordDisplay_t {
    QByteArrayData data[8];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChordDisplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChordDisplay_t qt_meta_stringdata_ChordDisplay = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ChordDisplay"
QT_MOC_LITERAL(1, 13, 12), // "deleteSignal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "ChordDisplay*"
QT_MOC_LITERAL(4, 41, 2), // "cd"
QT_MOC_LITERAL(5, 44, 16), // "slotDeleteButton"
QT_MOC_LITERAL(6, 61, 12), // "slotOpenView"
QT_MOC_LITERAL(7, 74, 13) // "slotCloseView"

    },
    "ChordDisplay\0deleteSignal\0\0ChordDisplay*\0"
    "cd\0slotDeleteButton\0slotOpenView\0"
    "slotCloseView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChordDisplay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x0a /* Public */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ChordDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChordDisplay *_t = static_cast<ChordDisplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deleteSignal((*reinterpret_cast< ChordDisplay*(*)>(_a[1]))); break;
        case 1: _t->slotDeleteButton(); break;
        case 2: _t->slotOpenView(); break;
        case 3: _t->slotCloseView(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ChordDisplay* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChordDisplay::*_t)(ChordDisplay * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChordDisplay::deleteSignal)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ChordDisplay::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_ChordDisplay.data,
      qt_meta_data_ChordDisplay,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ChordDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChordDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ChordDisplay.stringdata0))
        return static_cast<void*>(const_cast< ChordDisplay*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int ChordDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ChordDisplay::deleteSignal(ChordDisplay * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
