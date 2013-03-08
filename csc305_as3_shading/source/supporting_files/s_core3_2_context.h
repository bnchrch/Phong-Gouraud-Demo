#ifndef S_CORE3_2_CONTEXT_H
#define S_CORE3_2_CONTEXT_H

#include <qglobal.h>

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef __APPLE__
#include <QGLContext>

void* select_3_2_mac_visual(GDHandle handle);


struct Core3_2_context : public QGLContext
{
    Core3_2_context(const QGLFormat& format, QPaintDevice* device) : QGLContext(format,device) {}
    Core3_2_context(const QGLFormat& format) : QGLContext(format) {}

    virtual void* chooseMacVisual(GDHandle handle)
    {
        return select_3_2_mac_visual(handle);
    }
};
#endif
#endif

#endif // S_CORE3_2_CONTEXT_H
