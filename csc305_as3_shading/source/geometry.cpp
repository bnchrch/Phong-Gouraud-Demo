#include "geometry.h"
#include <iostream>

Geometry::Geometry() : mFileName(),
    mFilePath(),
    mModelMatrix(),
    mNormalMatrix(),
    mColorBuffer(0),
    mNormalBuffer(0),
    mTexCoordBuffer(0),
    mVertexBuffer(0),
    mVertexArray(0),
    mPrimitiveType(POINTS),
    mVertices(),
    mNormals(),
    mTexCoords(),
    mColors(),
    mTranslation(),
    mScale(1.0f, 1.0f, 1.0f),
    mRotation()

{
    initOpenGLBuffers();

    initDefaultShader();
}

Geometry::Geometry(std::string m_FilePath) : mFileName(),
    mFilePath(m_FilePath),
    mModelMatrix(),
    mNormalMatrix(),
    mColorBuffer(0),
    mNormalBuffer(0),
    mTexCoordBuffer(0),
    mVertexBuffer(0),
    mVertexArray(0),
    mPrimitiveType(POINTS),
    mVertices(),
    mNormals(),
    mTexCoords(),
    mColors(),
    mTranslation(),
    mScale(1.0f, 1.0f, 1.0f),
    mRotation()

{
    initOpenGLBuffers();

    initDefaultShader();

    this->parseFile();
}

void Geometry::translateX(float m_Translation)
{
    /**
     *  @todo assignment two
     *  add the new translation to the old one
     */
    mTranslation.x = m_Translation;
}

void Geometry::translateY(float m_Translation)
{
    /**
     *  @todo assignment two
     *  add the new translation to the old one
     */
    mTranslation.y = m_Translation;
}

void Geometry::translateZ(float m_Translation)
{
    /**
     *  @todo assignment two
     *  add the new translation to the old one
     */
    mTranslation.z = m_Translation;
}

void Geometry::scaleX(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale x to the old one
     */
    mScale.x = m_ScaleFactor;
}

void Geometry::scaleY(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale y to the old one
     */
    mScale.y = m_ScaleFactor;
}

void Geometry::scaleZ(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale z to the old one
     */
    mScale.z = m_ScaleFactor;
}

void Geometry::rotateX(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate x to the old one
     */
    mRotation.x = m_Degrees;
}

void Geometry::rotateY(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate y to the old one
     */
    mRotation.y = m_Degrees;
}

void Geometry::rotateZ(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate z to the old one
     */
    mRotation.z = m_Degrees;
}

void Geometry::createModelMatrix(bool m_UsePostMultiply)
{
    /**
     *  @todo assignment two
     * create the model matrix based on the translate, scale and rotation values
     * stored as class members.
     * @param m_UsePostMultiply defines if the single transformation matrices have to be
     * premultiplied or postmultiplied to build the final transformation matrix.
     * store the matrix in mModelMatrix
     */

    Matrix4x4 translation = Matrix4x4::Translation(mTranslation);

    Matrix4x4 rotationX = Matrix4x4::RotationX((mRotation.x * ( 3.1415926535f / 180.0f)));
    Matrix4x4 rotationY = Matrix4x4::RotationY((mRotation.y * ( 3.1415926535f / 180.0f)));
    Matrix4x4 rotationZ = Matrix4x4::RotationZ((mRotation.z * ( 3.1415926535f / 180.0f)));

    Matrix4x4 scale = Matrix4x4::Scale(mScale);
    Matrix4x4 invScale = Matrix4x4::Scale(1.0f/mScale.x, 1.0f/mScale.y, 1.0f/mScale.z);

    if(m_UsePostMultiply)
    {
        mModelMatrix = scale * rotationX * rotationY * rotationZ * translation;
        mNormalMatrix = (invScale * rotationX * rotationY * rotationZ).getMatrix3();
    }
    else
    {
        mModelMatrix = translation * rotationZ * rotationY * rotationX * scale;
        mNormalMatrix = (rotationZ * rotationY * rotationX * invScale).getMatrix3();
    }

}
