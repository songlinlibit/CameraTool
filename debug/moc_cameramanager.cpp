/****************************************************************************
** Meta object code from reading C++ file 'cameramanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../cameramanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameramanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cameraManager_t {
    const uint offsetsAndSize[24];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_cameraManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_cameraManager_t qt_meta_stringdata_cameraManager = {
    {
QT_MOC_LITERAL(0, 13), // "cameraManager"
QT_MOC_LITERAL(14, 14), // "sendCameraList"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 4), // "list"
QT_MOC_LITERAL(35, 21), // "sendImageToChannelOne"
QT_MOC_LITERAL(57, 21), // "sendImageToChannelTwo"
QT_MOC_LITERAL(79, 8), // "startOne"
QT_MOC_LITERAL(88, 11), // "std::string"
QT_MOC_LITERAL(100, 8), // "startTwo"
QT_MOC_LITERAL(109, 14), // "updateExposure"
QT_MOC_LITERAL(124, 15), // "updateFeatureUI"
QT_MOC_LITERAL(140, 4) // "code"

    },
    "cameraManager\0sendCameraList\0\0list\0"
    "sendImageToChannelOne\0sendImageToChannelTwo\0"
    "startOne\0std::string\0startTwo\0"
    "updateExposure\0updateFeatureUI\0code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cameraManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       4,    1,   59,    2, 0x06,    3 /* Public */,
       5,    1,   62,    2, 0x06,    5 /* Public */,
       6,    1,   65,    2, 0x06,    7 /* Public */,
       8,    1,   68,    2, 0x06,    9 /* Public */,
       9,    4,   71,    2, 0x06,   11 /* Public */,
      10,    1,   80,    2, 0x06,   16 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void cameraManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cameraManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendCameraList((*reinterpret_cast< std::add_pointer_t<QList<QString>>>(_a[1]))); break;
        case 1: _t->sendImageToChannelOne((*reinterpret_cast< std::add_pointer_t<QPixmap>>(_a[1]))); break;
        case 2: _t->sendImageToChannelTwo((*reinterpret_cast< std::add_pointer_t<QPixmap>>(_a[1]))); break;
        case 3: _t->startOne((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 4: _t->startTwo((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 5: _t->updateExposure((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4]))); break;
        case 6: _t->updateFeatureUI((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cameraManager::*)(QVector<QString> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cameraManager::sendCameraList)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (cameraManager::*)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cameraManager::sendImageToChannelOne)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (cameraManager::*)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cameraManager::sendImageToChannelTwo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (cameraManager::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cameraManager::startOne)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (cameraManager::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cameraManager::startTwo)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (cameraManager::*)(int , double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cameraManager::updateExposure)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (cameraManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cameraManager::updateFeatureUI)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject cameraManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_cameraManager.offsetsAndSize,
    qt_meta_data_cameraManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_cameraManager_t
, QtPrivate::TypeAndForceComplete<cameraManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<QString>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPixmap, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPixmap, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::string, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::string, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *cameraManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cameraManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cameraManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int cameraManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void cameraManager::sendCameraList(QVector<QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cameraManager::sendImageToChannelOne(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cameraManager::sendImageToChannelTwo(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void cameraManager::startOne(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void cameraManager::startTwo(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void cameraManager::updateExposure(int _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void cameraManager::updateFeatureUI(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
