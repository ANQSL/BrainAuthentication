/****************************************************************************
** Meta object code from reading C++ file 'ssveptestthread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ssveptestthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ssveptestthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ssveptestthread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      34,   30,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ssveptestthread[] = {
    "ssveptestthread\0\0movetarget()\0val\0"
    "logCCAVal(int)\0"
};

void ssveptestthread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ssveptestthread *_t = static_cast<ssveptestthread *>(_o);
        switch (_id) {
        case 0: _t->movetarget(); break;
        case 1: _t->logCCAVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ssveptestthread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ssveptestthread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ssveptestthread,
      qt_meta_data_ssveptestthread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ssveptestthread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ssveptestthread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ssveptestthread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ssveptestthread))
        return static_cast<void*>(const_cast< ssveptestthread*>(this));
    return QThread::qt_metacast(_clname);
}

int ssveptestthread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ssveptestthread::movetarget()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ssveptestthread::logCCAVal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
