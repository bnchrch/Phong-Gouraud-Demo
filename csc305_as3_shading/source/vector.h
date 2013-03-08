#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <assert.h>

/**
 *  @todo assignment two
 *  extend these classes to support the basic linear algebra functions, including dot and cross product
 */

/**
 * @brief The Vector3 class
 * represents a 3 dimensional vector.
 * given a Vector3 myVec3; the single elements can either
 * be accessed using myVec3.x myVec3.y myVec3.z or myVec3.elements[index]
 */
class Vector3
{
public:

    /**
     * we use a union, so the three values x,y,z and elements[3] occupy the
     * same region in memory, this we can use both of them for reading and
     * writing to the elements.
     */
    union
    {
        struct
        {
            float x, y, z;
        };
        float elements[3];
    };

    /**
     * @brief Vector3 constructor
     * @param m_x the x value
     * @param m_y the y value
     * @param m_z the z value
     */
    Vector3(float m_x = 0.0f, float m_y = 0.0f, float m_z = 0.0f);

    /**
     *	copy constructor
     *	@param	m_v the vector
     */
    Vector3(const Vector3 & m_v);

    /**
     *	static method to create the cross product of two vectors
     *	@param	v1 the first vector
     *	@param	v2 the second vector
     *	@return	returns a vector containing the cross product
     */
    static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);

    /**
     *	method computing the length of the vector
     *	@return	returns the length of the vector
     */
    inline float getLength() const
    {
        return sqrt(this->getSqrLength());
    }

    /**
     *	method computing the squared length of the vector
     *	@return	returns the squared length
     */
    inline float getSqrLength() const
    {
        return x*x + y*y + z*z;
    }

    /**
     *	normalizes the vector
     */
    inline void normalize()
    {
        float tmp = this->getLength();
        if(tmp != 0)
        {
            x /= tmp;
            y /= tmp;
            z /= tmp;
        }
    }

    /**
     *	assignment operator
     *	@param	v the new value
     *	@return	returns a reference to the new vector
     */
    Vector3 & operator = (const Vector3 & v);

    /**
     *	add to self operator
     *	@param	v the vector to add to this
     *	@return	returns reference to the value with v added
     */
    Vector3 & operator +=(const Vector3 & v);

    /**
     *	subtract from self operator
     *	@param	v the vector to subtract from this
     *	@return	returns the reference to the value with v subtracted
     */
    Vector3 & operator -=(const Vector3 & v);

    /**
     *	multiply self with operator
     *	@param	m the value to multiply self with
     *	@return	returns the reference to the value multiplied by m
     */
    Vector3 & operator*= (const  float & m);

    /**
     *	divide self by operator
     *	@param	m the value to divide self by
     *	@return	returns the reference to the value divided by m
     */
    Vector3 & operator/= (const  float & m);

    /**
     *	equality operator
     *	@param	a the first vector
     *	@param	b the second vector
     *	@return	returns if they are equal
     */
    friend bool operator == (const Vector3 & a, const Vector3 & b)
    {
        return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
    }

    /**
     *	inequality operator
     *	@param	a the first vector
     *	@param	b the second vector
     *	@return	returns if they are not equal
     */
    friend bool operator != (const Vector3 &a, const Vector3 & b)
    {
        return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z));
    }

    /**
     *	negation operator
     *	@param	v the input vector
     *	@return	returns the negated input
     */
    friend Vector3 operator - (const Vector3 & v)
    {
        return Vector3 (-v.x, -v.y, -v.z);
    }

    /**
     *	summation operator
     *	@param	a first vector
     *	@param	b second vector
     *	@return	returns the sum
     */
    friend Vector3  operator + (const Vector3 & a, const Vector3 & b)
    {
        return Vector3 (a.x + b.x, a.y + b.y, a.z + b.z);
    }

    /**
     *	subtraction operator
     *	@param	a first vector
     *	@param	b second vector
     *	@return	returns the subtraction
     */
    friend Vector3  operator - (const Vector3 & a, const Vector3 & b)
    {
        return Vector3 (a.x - b.x, a.y - b.y, a.z - b.z);
    }

    /**
     *	multiplication operator
     *	@param	a first vector
     *	@param	b second vector
     *	@return	returns the multiplication
     */
    friend float  operator * (const Vector3 & a, const Vector3 & b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    /**
     *	multiplies the vector with a constant value
     *	@param	v the vector
     *	@param	m the constant value
     *	@return	returns the multiplication
     */
    friend Vector3  operator * (const Vector3 & v, const float & b)
    {
        return Vector3 (v.x * b, v.y * b, v.z * b);
    }

    /**
     *	multiplies a vector by a constant
     *	@param	b the constant value
     *	@param	v the vector
     *	@return	returns the multiplication
     */
    friend Vector3  operator * (const float & b, const Vector3 & v)
    {
        return Vector3 (v.x * b, v.y * b, v.z * b);
    }

};

