#include "s_shader.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <iostream>
#include "s_openglerror.h"

Shader::Shader(std::string m_ShaderContent, type m_Type) : mHandle(0), mShaderContent(m_ShaderContent), mType(m_Type)
{

}

Shader::~Shader()
{
    if((int)mMapAttachment.size() > 0)
        if (mMapAttachment[mHandle] == 0)
        {
            glDeleteShader(mHandle);
            GLenum glError = glGetError();

            if (glError != GL_NO_ERROR)
            {
                std::cerr << "Error deleting shader " << getErrorString(glError).c_str() << std::endl;
            }
        }
}

bool Shader::load()
{
    if(mHandle > 0)
        return true;

    mHandle = glCreateShader((uint32_t)mType);
    GLenum glError = glGetError();

    if (glError != GL_NO_ERROR)
    {
        std::cerr << "Error creating shader " << getErrorString(glError).c_str() << std::endl;
    }

    mMapAttachment[mHandle] = 0;

    const char *strings[] = { mShaderContent.c_str() };

    glShaderSource(mHandle, 1, strings, NULL);
    glError = glGetError();

    if (glError != GL_NO_ERROR)
    {
        std::cerr << "Error loading shader " << getErrorString(glError).c_str() << std::endl;
    }

    glCompileShader(mHandle);
    glError = glGetError();

    if (glError != GL_NO_ERROR)
    {
        std::cerr << "Error compiling shader " << getErrorString(glError).c_str() << std::endl;
    }

    int result = 1;
    glGetShaderiv(mHandle, GL_COMPILE_STATUS, & result);

    if (!result)
    {
        int length = 0;

        glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, & length);

        char * info = new char[length];
        int written = 0;

        glGetShaderInfoLog(mHandle, length, &written, info);
        std::string strInfo(info);
        delete[] info;

        std::cerr << "Error compiling shader " << std::endl;
        std::cerr << strInfo.c_str() << std::endl;
    }

    return (bool)result;
}

void Shader::activate()
{

}

void Shader::attach()
{
    mMapAttachment[mHandle]++;
}

void Shader::detach()
{
    if((int)mMapAttachment.size() > 0)
        mMapAttachment[mHandle]--;
}

std::map<unsigned int, unsigned int> Shader::mMapAttachment;
