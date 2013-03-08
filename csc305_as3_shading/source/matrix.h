#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "vector.h"

/**
 *  @todo assignment two
 *  1. extend these matrix classes to support all the basic linear algebra functions
 *  (add, subtract, multiply)
 *  2. add convenience functions to create scale & rotation matrices around the available axes,
 *  and a translation matrix
 *  3. add functions to create the projection matrix versions.
 *  for perspective projection, this function should take the field of view, image ratio, near plane and far plane distance
 *  for orthographic projection it should take the left, right, top, bottom, near plane and far plane values
 *  4. add functions to create the view matrix using eye position, at position and the up vector
 */

/**
 *	@class	Matrix3x3
 *	@brief	3 by 3 Matrix class
 *	Homogenous 3x3 Matrix, onedimensional array (like opengl), column major
 *	|0 3 6|
 *	|1 4 7|
 *	|2 5 8|
 */
class Matrix3x3
{
public:

    float elements[9];/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix3x3();

    /**
     *	copy constructor
     *	@param	m the new matrix
     */
    Matrix3x3(const Matrix3x3 & m);

    /**
     *	constructor with vector of values
     *	@param	v the vector
     */
    Matrix3x3(std::vector<float> & v);

    /**
     *	generates the identity matrix
     */
    void loadIdentity();

    /**
     *	returns the transposed matrix
     *	@return	returns new matrix
     */
    Matrix3x3 getTranspose();

    /**
     *	transposes the matrix
     */
    void transpose();

    /**
     *	Transform a Vector3 (w assumed to be 1) without division by w.
     *	(effectively only a rotation).
     *	@param	v the vector
     *	@return	returns the transformed vector
     */
    Vector3 transform(const Vector3 & v);

    /**
     *	access operator
     *	@param	n the index in the array
     *	@return	returns reference to the value
     */
    float & operator [] (unsigned int n);

    /**
     *	access operator
     *	@param	n the index in the array
     *	@return	returns the value
     */
    float operator [] (unsigned int n) const;

