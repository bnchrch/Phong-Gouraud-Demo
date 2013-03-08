#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"
#include <vector>
#include <string>
#include "supporting_files/s_program.h"
#include "matrix.h"

/**
 * @brief The Geometry class
 * most of the methods are already implemented in supporting_files/geometry.cpp
 */
class Geometry
{
public:

    /**
     *	@brief	primitive enums for drawing
     *	parts map to opengl
     */
    typedef enum
    {
        POINTS			= 0x0000,	/**< maps to GL_POINTS. */
        LINES			= 0x0001,	/**< maps to GL_LINES. */
        LINE_LOOP		= 0x0002,	/**< maps to GL_LINE_LOOP. */
        LINE_STRIP      = 0x0003,	/**< maps to GL_LINE_STRIP. */
        TRIANGLES       = 0x0004,	/**< maps to GL_TRIANGLES. */
        TRIANGLE_STRIP  = 0x0005,	/**< maps to GL_TRIANGLE_STRIP. */
        TRIANGLE_FAN    = 0x0006,	/**< maps to GL_TRIANGLE_FAN. */

        QUADS,						/**< compatibility for quads. we are triangulating them. */
        QUAD_STRIP					/**< compatibility for quad strips. we are triangulating them. */
    }
    primitive;

    /**
     * @brief Geometry
     */
    Geometry();

    /**
     * @brief Geometry
     * @param m_FilePath the path to the obj file to load
     */
    Geometry(std::string m_FilePath);

    /**
     * @brief ~Geometry
     */
    virtual ~Geometry();

    /**
     *  @brief draw
     *  draws the geometry to the screen
     *  @param  m_Program the shader program to be used for drawing
     *  @param  m_ProjectionMatrix the projection matrix to be used for renderin
     *  @param  m_ViewMatrix the view matrix to be used for rendering
     *  @param  m_UsePostMultiply if the modelmatrix has to be post multiplied with the positions
     *  @param  m_LightPos the position of the light
     *  @param  m_LightCol the color of the light
     *  @param  m_TextureHandle the handle for the texture
     *  @param  m_BumpTextureHandle the handle for the bump map
     */
    void draw(Matrix4x4 & m_ProjectionMatrix,
              Matrix4x4 & m_ViewMatrix,
              bool m_UsePostMultiply,
              Vector3 & m_LightPos,
              Vector4 & m_LightCol,
              uint32_t m_TextureHandle,
              uint32_t m_BumpTextureHandle,
              Program * m_Program = NULL);

    /**
     * @brief getFileName
     * @return returns the file name of our geometry
     */
    std::string getFileName() const;

    /**
     * @brief getFilePath
     * @return returns the full path of our geometry
     */
    std::string getFilePath() const;


    /**
     *  @todo assignment two start
     *  implement the following methods in geometry.cpp. The method skeletons are already present
     *  store the transformations in separate values (e.g. a Vector3 for the aggregated Translation)
     *  only the updateModelMatrix() function should then create the proper matrices and multiply them
     *  to build mModelMatrix
     *  implement the following functions:
     *  translate
     *  scaleX
     *  scaleY
     *  scaleZ
     *  rotateX
     *  rotateY
     *  rotateZ
     *  createModelMatrix
     */

	/**
     *	translates each vertex by the given translation in x
	 *	@param	m_Translation the translation vector
	 */
    void translateX(float m_Translation);

    /**
     *	translates each vertex by the given translation in y
     *	@param	m_Translation the translation vector
     */
    void translateY(float m_Translation);

    /**
     *	translates each vertex by the given translation in z
     *	@param	m_Translation the translation vector
     */
    void translateZ(float m_Translation);

    /**
     * @brief scaleX
     * @param m_ScaleFactor the new scale factor for X
     */
    void scaleX(float m_ScaleFactor);

    /**
     * @brief scaleY
     * @param m_ScaleFactor the new scale factor for Y
     */
    void scaleY(float m_ScaleFactor);

    /**
     * @brief scaleZ
     * @param m_ScaleFactor the new scale factor for Z
     */
    void scaleZ(float m_ScaleFactor);

    /**
     * @brief rotateX
     * @param m_Degrees the number of degrees to rotate in X
     */
    void rotateX(float m_Degrees);

    /**
     * @brief rotateY
     * @param m_Degrees the number of degrees to rotate in Y
     */
    void rotateY(float m_Degrees);

    /**
     * @brief rotateZ
     * @param m_Degrees the number of degrees to rotate in Z
     */
    void rotateZ(float m_Degrees);

    /**
     * @brief createModelMatrix
     * creates the model matrix based on the translate, scale and rotation values
     * stored as class members.
     * @param m_UsePostMultiply defines if the single transformation matrices have to be
     * premultiplied or postmultiplied to build the final transformation matrix.
     */
    void createModelMatrix(bool m_UsePostMultiply);

    /**
     *  @todo assignment two end
     */

private:

    /**
     *  @brief parseFile
     *  method that parses the obj file
     */
    void parseFile();
	
	/**
	 *	converts the model stored as quads into triangles
	 */
	void convertQuadsToTriangles();
	
	/**
	 *	initialises the OpenGL buffers we need for drawing
	 */
	void initOpenGLBuffers();
	
	/**	
	 *	initializes the default shader
	 *	@return	returns if success
	 */
	bool initDefaultShader();

     std::string    mFileName;              /**< the file name of the model if set. */
     std::string    mFilePath;              /**< the full cannonical path to the model file, if set. */

     Matrix4x4      mModelMatrix;           /**< the model matrix. */
     Matrix3x3      mNormalMatrix;          /**< the normal matrix. */

    unsigned int mColorBuffer;				/**< handle for the color buffer. */
    unsigned int mNormalBuffer;				/**< handle for the normal buffer. */
    unsigned int mTexCoordBuffer;			/**< handle for the texture coordinate buffer. */
    unsigned int mVertexBuffer;				/**< handle for the vertex buffer. */

    unsigned int mVertexArray;				/**< the VAO handle. */

    primitive				mPrimitiveType;		/**< the drawing primitivetype. */

    std::vector<Vector3>	mVertices;		/**< the array for the vertices. */
    std::vector<Vector3>	mNormals;		/**< the array for the normals. */
    std::vector<Vector3>	mTexCoords;		/**< the array for the texture coordinates.
											 *	2d texture coordinates are expanded to have 0 in z. */
    std::vector<Vector4>	mColors;		/**< the array for the colors.
                                                 *	The w is added with 1, when not present. */
    Program    * mProgram;          /**< the shader program we use to render our geometry. */

    Vector3     mTranslation;       /**< the current translation. */
    Vector3     mScale;             /**< the current scale. */
    Vector3     mRotation;          /**< the current rotation. */
};


#endif // GEOMETRY_H
