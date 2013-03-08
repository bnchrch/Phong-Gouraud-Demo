#include "matrix.h"

#include <sstream>

Matrix3x3::Matrix3x3()
{
    this->loadIdentity();
}

Matrix3x3::Matrix3x3(const Matrix3x3 & m)
{
    for(int i = 0; i < 9; ++i)
    {
        elements[i] = m.elements[i];
    }
}

Matrix3x3::Matrix3x3(std::vector<float> & v)
{
    for(int i = 0; i < 9; ++i)
    {
        elements[i] = v[i];
    }
}

void Matrix3x3::loadIdentity()
{
    elements[0] = elements[4] = elements[8] = 1;
    elements[1] = elements[2] = elements[3] = elements[5] = elements[6] = elements[7] = 0;
}

Matrix3x3 Matrix3x3::getTranspose()
{

    std::vector<float> tmp(9);

    for (int i = 0; i < 3; i++)
    {
        tmp[3 * i] = elements[i];
        tmp[3 * i + 1] = elements[i + 3];
        tmp[3 * i + 2] = elements[i + 6];
    }

    return Matrix3x3(tmp);
}

void Matrix3x3::transpose()
{
    (*this) = getTranspose();
}

Vector3 Matrix3x3::transform(const Vector3 & v)
{
    float x, y, z;
    x=elements[0]*v.x+elements[3]*v.y+elements[6]*v.z;
    y=elements[1]*v.x+elements[4]*v.y+elements[7]*v.z;
    z=elements[2]*v.x+elements[5]*v.y+elements[8]*v.z;
    return Vector3(x, y, z);
}

float & Matrix3x3::operator [] (unsigned int n)
{
    if(n > 8) n = 8;
    return elements[n];
}

float Matrix3x3::operator [] (unsigned int n) const
{
    if(n > 8) n = 8;
    return elements[n];
}

Matrix4x4::Matrix4x4()
{
    loadIdentity();
}

Matrix4x4::Matrix4x4(const Matrix4x4 & m)
{
    for(size_t i = 0; i < 16; ++i)
    {
        elements[i] = m.elements[i];
    }
}

Matrix4x4::Matrix4x4(std::vector<float> v)
{
    for(size_t i = 0; i < 16; ++i)
    {
        elements[i] = v[i];
    }
}

void Matrix4x4::loadIdentity()
{
    elements[0] = elements[5] = elements[10] = elements[15] = 1;
    elements[1] = elements[2] = elements[3] = elements[4] = elements[6] = elements[7]
            = elements[8] = elements[9] = elements[11] = elements[12] = elements[13] = elements[14] = 0;
}

void Matrix4x4::lookAt(Vector3 m_Eye,
                       Vector3 m_At,
                       Vector3 m_Up)
{
    this->loadIdentity();

    Vector3 side;
    Vector3 view = m_At - m_Eye;
    Vector3 up = m_Up;

    view.normalize();
    up.normalize();

    /* Side = forward x up */
    side = Vector3::CrossProduct(view, up);
    side.normalize();

    up = Vector3::CrossProduct(side, view);
    up.normalize();

    elements[0] = side.x;
    elements[4] = side.y;
    elements[8] = side.z;

    elements[1] = up.x;
    elements[5] = up.y;
    elements[9] = up.z;

    elements[2] = -view.x;
    elements[6] = -view.y;
    elements[10] = -view.z;

    Vector3 invEye = -m_Eye;

    Matrix4x4 temp = Matrix4x4::Translation(invEye);
    (*this) = (*this) * temp;
}

void Matrix4x4::perspective(float m_Angle,
                            float m_AspectRatio,
                            float m_Near,
                            float m_Far)
{
    float radian = ((m_Angle/2) * ( 3.1415926535f / 180.0f));
    float tanFov = tan(radian);
    float right = m_AspectRatio * tanFov * m_Near;
    float left = -right;
    float top = tanFov * m_Near;
    float bottom = -top;

    this->loadIdentity();
    elements[0] = (2.0f * m_Near) / (right - left);
    elements[5] = (2.0f * m_Near) / (top - bottom);
    elements[8] = (right + left) / (right - left);
    elements[9] = (top + bottom) / (top - bottom);
    elements[10] = (-(m_Far + m_Near)) / (m_Far - m_Near);
    elements[11] = -1.0f;
    elements[14] = (-(2.0f * m_Near * m_Far) / (m_Far - m_Near));
    elements[15] = 0.0f;
}