    /**
     *	multiplication operator
     *	@param	m1 the first matrix
     *	@param	m2 the second matrix
     *	@return	returns the resulting matrix
     */
    friend Matrix3x3 operator *(const Matrix3x3 & m1, const Matrix3x3 & m2)
    {
        std::vector<float> temp(9);
        temp[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
        temp[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
        temp[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];
        temp[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m2[5];
        temp[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m2[5];
        temp[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m2[5];
        temp[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m2[8];
        temp[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m2[8];
        temp[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m2[8];

        return Matrix3x3(temp);
    }

    /**
     *	addition operator
     *	@param	m1 the first matrix
     *	@param	m2 the second matrix
     *	@return	returns the resulting matrix
     */
    friend Matrix3x3 operator +(const Matrix3x3 & m1, const Matrix3x3 & m2)
    {
        std::vector<float> temp(9);
        for(int i = 0; i < 9; ++i)
        {
            temp[i] = m1[i] + m2[i];
        }
        return Matrix3x3(temp);

    }

    /**
     *	multiplication of matrix with vector
     *	@param	m the matrix
     *	@param	v the vector
     *	@return	returns a vector containing the result
     */
    friend Vector3 operator *(const Matrix3x3 & m, const Vector3 & v)
    {
        float x = m[0] * v.x + m[3] * v.y + m[6] * v.z;
        float y = m[1] * v.x + m[4] * v.y + m[7] * v.z;
        float z = m[2] * v.x + m[5] * v.y + m[8] * v.z;

        return Vector3(x, y, z);
    }
};

/**
 *	@class	Matrix4x4
 *	@brief	4 by 4 matrix
 *	Homogenous 4x4 Matrix, onedimensional array (like opengl), column major
 *	|0 4 8  12|
 *	|1 5 9  13|
 *	|2 6 10 14|
 *	|3 7 11 15|
 */
class Matrix4x4
{
public:

    float elements[16];	/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix4x4();

    /**
     *	copy constructor
     *	@param	m the new matrix
     */
    Matrix4x4(const Matrix4x4 & m);

    /**
     *	constructor with vector of values
     *	@param	v the vector
     */
    Matrix4x4(std::vector<float> v);

    /**
     *	generates the identity matrix
     */
    void loadIdentity();

    /**
     * @brief lookAt
     * creates a view matrix based on the three parameters
     * @param m_Eye where the eye is
     * @param m_At where it looks at
     * @param m_Up the up vector
     */
    void lookAt(Vector3 m_Eye,
                Vector3 m_At,
                Vector3 m_Up);

    /**
     * @brief perspective
     * creates a perspective projection matrix
     * @param m_Angle the field of view angle
     * @param m_AspectRatio the aspect ratio
     * @param m_Near the near plane
     * @param m_Far the far plane
     */
    void perspective(float m_Angle,
                     float m_AspectRatio,
                     float m_Near,
                     float m_Far);

    /**
     * @brief ortho
     * creates an orthogonal projection matrix
     * @param m_Left the left value
     * @param m_Right the right value
     * @param m_Top the top value
     * @param m_Bottom the bottom value
     * @param m_Near the near value
     * @param m_Far the far value
     */
    void ortho(float m_Left,
               float m_Right,
               float m_Top,
               float m_Bottom,
               float m_Near,
               float m_Far);

    /**
     *	static method to construct a translation matrix
     *	@param	x the translation in x
     *	@param	y the translation in y
     *	@param	z the translation in z
     *	@return	returns the matrix
     */
    static Matrix4x4 Translation(const float x, const float y, const float z);

    /**
     *	static method to construct a translation matrix
     *	@param	v the translation vector
     *	@return	returns the matrix
     */
    static Matrix4x4 Translation(const Vector3 & v);

    /**
     *	static methdo to construct a rotation matrix in x
     *	@param	angleRad the angle of the rotation
     *	@return	returns the matrix
     */
    static Matrix4x4 RotationX(const float angleRad);

    /**
     *	static methdo to construct a rotation matrix in y
     *	@param	angleRad the angle of the rotation
     *	@return	returns the matrix
     */
    static Matrix4x4 RotationY(const float angleRad);

    /**
     *	static methdo to construct a rotation matrix in z
     *	@param	angleRad the angle of the rotation
     *	@return	returns the matrix
     */
    static Matrix4x4 RotationZ(const float angleRad);

    /**
     *	static method to construct a scale matrix
     *	@param	x scale in x
     *	@param	y scale in y
     *	@param	z scale in z
     *	@return	returns the matrix
     */
    static Matrix4x4 Scale(const float x, const float y, const float z);

    /**
     *	static method to construct a scale matrix
     *	@param	v the scale vector
     *	@return	returns the matrix
     */
    static Matrix4x4 Scale(Vector3 &v);

    /**
     *	access operator
     *	@param	n the index in the array
     *	@return	returns reference to the value
     */
    float & operator [] (unsigned int n);

    /**
     *	access operator
     *	@param	n the index in the array
     *	@return	returns the value
     */
    float operator [] (unsigned int n) const;


    /**
     *	equality operator
     *	@param	a the first matrix
     *	@param	b the second matrix
     *	@return	returns if they are equal
     */
    friend bool operator == (const Matrix4x4 & a, const Matrix4x4 & b)
    {
        for (int i = 0; i < 16; i++)
        {
            if (a[i] != b[i]) return false;
        }
        return true;
    }

    /**
     *	inequality operator
     *	@param	a the first matrix
     *	@param	b the second matrix
     *	@return	returns if they are not equal
     */
    friend bool operator != (const Matrix4x4 & a, const Matrix4x4 & b)
    {
        for (int i = 0; i < 16; i++)
        {
            if (a[i] != b[i]) return true;
        }
        return false;
    }

    /**
     *	multiplication operator
     *	@param	m1 the first matrix
     *	@param	m2 the second matrix
     *	@return	returns the resulting matrix
     */
    friend Matrix4x4  operator * (const Matrix4x4 & a, const Matrix4x4 & b)
    {
        float sum;
        Matrix4x4 result;
        int x, y, i;
        for (x=0; x<4; x++)
        {
            for (y=0; y<4; y++)
            {
                sum=0;
                for (i=0; i<4; i++) sum+=a[y+4*i]*b[4*x+i];
                result[y+4*x]=sum;
            }
        }
        return result;
    }

    /**
     *	operator for scalar multiplication
     *	@param	v the scalar
     *	@return	returns the new matrix
     */
    Matrix4x4 operator * (const float & v);

    /**
     *	operator for scalar multiplication
     *	@param	v the scalar
     *	@return	returns the new matrix
     */
    Matrix4x4 operator *= (const float & v);

    /**
     *	assignment operator
     *	@param	b the new matrix
     *	@return	returns the changed matrix
     */
    Matrix4x4 & operator = (const Matrix4x4 b);

    /**
     *	Transform a Vector4 and divide by result w.
     *	@param	v the vector
     *	@return	returns the result
     */
    Vector4 homogenTransform(const Vector4 & v);

    /**
     *	Transform a Vector3 (w assumed to be 1) and divide by result w.
     *	@param	v the vector
     *	@return	returns the result
     */
    Vector3 homogenTransform(const Vector3 & v);

    /**
     *	Transform a Vector3
     *	@param	v the vector
     *	@return	returns the result
     */
    Vector3 transform(const Vector3 & v);

    /**
     *	Transform a Vector4 without division by w.
     *	@param	v the vector
     *	@return	returns the result
     */
    Vector4 transform(const Vector4 & v);

    /**
     *	get the matrix' determinant.
     *	@return	returns the determinant
     */
    float getDeterminant();

    /**
     *	inverts the matrix
     */
    void invert();

    /**
     *	returns the inverse of the matrix
     *	@return	returns a new matrix containing the result
     */
    Matrix4x4 getInverse();

    /**
     * @brief getMatrix3
     * @return returns the upper left matrix 3x3
     */
    Matrix3x3 getMatrix3();

    /**
     *	transposes the matrix.
     */
    void transpose();

    /**
     *	returns the transposed matrix
     *	@return	returns a new matrix containing the transposed
     */
    Matrix4x4 getTranspose();

    /**
     *	converts the matrix to a string for readability
     *	@return	returns a string containing the values
     */
    std::string toString() const;

};

#endif // MATRIX_H