/**
 * @brief The Vector4 class
 * represents a 4 dimensional vector.
 * given a Vector4 myVec4; the single elements can either
 * be accessed using myVec4.x myVec4.y myVec4.z myVec4.w or myVec4.elements[index]
 */
class Vector4
{
public:

    /**
     * we use a union, so the four values x,y,z,w and elements[4] occupy the
     * same region in memory, this we can use both of them for reading and
     * writing to the elements.
     */
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float elements[4];
    };

    /**
     * @brief Vector4
     * @param m_x the x value
     * @param m_y the y value
     * @param m_z the z value
     * @param m_w the w value
     */
    Vector4(float m_x = 0.0f, float m_y = 0.0f, float m_z = 0.0f, float m_w = 1.0f);

    /**
     *	copy constructor
     *	@param	m_v the other vector
     */
    Vector4(const Vector4 & m_v)
    : x(m_v.x), y(m_v.y), z(m_v.z), w(m_v.w)
    {
    }

    /**
     *	normalizes the vector
     */
    inline void normalize()
    {
        x /= w;
        y /= w;
        z /= w;
        w = 1;
    }

    /**
     *	returns the corresponding vector 3
     *	@return	returns the Vector3
     */
    Vector3  getVector3();

    /**
     *	assignment operator
     *	@param	m_v the new vector
     *	@return	returns a reference to a new vector with the given value.
     */
    Vector4 & operator = (const Vector4 & v);

    /**
     *	add assignment operator
     *	@param	m_v the vector to add to this
     *	@return	returns reference to the incremented vector
     */
    Vector4 & operator +=(const Vector4 & v);

    /**
     *	subtract assignment operator
     *	@param	m_v the vector to subtract from this
     *	@return	returns reference to the subtracted vector
     */
    Vector4 & operator -=(const Vector4 & v);

    /**
     *	multiply assignment operator
     *	multiplies the vector with a constant value
     *	@param	m the constant
     *	@return	returns self multiplied by m
     */
    Vector4 & operator*= (const float & m);

    /**
     *	divide assignment operator
     *	divides the vector with a constant value
     *	@param	m the constant
     *	@return	returns self divided by m
     */
    Vector4 & operator/= (const float  & m);

    /**
     *	equality operator
     *	@param	a the first vector
     *	@param	b the second vector
     *	@return	returns if both are equal
     */
    friend bool operator == (const Vector4 & a, const Vector4 & b)
    {
        return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
    }

    /**
     *	not equality operator
     *	@param	a the first vector
     *	@param	b the second vector
     *	@return	returns if both are not equal
     */
    friend bool operator != (const Vector4 &a, const Vector4 & b)
    {
        return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z) || (a.w != b.w));
    }

    /**
     *	negation operator
     *	@param	v the vector to negate
     *	@return	returns the negated vector
     */
    friend Vector4  operator - (const Vector4 & v)
    {
        return Vector4 (-v.x, -v.y, -v.z, -v.w);
    }

    /**
     *	summation operator
     *	@param	a the first vector
     *	@param	b the second vector
     *	@return	returns the sum of both vectors
     */
    friend Vector4  operator + (const Vector4 & a, const Vector4 & b)
    {
        return Vector4 (a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }

    /**
     *	subtraction operator
     *	@param	a the first vector
     *	@param	b the second vector
     *	@return	returns the difference of a and b
     */
    friend Vector4  operator - (const Vector4 & a, const Vector4 & b)
    {
        return Vector4 (a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    /**
     *	multiplication operator.
     *	dot product
     *	@param	a the first vector
     *	@param	b the second vector
     *	@return	returns the dot product
     */
    friend float  operator * (const Vector4 & a, const Vector4 & b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w + b.w);
    }

    /**
     *	multiplication of a constant
     *	@param	v the vector
     *	@param	b the constant
     *	@return	returns the vector multiplied by the constant
     */
    friend Vector4  operator * (const Vector4 & v, const float & b)
    {
        return Vector4 (v.x * b, v.y * b, v.z * b, v.w * b);
    }

    /**
     *	multiplication with a constant
     *	@param	b the constant
     *	@param	v the vector
     *	@return	returns the vector multiplied by the constant
     */
    friend Vector4  operator * (const float & b, const Vector4 & v)
    {
        return Vector4 (v.x * b, v.y * b, v.z * b, v.w * b);
    }
};

#endif // VECTOR_H