void Matrix4x4::ortho(float m_Left,
                      float m_Right,
                      float m_Top,
                      float m_Bottom,
                      float m_Near,
                      float m_Far)
{
    this->loadIdentity();
    elements[0] = (2.0f) / (m_Right - m_Left);
    elements[5] = (2.0f) / (m_Top - m_Bottom);
    elements[10] = (2.0f) / (m_Far - m_Near);

    elements[12] = (-(m_Left + m_Right) / (m_Right - m_Left));
    elements[13] = (-(m_Bottom + m_Top) / (m_Top - m_Bottom));
    elements[14] = (-(m_Near + m_Far) / (m_Far - m_Near));
}

Matrix4x4 Matrix4x4::Translation(const float x, const float y, const float z)
{
    Matrix4x4 m;
    m[12] = x;
    m[13] = y;
    m[14] = z;
    return m;
}

Matrix4x4 Matrix4x4::Translation(const Vector3 & v)
{
    return Translation(v.x, v.y, v.z);
}

Matrix4x4 Matrix4x4::RotationX(const float angleRad)
{
    Matrix4x4 m;

    float cosine = cos(angleRad);
    float sinus = sin(angleRad);

    //  |  1  0       0       0 |
    //M=|  0  cos(A) -sin(A)  0 |
    //  |  0  sin(A)  cos(A)  0 |
    //  |  0  0       0       1 |
    m[0]=1; m[4]=0;			m[8]=0;			m[12]=0;
    m[1]=0; m[5]=cosine;	m[9]=-sinus;	m[13]=0;
    m[2]=0; m[6]=sinus;		m[10]=cosine;	m[14]=0;
    m[3]=0; m[7]=0;         m[11]=0;        m[15]=1;
    return m;
}

Matrix4x4 Matrix4x4::RotationY(const float angleRad)
{
    Matrix4x4 m;

    float cosine = cos(angleRad);
    float sinus = sin(angleRad);

    //  |  cos(A)  0  sin(A)  0 |
    //M=|  0       1  0       0 |
    //  | -sin(A)  0  cos(A)  0 |
    //  |  0       0  0       1 |
    m[0]=cosine;	m[4]=0; m[8]=sinus;		m[12]=0;
    m[1]=0;         m[5]=1; m[9]=0;         m[13]=0;
    m[2]=-sinus;	m[6]=0; m[10]=cosine;	m[14]=0;
    m[3]=0;         m[7]=0; m[11]=0;        m[15]=1;
    return m;
}

Matrix4x4 Matrix4x4::RotationZ(const float angleRad)
{
    Matrix4x4 m;

    float cosine = cos(angleRad);
    float sinus = sin(angleRad);

    //  |  cos(A)  -sin(A) 0  0 |
    //M=|  sin(A)   cos(A) 0  0 |
    //  |  0        0      1  0 |
    //  |  0        0      0  1 |
    m[0]=cosine;	m[4]=-sinus;	m[8]=0;  m[12]=0;
    m[1]=sinus;		m[5]=cosine;	m[9]=0;  m[13]=0;
    m[2]=0;         m[6]=0;         m[10]=1; m[14]=0;
    m[3]=0;         m[7]=0;         m[11]=0; m[15]=1;
    return m;
}

Matrix4x4 Matrix4x4::Scale(const float x, const float y, const float z)
{
    Matrix4x4 m;
    m[0]=x;
    m[5]=y;
    m[10]=z;
    m[15]=1;
    return m;
}

Matrix4x4 Matrix4x4::Scale(Vector3 &v)
{
    Matrix4x4 m;
    m[0]=v.x;
    m[5]=v.y;
    m[10]=v.z;
    m[15]=1;
    return m;
}

float & Matrix4x4::operator [] (unsigned int n)
{
    if(n > 16) n = 16;
    return elements[n];
}

float Matrix4x4::operator [] (unsigned int n) const
{
    if(n > 16) n = 16;
    return elements[n];
}

Matrix4x4 Matrix4x4::operator * (const float & v)
{
    for (int i = 0; i < 16; i++)
    {
        elements[i] *= v;
    }
    return *this;
}

Matrix4x4 Matrix4x4::operator *= (const float & v)
{
    for (int i = 0; i < 16; i++)
    {
        elements[i] *= v;
    }
    return *this;
}

Matrix4x4 & Matrix4x4::operator = (const Matrix4x4 b)
{
    if(this != & b)
    {
        for(size_t i = 0; i < 16; ++i)
        {
            elements[i] = b.elements[i];
        }
    }
    return *this;
}

Vector4 Matrix4x4::homogenTransform(const Vector4 & v)
{
    Vector4 result = transform(v);
    result.normalize();
    return result;
}

Vector3 Matrix4x4::homogenTransform(const Vector3 & v)
{
    Vector4 tmp = transform(Vector4(v.x, v.y, v.z, 1));
    tmp.normalize();
    Vector3 result(tmp.x, tmp.y, tmp.z);
    return result;
}

