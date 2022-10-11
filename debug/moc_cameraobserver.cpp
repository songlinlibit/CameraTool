/****************************************************************************
** Meta object code from reading C++ file 'cameraobserver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../cameraobserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraobserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraObserver_t {
    const uint offsetsAndSize[6];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CameraObserver_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CameraObserver_t qt_meta_stringdata_CameraObserver = {
    {
QT_MOC_LITERAL(0, 14), // "CameraObserver"
QT_MOC_LITERAL(15, 16), // "updateDeviceList"
QT_MOC_LITERAL(32, 0) // ""

    },
    "CameraObserver\0updateDeviceList\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraObserver[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void CameraObserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraObserver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateDeviceList(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraObserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraObserver::updateDeviceList)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject CameraObserver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CameraObserver.offsetsAndSize,
    qt_meta_data_CameraObserver,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CameraObserver_t
, QtPrivate::TypeAndForceComplete<CameraObserver, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *CameraObserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraObserver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraObserver.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "AVT::VmbAPI::ICameraListObserver"))
        return static_cast< AVT::VmbAPI::ICameraListObserver*>(this);
    return QObject::qt_metacast(_clname);
}

int CameraObserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CameraObserver::updateDeviceList()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
