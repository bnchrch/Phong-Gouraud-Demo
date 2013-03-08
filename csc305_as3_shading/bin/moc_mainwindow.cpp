/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Mar 8 11:02:55 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AssignmentThree/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      40,   25,   11,   11, 0x0a,
      70,   25,   11,   11, 0x0a,
      99,   11,   11,   11, 0x0a,
     113,   11,   11,   11, 0x0a,
     130,   11,   11,   11, 0x08,
     161,   11,   11,   11, 0x08,
     206,  198,   11,   11, 0x08,
     238,  232,   11,   11, 0x08,
     270,  232,   11,   11, 0x08,
     302,  232,   11,   11, 0x08,
     334,  232,   11,   11, 0x08,
     363,  232,   11,   11, 0x08,
     392,  232,   11,   11, 0x08,
     421,  232,   11,   11, 0x08,
     449,  232,   11,   11, 0x08,
     477,  232,   11,   11, 0x08,
     505,  198,   11,   11, 0x08,
     533,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0drawOpenGL()\0m_GeometryName\0"
    "newGeometryAdded(std::string)\0"
    "geometryRemoved(std::string)\0addGeometry()\0"
    "removeGeometry()\0on_actionAdd_Model_triggered()\0"
    "on_actionRemove_Selected_triggered()\0"
    "checked\0on_checkBox_toggled(bool)\0"
    "value\0on_translateX_valueChanged(int)\0"
    "on_translateY_valueChanged(int)\0"
    "on_translateZ_valueChanged(int)\0"
    "on_rotateX_valueChanged(int)\0"
    "on_rotateY_valueChanged(int)\0"
    "on_rotateZ_valueChanged(int)\0"
    "on_scaleX_valueChanged(int)\0"
    "on_scaleY_valueChanged(int)\0"
    "on_scaleZ_valueChanged(int)\0"
    "on_checkBox_2_toggled(bool)\0"
    "on_actionLoad_Shader_triggered()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->drawOpenGL(); break;
        case 1: _t->newGeometryAdded((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->geometryRemoved((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->addGeometry(); break;
        case 4: _t->removeGeometry(); break;
        case 5: _t->on_actionAdd_Model_triggered(); break;
        case 6: _t->on_actionRemove_Selected_triggered(); break;
        case 7: _t->on_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_translateX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_translateY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_translateZ_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_rotateX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_rotateY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_rotateZ_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_scaleX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_scaleY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_scaleZ_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_checkBox_2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_actionLoad_Shader_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
