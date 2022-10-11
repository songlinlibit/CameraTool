/****************************************************************************
** Meta object code from reading C++ file 'imageprocessthread.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../imageprocessthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageprocessthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_imageProcessThread_t {
    const uint offsetsAndSize[14];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_imageProcessThread_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_imageProcessThread_t qt_meta_stringdata_imageProcessThread = {
    {
QT_MOC_LITERAL(0, 18), // "imageProcessThread"
QT_MOC_LITERAL(19, 11), // "pixmapReady"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 13), // "streamStarted"
QT_MOC_LITERAL(46, 13), // "streamStopped"
QT_MOC_LITERAL(60, 12), // "sendFeatures"
QT_MOC_LITERAL(73, 24) // "QMap<QString,FeaturePtr>"

    },
    "imageProcessThread\0pixmapReady\0\0"
    "streamStarted\0streamStopped\0sendFeatures\0"
    "QMap<QString,FeaturePtr>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_imageProcessThread[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       3,    0,   41,    2, 0x06,    3 /* Public */,
       4,    0,   42,    2, 0x06,    4 /* Public */,
       5,    1,   43,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void imageProcessThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<imageProcessThread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pixmapReady((*reinterpret_cast< std::add_pointer_t<QPixmap>>(_a[1]))); break;
        case 1: _t->streamStarted(); break;
        case 2: _t->streamStopped(); break;
        case 3: _t->sendFeatures((*reinterpret_cast< std::add_pointer_t<QMap<QString,FeaturePtr>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (imageProcessThread::*)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&imageProcessThread::pixmapReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (imageProcessThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&imageProcessThread::streamStarted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (imageProcessThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&imageProcessThread::streamStopped)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (imageProcessThread::*)(QMap<QString,FeaturePtr> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&imageProcessThread::sendFeatures)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject imageProcessThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_imageProcessThread.offsetsAndSize,
    qt_meta_data_imageProcessThread,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_imageProcessThread_t
, QtPrivate::TypeAndForceComplete<imageProcessThread, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPixmap, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMap<QString,FeaturePtr>, std::false_type>



>,
    nullptr
} };


const QMetaObject *imageProcessThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *imageProcessThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_imageProcessThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int imageProcessThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void imageProcessThread::pixmapReady(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void imageProcessThread::streamStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void imageProcessThread::streamStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void imageProcessThread::sendFeatures(QMap<QString,FeaturePtr> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
