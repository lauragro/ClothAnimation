/****************************************************************************
** Meta object code from reading C++ file 'openglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../my_clothing/openglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OpenGLWidget_t {
    QByteArrayData data[8];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenGLWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenGLWidget_t qt_meta_stringdata_OpenGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OpenGLWidget"
QT_MOC_LITERAL(1, 13, 9), // "button_go"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "button_stop"
QT_MOC_LITERAL(4, 36, 12), // "button_reset"
QT_MOC_LITERAL(5, 49, 11), // "advanceTime"
QT_MOC_LITERAL(6, 61, 12), // "advanceFrame"
QT_MOC_LITERAL(7, 74, 5) // "endit"

    },
    "OpenGLWidget\0button_go\0\0button_stop\0"
    "button_reset\0advanceTime\0advanceFrame\0"
    "endit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenGLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OpenGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OpenGLWidget *_t = static_cast<OpenGLWidget *>(_o);
        switch (_id) {
        case 0: _t->button_go(); break;
        case 1: _t->button_stop(); break;
        case 2: _t->button_reset(); break;
        case 3: _t->advanceTime(); break;
        case 4: _t->advanceFrame(); break;
        case 5: _t->endit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject OpenGLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_OpenGLWidget.data,
      qt_meta_data_OpenGLWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OpenGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGLWidget.stringdata))
        return static_cast<void*>(const_cast< OpenGLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int OpenGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
