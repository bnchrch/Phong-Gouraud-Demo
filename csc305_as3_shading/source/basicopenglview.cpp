#include "basicopenglview.h"
#include <QMessageBox>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <QMouseEvent>

void BasicOpenGLView::loadMaterial(std::string m_Material)
{
    std::ifstream t(m_Material.c_str());
    std::stringstream buffer;
    buffer << t.rdbuf();

    /**
     * we assume file contents like this:
     * vertex path/to/vertex/shader.vs
     * fragment path/to/fragment/shader.fs
     *
     * with an optional
     * texture path/to/texture.png
     *
     * paths are relative to the m_Material path
     */

    if(mProgram)
    {
        delete mProgram;
        mProgram = NULL;
    }

    if(mTextureHandle)
    {
        glDeleteTextures(1, & mTextureHandle);
        mTextureHandle = 0;
    }

    std::string filePath = m_Material.substr(0, m_Material.find_last_of("/") + 1);

    const std::string vertex("vertex");
    const std::string fragment("fragment");
    const std::string texture("texture");
    const std::string bump("bumpmap");

    mProgram = new Program();

    std::string line;
    while(std::getline(buffer, line))
    {
        if(line.compare(0, vertex.size(), vertex) == 0)
        {
            std::string vertexPath = filePath + line.substr(vertex.size() + 1);

            std::ifstream v(vertexPath.c_str());
            std::stringstream vbuffer;
            vbuffer << v.rdbuf();

            Shader * vShader = new Shader(vbuffer.str(), Shader::VERTEX);
            if(vShader->load())
            {
                mProgram->push_back(vShader);
            }
        }
        else if(line.compare(0, fragment.size(), fragment) == 0)
        {
            std::string fragmentPath = filePath + line.substr(fragment.size() + 1);

            std::ifstream f(fragmentPath.c_str());
            std::stringstream fbuffer;
            fbuffer << f.rdbuf();

            Shader * fShader = new Shader(fbuffer.str(), Shader::FRAGMENT);
            if(fShader->load())
            {
                mProgram->push_back(fShader);
            }
        }
        else if(line.compare(0, texture.size(), texture) == 0)
        {
            std::string texturePath = filePath + line.substr(texture.size() + 1);

            /**
             * @todo assignment 3
             * use the texturePath to load an image from disc, and transfer its data to
             * OpenGL and store the OpenGL image handle in mTextureHandle
             */

            //start my code
            QImage tempImage;
            tempImage.load(texturePath.c_str());
            tempImage = QGLWidget::convertToGLFormat(tempImage);



        // copy the texture to opengl
        glGenTextures(1, &mTextureHandle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage.width(), tempImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage.bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            /*
            glGenTextures(1, & mTextureHandle);
            glBindTexture(GL_TEXTURE_2D, mTextureHandle);

            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RGBA,
                         tempImage.width(),
                         tempImage.height(),
                         0,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         tempImage.bits());

            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
*/
            //end my code
        }
        else if(line.compare(0, bump.size(), bump) == 0)
        {
            std::string texturePath = filePath + line.substr(texture.size() + 1);

            /**
             * @todo assignment 3
             * use the texturePath to load an image from disc, and transfer its data to
             * OpenGL and store the OpenGL image handle in mBumpTextureHandle
             */
            QImage tempImage;
            tempImage.load(texturePath.c_str());
            tempImage = QGLWidget::convertToGLFormat(tempImage);



        // copy the texture to opengl
        glGenTextures(1, &mBumpTextureHandle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mBumpTextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage.width(), tempImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage.bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else
        {
            /**
             * unknown file contents
             */
        }
    }

    if(!mProgram->link())
    {
        delete mProgram;
        mProgram = NULL;
    }
}

void BasicOpenGLView::setOrtho(bool m_RenderOrtho)
{
    mRenderOrtho = m_RenderOrtho;

    this->resizeGL(this->width(), this->height());
}

void BasicOpenGLView::setPostMultiply(bool m_PostMultiply)
{
    mUsePostMultiply = m_PostMultiply;
}

void BasicOpenGLView::initializeGL()
{
#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Glew could not initialize" << std::endl;
    }
#endif
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    std::cout<<glGetString(GL_VERSION)<<std::endl;
#else
    if(this->format().majorVersion() < 3 && this->format().minorVersion() < 2)
    {
        QMessageBox msgBox;
        msgBox.setText("The OpenGL version available on this computer is too old.");
        msgBox.setInformativeText("OpenGL 3.2 or higher required to run this application.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();
        QCoreApplication::quit();
    }
#endif

    mLightPos = Vector3(0.0, 10.0, 0.0);
    mLightCol = Vector4(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    /**
     *  @todo assignment two
     *  initialize the mViewMatrix and mProjectionMatrix with starting values here
     */
}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    /**
     *  @todo assignment two
     *  mProjectionMatrix has to be updated in here, when the window is
     *  resized with the values depending on the selected method (orthographic
     *  or perspective)
     *  Hint: for the swap between projection methods to work properly you will also
     *  need to add a function that responds to the switch in the UI
     */
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
    else
    {
        mProjectionMatrix.perspective(60,
                                      ((float)this->width()) / this->height(),
                                      0.1,
                                      500.0);
    }
}

void BasicOpenGLView::mousePressEvent(QMouseEvent *event)
{
    /**
     *  @todo assignment two
     *  these function might be needed for the arc ball or world crawler
     */
	mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    /**
     *  @todo assignment two
     *  these function might be needed for the arc ball or world crawler
     */
	mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
	float eventX = (float)event->x() / width();
    float eventY = 1.0f - (float) event->y() / height();
	
    eventX -= 0.5f;
    eventY -= 0.5f;
    eventX *= 2.0f;
    eventY *= 2.0f;
	
	Vector3 curPoint(eventX, eventY);
	
	if(mFirstFrameDragging)
	{
		mLastMousePos = curPoint;
		mFirstFrameDragging = false;
		return;
	}
	
	Vector3 difference;
	for(size_t i = 0; i < 3; ++i)
	{
		difference.elements[i] = curPoint.elements[i] - mLastMousePos.elements[i];
	}

    /**
     *  @todo assignment two
     *  use the mouse input to modify mViewMatrix to work as an arc-ball interface,
     *  or to rotate the viewer in the XZ plane, depending on the selected mode in the
     *  UI (Arc Ball or World crawler)
     */

    Matrix4x4 rotationX = Matrix4x4::RotationX(-difference.elements[1]);
    Matrix4x4 rotationY = Matrix4x4::RotationY(difference.elements[0]);

    Vector3 oldForward(mViewMatrix[2], mViewMatrix[6], mViewMatrix[10]);
    oldForward.normalize();
    oldForward *= -mDistance;

    Matrix4x4 translateToOrigin = Matrix4x4::Translation(oldForward);
    mViewMatrix = mViewMatrix * translateToOrigin;

    mViewMatrix = (mViewMatrix * rotationX) * rotationY;

    Vector3 newForward(mViewMatrix[2], mViewMatrix[6], mViewMatrix[10]);
    newForward.normalize();
    newForward *= mDistance;

    Matrix4x4 translateFromOrigin = Matrix4x4::Translation(newForward);

    mViewMatrix = mViewMatrix * translateFromOrigin;

	mLastMousePos = curPoint;
}

void BasicOpenGLView::keyPressEvent(QKeyEvent *event)
{
    /**
     *  @todo assignment two
     *  if World Crawler mode is selected in the UI, use this method to handle
     *  the keyboard input (either arrow keys or WASD) to create the world crawler
     *  movement and create the mViewMatrix for it
     */
}

void BasicOpenGLView::keyReleaseEvent(QKeyEvent *event)
{
    /**
     *  @todo assignment two
     *  if World Crawler mode is selected in the UI, use this method to handle
     *  the keyboard input (either arrow keys or WASD) to create the world crawler
     *  movement and create the mViewMatrix for it
     */
}

void BasicOpenGLView::wheelEvent(QWheelEvent * e)
{
    int delta = e->delta();

    Vector3 oldForward(mViewMatrix[2], mViewMatrix[6], mViewMatrix[10]);
    oldForward.normalize();
    oldForward *= -mDistance;

    Matrix4x4 translateToOrigin = Matrix4x4::Translation(oldForward);
    mViewMatrix = mViewMatrix * translateToOrigin;

    mDistance -= ((float)delta) / 10.0f;

    Vector3 newForward(mViewMatrix[2], mViewMatrix[6], mViewMatrix[10]);
    newForward.normalize();
    newForward *= mDistance;

    Matrix4x4 translateFromOrigin = Matrix4x4::Translation(newForward);

    mViewMatrix = mViewMatrix * translateFromOrigin;
}

void BasicOpenGLView::translateX(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->translateX(m_Value);
    }
}

void BasicOpenGLView::translateY(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->translateY(m_Value);
    }
}

void BasicOpenGLView::translateZ(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->translateZ(m_Value);
    }
}

void BasicOpenGLView::rotateX(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->rotateX(m_Value);
    }
}

void BasicOpenGLView::rotateY(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->rotateY(m_Value);
    }
}

void BasicOpenGLView::rotateZ(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->rotateZ(m_Value);
    }
}

void BasicOpenGLView::scaleX(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->scaleX(m_Value);
    }
}

void BasicOpenGLView::scaleY(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->scaleY(m_Value);
    }
}

void BasicOpenGLView::scaleZ(float m_Value, std::string m_ModelName)
{
    if(mGeometries.find(m_ModelName) != mGeometries.end())
    {
        mGeometries[m_ModelName]->scaleZ(m_Value);
    }
}




