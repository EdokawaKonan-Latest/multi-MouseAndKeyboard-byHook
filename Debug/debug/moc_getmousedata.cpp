/****************************************************************************
** Meta object code from reading C++ file 'getmousedata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mousechange/Header/getmousedata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getmousedata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GetMouseData_t {
    QByteArrayData data[18];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GetMouseData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GetMouseData_t qt_meta_stringdata_GetMouseData = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GetMouseData"
QT_MOC_LITERAL(1, 13, 5), // "mouse"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "countOne"
QT_MOC_LITERAL(4, 29, 8), // "countTwo"
QT_MOC_LITERAL(5, 38, 10), // "countThree"
QT_MOC_LITERAL(6, 49, 9), // "countFour"
QT_MOC_LITERAL(7, 59, 4), // "getX"
QT_MOC_LITERAL(8, 64, 1), // "p"
QT_MOC_LITERAL(9, 66, 4), // "getY"
QT_MOC_LITERAL(10, 71, 10), // "mouseCount"
QT_MOC_LITERAL(11, 82, 9), // "getButton"
QT_MOC_LITERAL(12, 92, 4), // "init"
QT_MOC_LITERAL(13, 97, 11), // "getDistance"
QT_MOC_LITERAL(14, 109, 8), // "setMouse"
QT_MOC_LITERAL(15, 118, 2), // "id"
QT_MOC_LITERAL(16, 121, 1), // "i"
QT_MOC_LITERAL(17, 123, 7) // "getKind"

    },
    "GetMouseData\0mouse\0\0countOne\0countTwo\0"
    "countThree\0countFour\0getX\0p\0getY\0"
    "mouseCount\0getButton\0init\0getDistance\0"
    "setMouse\0id\0i\0getKind"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetMouseData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   84,    2, 0x02 /* Public */,
       9,    1,   87,    2, 0x02 /* Public */,
      10,    0,   90,    2, 0x02 /* Public */,
      11,    1,   91,    2, 0x02 /* Public */,
      12,    0,   94,    2, 0x02 /* Public */,
      13,    1,   95,    2, 0x02 /* Public */,
      14,    2,   98,    2, 0x02 /* Public */,
      17,    1,  103,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int, QMetaType::Int,    8,
    QMetaType::Int, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::ULongLong, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::UShort, QMetaType::Int,    8,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   15,   16,
    QMetaType::Int, QMetaType::Int,   15,

       0        // eod
};

void GetMouseData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GetMouseData *_t = static_cast<GetMouseData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouse(); break;
        case 1: _t->countOne(); break;
        case 2: _t->countTwo(); break;
        case 3: _t->countThree(); break;
        case 4: _t->countFour(); break;
        case 5: { int _r = _t->getX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->getY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->mouseCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { unsigned long long _r = _t->getButton((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< unsigned long long*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->init(); break;
        case 10: { unsigned short _r = _t->getDistance((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< unsigned short*>(_a[0]) = std::move(_r); }  break;
        case 11: { int _r = _t->setMouse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->getKind((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (GetMouseData::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMouseData::mouse)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GetMouseData::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMouseData::countOne)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GetMouseData::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMouseData::countTwo)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GetMouseData::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMouseData::countThree)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (GetMouseData::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMouseData::countFour)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject GetMouseData::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GetMouseData.data,
      qt_meta_data_GetMouseData,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GetMouseData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GetMouseData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GetMouseData.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int GetMouseData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void GetMouseData::mouse()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GetMouseData::countOne()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GetMouseData::countTwo()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GetMouseData::countThree()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GetMouseData::countFour()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
