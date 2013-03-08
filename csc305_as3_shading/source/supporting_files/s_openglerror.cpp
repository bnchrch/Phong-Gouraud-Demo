#include "s_openglerror.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif

std::string getErrorString(uint32_t m_ErrorCode)
{
    switch (m_ErrorCode)
    {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
        break;
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
        break;
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
        break;
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
        break;
    default:
        break;
    }
    return "";
}