Vector3 Matrix4x4::transform(const Vector3 & v)
{
    float x, y, z;
    x=elements[0]*v.x+elements[4]*v.y+elements[8 ]*v.z;
    y=elements[1]*v.x+elements[5]*v.y+elements[9 ]*v.z;
    z=elements[2]*v.x+elements[6]*v.y+elements[10]*v.z;
    return Vector3(x, y, z);
}

Vector4 Matrix4x4::transform(const Vector4 & v)
{
    float x, y, z, w;
    x=elements[0]*v.x+elements[4]*v.y+elements[8 ]*v.z+elements[12]*v.w;
    y=elements[1]*v.x+elements[5]*v.y+elements[9 ]*v.z+elements[13]*v.w;
    z=elements[2]*v.x+elements[6]*v.y+elements[10]*v.z+elements[14]*v.w;
    w=elements[3]*v.x+elements[7]*v.y+elements[11]*v.z+elements[15]*v.w;

    return Vector4(x, y, z, w);
}

float Matrix4x4::getDeterminant()
{
    return
            elements[12]*elements[9]*elements[6]*elements[3]-
            elements[8]*elements[13]*elements[6]*elements[3]-
            elements[12]*elements[5]*elements[10]*elements[3]+
            elements[4]*elements[13]*elements[10]*elements[3]+
            elements[8]*elements[5]*elements[14]*elements[3]-
            elements[4]*elements[9]*elements[14]*elements[3]-
            elements[12]*elements[9]*elements[2]*elements[7]+
            elements[8]*elements[13]*elements[2]*elements[7]+
            elements[12]*elements[1]*elements[10]*elements[7]-
            elements[0]*elements[13]*elements[10]*elements[7]-
            elements[8]*elements[1]*elements[14]*elements[7]+
            elements[0]*elements[9]*elements[14]*elements[7]+
            elements[12]*elements[5]*elements[2]*elements[11]-
            elements[4]*elements[13]*elements[2]*elements[11]-
            elements[12]*elements[1]*elements[6]*elements[11]+
            elements[0]*elements[13]*elements[6]*elements[11]+
            elements[4]*elements[1]*elements[14]*elements[11]-
            elements[0]*elements[5]*elements[14]*elements[11]-
            elements[8]*elements[5]*elements[2]*elements[15]+
            elements[4]*elements[9]*elements[2]*elements[15]+
            elements[8]*elements[1]*elements[6]*elements[15]-
            elements[0]*elements[9]*elements[6]*elements[15]-
            elements[4]*elements[1]*elements[10]*elements[15]+
            elements[0]*elements[5]*elements[10]*elements[15];
}

