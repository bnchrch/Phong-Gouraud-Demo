#ifndef BASICOPENGLVIEW_H
#define BASICOPENGLVIEW_H

#ifndef __APPLE__
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <QGLWidget>
#include <QMatrix4x4>
#include <QTime>
#include "geometry.h"


/**
  * @class  BasicOpenGLView
  * @brief  our OpenGL view derived from QGLWidget.
  * We have to override several functions for our
  * application-specific OpenGL drawing functionality
  */
class BasicOpenGLView : public QGLWidget
{
    /**
      * macro needed to be inserted in every QT derived class.
      */
    Q_OBJECT
public:

    /**
      * our constructor
      * @param  parent the parent object of the widget.
                pass this one on to the superclass constructor
      */
    explicit BasicOpenGLView(QWidget *parent = 0);

    /**
     * @brief loadGeometry
     * loads the geometry at the given path
     * @param m_GeometryPath the full path to the geometry file
     */
    void loadGeometry(std::string m_GeometryPath);

    /**
     * @brief removeGeometry
     * removes all occurences of the geometry with the given filename
     * @param m_GeometryFileName the filename of the geometry
     */
    void removeGeometry(std::string m_GeometryFileName);

    /**
     * @brief loadMaterial
     * loads a material object
     * @param m_MaterialPath the full path to the material file
     */
    void loadMaterial(std::string m_Material);

    /**
     * @brief setOrtho
     * @param m_RenderOrtho if orthographic rendering is on
     */
    void setOrtho(bool m_RenderOrtho);

    /**
     * @brief setPostMultiply
     * @param m_PostMultiply if postmultiply should be used
     */
    void setPostMultiply(bool m_PostMultiply);

    /**
     * @brief translateX
     * @param m_Value
     * @param m_ModelName
     */
    void translateX(float m_Value, std::string m_ModelName);

    /**
     * @brief translateY
     * @param m_Value
     * @param m_ModelName
     */
    void translateY(float m_Value, std::string m_ModelName);

    /**
     * @brief translateZ
     * @param m_Value
     * @param m_ModelName
     */
    void translateZ(float m_Value, std::string m_ModelName);

    /**
     * @brief rotateX
     * @param m_Value
     * @param m_ModelName
     */
    void rotateX(float m_Value, std::string m_ModelName);

    /**
     * @brief rotateY
     * @param m_Value
     * @param m_ModelName
     */
    void rotateY(float m_Value, std::string m_ModelName);

    /**
     * @brief rotateZ
     * @param m_Value
     * @param m_ModelName
     */
    void rotateZ(float m_Value, std::string m_ModelName);

    /**
     * @brief scaleX
     * @param m_Value
     * @param m_ModelName
     */
    void scaleX(float m_Value, std::string m_ModelName);

    /**
     * @brief scaleY
     * @param m_Value
     * @param m_ModelName
     */
    void scaleY(float m_Value, std::string m_ModelName);

    /**
     * @brief scaleZ
     * @param m_Value
     * @param m_ModelName
     */
    void scaleZ(float m_Value, std::string m_ModelName);

signals:

    /**
     * @brief addedNewGeometry
     * signal is emitted when a new geometry is added to the scene
     * @param m_GeometryName the name of the geometry
     */
    void addedNewGeometry(std::string m_GeometryName);

    /**
     * @brief removedGeometry
     * signal is emitted when a geometry object is removed from the scene
     * @param m_GeometryName the name of the geometry
     */
    void removedGeometry(std::string m_GeometryName);

public slots:

protected:

    /**
      * function called automatically by QT after the OpenGL context is created
      * in here, do all OpenGL setup stuff, that you can before the actual program
      * execution starts
      */
    void initializeGL();

    /**
      * the function called whenever our Widget is being redrawn.
      * assume that the BasicOpenGLView's OpenGL context has already
      * been made the current one, so no need to call
      * this->makeCurrent(); anymore
      * Do all your rendering loop related code in there
      */
    void paintGL();

    /**
      * method called when the widget is resized.
      * we need code in there, to react to the changed window size
      * otherwise the rendering will look skewed and ugly
      */
    void resizeGL(int width, int height);

    /**
      * function called when a mouse button is pressed and the cursor is hovering
      * over our widget
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mousePressEvent(QMouseEvent *event);
	
	/**
	 * function called when a mouse button is released and/or the cursor stopped hovering
	 * over our widget
	 * use the QMouseEvent classmembers to access the mouse information
	 */
	void mouseReleaseEvent(QMouseEvent *event);

    /**
      * function called when mouse cursor is moved inside our widgets region
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * keyPressEvent is called when the window has focus and a key on the
     * keyboard is pressed
     * @param event
     */
    void keyPressEvent ( QKeyEvent * event );

    /**
     * keyReleaseEvent is called when the window has focus and a key on the
     * keyboard is released
     * @param event
     */
    void keyReleaseEvent ( QKeyEvent * event );

    /**
     * the wheel event function
     * @param event the wheel event
     */
    void wheelEvent(QWheelEvent * e);

private:

    Matrix4x4       mProjectionMatrix;              /**< the projection matrix to be used for rendering. */
    Matrix4x4       mViewMatrix;                    /**< the view matrix to be used for rendering. */
    bool            mUsePostMultiply;               /**< if the post multiply has to be used for the matrices. */
    std::map<std::string, Geometry *>   mGeometries;    /**< the map containing the filename of the geometry as key, and the pointer to the geometry as value. */
	
	bool	mFirstFrameDragging;			/**< if we are in the first dragging frame. */
	Vector3	mLastMousePos;					/**< the last mouse position while dragging. */
    float mDistance;                        /**< the distance the camera is from the scene origin. */
    bool mRenderOrtho;                      /**< if orthographic projection is selected. */

    GLuint  mTextureHandle;                 /**< the handle for a texture, if present. */
    GLuint  mBumpTextureHandle;             /**< the handle for the bump texture, if present. */
    Program * mProgram;                     /**< program to override the shaders used for rendering. */
    Vector3 mLightPos;                      /**< the position of the light source. */
    Vector4 mLightCol;                      /**< the color of the light source. */

    QTime   mAnimationTimer;                /**< timer used in the animation of the light. */
};

#endif // BASICOPENGLVIEW_H
