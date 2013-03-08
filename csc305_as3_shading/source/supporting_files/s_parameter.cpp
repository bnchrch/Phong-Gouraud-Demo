#include "s_parameter.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif


Parameter::Parameter() : mHandle(0), mName()
{

}

Parameter::Parameter(uint32_t m_Handle, std::string m_Name) : mHandle(m_Handle), mName(m_Name)
{
}

Parameter::~Parameter()
{
}