void Matrix4x4::invert()
{
    float x = getDeterminant();
    std::vector<float> i(16, 0.0);
    i[0]= (-elements[13]*elements[10]*elements[7] +elements[9]*elements[14]*elements[7] +elements[13]*elements[6]*elements[11]
            -elements[5]*elements[14]*elements[11] -elements[9]*elements[6]*elements[15] +elements[5]*elements[10]*elements[15])/x;
    i[4]= ( elements[12]*elements[10]*elements[7] -elements[8]*elements[14]*elements[7] -elements[12]*elements[6]*elements[11]
            +elements[4]*elements[14]*elements[11] +elements[8]*elements[6]*elements[15] -elements[4]*elements[10]*elements[15])/x;
    i[8]= (-elements[12]*elements[9]* elements[7] +elements[8]*elements[13]*elements[7] +elements[12]*elements[5]*elements[11]
            -elements[4]*elements[13]*elements[11] -elements[8]*elements[5]*elements[15] +elements[4]*elements[9]* elements[15])/x;
    i[12]=( elements[12]*elements[9]* elements[6] -elements[8]*elements[13]*elements[6] -elements[12]*elements[5]*elements[10]
            +elements[4]*elements[13]*elements[10] +elements[8]*elements[5]*elements[14] -elements[4]*elements[9]* elements[14])/x;
    i[1]= ( elements[13]*elements[10]*elements[3] -elements[9]*elements[14]*elements[3] -elements[13]*elements[2]*elements[11]
            +elements[1]*elements[14]*elements[11] +elements[9]*elements[2]*elements[15] -elements[1]*elements[10]*elements[15])/x;
    i[5]= (-elements[12]*elements[10]*elements[3] +elements[8]*elements[14]*elements[3] +elements[12]*elements[2]*elements[11]
            -elements[0]*elements[14]*elements[11] -elements[8]*elements[2]*elements[15] +elements[0]*elements[10]*elements[15])/x;
    i[9]= ( elements[12]*elements[9]* elements[3] -elements[8]*elements[13]*elements[3] -elements[12]*elements[1]*elements[11]
            +elements[0]*elements[13]*elements[11] +elements[8]*elements[1]*elements[15] -elements[0]*elements[9]* elements[15])/x;
    i[13]=(-elements[12]*elements[9]* elements[2] +elements[8]*elements[13]*elements[2] +elements[12]*elements[1]*elements[10]
            -elements[0]*elements[13]*elements[10] -elements[8]*elements[1]*elements[14] +elements[0]*elements[9]* elements[14])/x;
    i[2]= (-elements[13]*elements[6]* elements[3] +elements[5]*elements[14]*elements[3] +elements[13]*elements[2]*elements[7]
            -elements[1]*elements[14]*elements[7]  -elements[5]*elements[2]*elements[15] +elements[1]*elements[6]* elements[15])/x;
    i[6]= ( elements[12]*elements[6]* elements[3] -elements[4]*elements[14]*elements[3] -elements[12]*elements[2]*elements[7]
            +elements[0]*elements[14]*elements[7]  +elements[4]*elements[2]*elements[15] -elements[0]*elements[6]* elements[15])/x;
    i[10]=(-elements[12]*elements[5]* elements[3] +elements[4]*elements[13]*elements[3] +elements[12]*elements[1]*elements[7]
            -elements[0]*elements[13]*elements[7]  -elements[4]*elements[1]*elements[15] +elements[0]*elements[5]* elements[15])/x;
    i[14]=( elements[12]*elements[5]* elements[2] -elements[4]*elements[13]*elements[2] -elements[12]*elements[1]*elements[6]
            +elements[0]*elements[13]*elements[6]  +elements[4]*elements[1]*elements[14] -elements[0]*elements[5]* elements[14])/x;
    i[3]= ( elements[9]* elements[6]* elements[3] -elements[5]*elements[10]*elements[3] -elements[9]* elements[2]*elements[7]
            +elements[1]*elements[10]*elements[7]  +elements[5]*elements[2]*elements[11] -elements[1]*elements[6]* elements[11])/x;
    i[7]= (-elements[8]* elements[6]* elements[3] +elements[4]*elements[10]*elements[3] +elements[8]* elements[2]*elements[7]
            -elements[0]*elements[10]*elements[7]  -elements[4]*elements[2]*elements[11] +elements[0]*elements[6]* elements[11])/x;
    i[11]=( elements[8]* elements[5]* elements[3] -elements[4]*elements[9]* elements[3] -elements[8]* elements[1]*elements[7]
            +elements[0]*elements[9]* elements[7]  +elements[4]*elements[1]*elements[11] -elements[0]*elements[5]* elements[11])/x;
    i[15]=(-elements[8]* elements[5]* elements[2] +elements[4]*elements[9]* elements[2] +elements[8]* elements[1]*elements[6]
            -elements[0]*elements[9]* elements[6]  -elements[4]*elements[1]*elements[10] +elements[0]*elements[5]* elements[10])/x;

    for(size_t j = 0; j < 16; ++j)
    {
        elements[j] = i[j];
    }
}

void Matrix4x4::transpose()
{
    std::vector<float> t(16);
    t[0]=elements[0];  t[4]=elements[1];  t[8]=elements[2];   t[12]=elements[3];
    t[1]=elements[4];  t[5]=elements[5];  t[9]=elements[6];   t[13]=elements[7];
    t[2]=elements[8];  t[6]=elements[9];  t[10]=elements[10]; t[14]=elements[11];
    t[3]=elements[12]; t[7]=elements[13]; t[11]=elements[14]; t[15]=elements[15];
    for(size_t j = 0; j < 16; ++j)
    {
        elements[j] = t[j];
    }
}

Matrix4x4 Matrix4x4::getTranspose()
{
    Matrix4x4 tmp = *this;
    tmp.transpose();
    return tmp;
}

Matrix4x4 Matrix4x4::getInverse()
{
    Matrix4x4 i(*this);
    i.invert();
    return i;
}

Matrix3x3 Matrix4x4::getMatrix3()
{
    Matrix3x3 result;

    result[0] = elements[0];
    result[1] = elements[1];
    result[2] = elements[2];

    result[3] = elements[4];
    result[4] = elements[5];
    result[5] = elements[6];

    result[6] = elements[8];
    result[7] = elements[9];
    result[8] = elements[10];

    return result;
}

std::string Matrix4x4::toString() const
{
    std::stringstream tmp;
    for (int i = 0; i < 4; ++i)
    {
        tmp << "(" << elements[i] << ", " << elements[i+4] << ", " << elements[i+8]<< ", " << elements[i+12] << ")" << std::endl;
    }
    return tmp.str();
}
