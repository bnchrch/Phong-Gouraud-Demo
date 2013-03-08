#include "basicopenglview.h"
#include <iostream>

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef __APPLE__
#include "supporting_files/s_core3_2_context.h"
#endif
#endif

BasicOpenGLView::BasicOpenGLView(QWidget *parent) :
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#ifdef __APPLE__
    QGLWidget(new Core3_2_context(QGLFormat::defaultFormat()), parent),
#else
    QGLWidget(QGLFormat::defaultFormat(), parent),
#endif
#endif
    mProjectionMatrix(),
    mViewMatrix(),
    mUsePostMultiply(false),
    mGeometries(),
    mFirstFrameDragging(true),
    mLastMousePos(),
    mDistance(2.0f),
    mTextureHandle(0),
    mBumpTextureHandle(0),
    mProgram(NULL),
    mAnimationTimer()
{
    mViewMatrix.lookAt(Vector3(0, 0, 2),
                       Vector3(0, 0, 0),
                       Vector3(0, 1, 0));

    mAnimationTimer.start();
}

void BasicOpenGLView::paintGL()
{
    // given our timer, this should be 20
    int elapsed = mAnimationTimer.elapsed();

    float secondsElapsed = elapsed * 0.001f;

    mLightPos.x = sin(secondsElapsed) * 20.0f;
    mLightPos.z = cos(secondsElapsed) * 20.0f;
    mLightPos.y = cos(secondsElapsed * 0.5f) * 20.0f;

    QColor curColor;
    curColor.setHsvF(fabs(cos(secondsElapsed / 20.0f)), 1.0, 1.0);

    mLightCol.x = curColor.redF();
    mLightCol.y = curColor.greenF();
    mLightCol.z = curColor.blueF();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(mRenderOrtho)
    {
        float mAspectRatio = ((float)this->width()) / this->height();
        mProjectionMatrix.ortho(-mDistance,
                                mDistance,
                                mDistance * mAspectRatio,
                                -mDistance * mAspectRatio,
                                -0.1,
                                -500.0);
    }

    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();

    while (it != mGeometries.end())
    {
        it->second->createModelMatrix(mUsePostMultiply);
        it->second->draw(mProjectionMatrix,
                         mViewMatrix,
                         mUsePostMultiply,
                         mLightPos,
                         mLightCol,
                         mTextureHandle,
                         mBumpTextureHandle,
                         mProgram);
        ++it;
    }

}

void BasicOpenGLView::loadGeometry(std::string m_GeometryPath)
{
    Geometry * newGeometry = new Geometry(m_GeometryPath);
    std::string geometryName = newGeometry->getFileName();

    if(mGeometries.find(geometryName) != mGeometries.end())
    {
        removeGeometry(geometryName);
    }
    mGeometries.insert(std::make_pair(geometryName, newGeometry));

    emit addedNewGeometry(geometryName);
}

void BasicOpenGLView::removeGeometry(std::string m_GeometryFileName)
{
    if(mGeometries.find(m_GeometryFileName) != mGeometries.end())
    {
        delete mGeometries[m_GeometryFileName];
    }
    mGeometries.erase(m_GeometryFileName);

    emit removedGeometry(m_GeometryFileName);
}
