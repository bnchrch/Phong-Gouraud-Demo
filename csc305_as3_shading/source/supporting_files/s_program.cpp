#include "s_program.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <iostream>
#include "s_openglerror.h"

Program::Program() : mHandle(0), mShaders(), mParameters(), mAttributes()
{

}

Program::Program(std::vector<Shader *> m_Shaders)  : mHandle(0), mShaders(m_Shaders), mParameters(), mAttributes()
{

}

Program::~Program()
{
    destroy();

    std::map<std::string, Parameter *>::iterator i = mParameters.begin();
    while(i != mParameters.end())
    {
        delete (*i).second;
        i++;
    }
    mParameters.clear();

    i = mAttributes.begin();
    while(i != mAttributes.end())
    {
        delete (*i).second;
        i++;
    }
    mAttributes.clear();

    mShaders.clear();
}

bool Program::link()
{
    if(mHandle > 0)
        return true;

    mHandle = glCreateProgram();
    GLenum glError = glGetError();

    if (glError != GL_NO_ERROR)
    {
        std::cerr << "Error creating program" << getErrorString(glError).c_str() << std::endl;
    }

    for(size_t i = 0; i < mShaders.size(); ++i)
    {
        glAttachShader(mHandle, dynamic_cast<Shader *>(mShaders[i])->getHandle());
        glError = glGetError();

        if (glError != GL_NO_ERROR)
        {
            std::cerr << "Error attaching shader " << getErrorString(glError).c_str() << std::endl;
        }

        dynamic_cast<Shader *>(mShaders[i])->attach();
    }

    glLinkProgram(mHandle);
    glError = glGetError();

    if (glError != GL_NO_ERROR)
    {
        std::cerr << "Error linking program" << getErrorString(glError).c_str() << std::endl;
    }

    int result = 1;
    glGetProgramiv(mHandle, GL_LINK_STATUS, & result);

    if (!result)
    {
        int length = 0;

        glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, & length);

        char * info = new char[length];
        int written = 0;

        glGetProgramInfoLog(mHandle, length, &written, info);
        std::string strInfo(info);
        delete[] info;

        std::cerr << "Error linking program" << std::endl;
        std::cerr << strInfo.c_str() << std::endl;
    }

    int numUniforms = 0;
    const int numChars = 100;
    char tempName[numChars];

    glGetProgramiv(mHandle, GL_ACTIVE_UNIFORMS, & numUniforms);

    for(int i = 0; i < numUniforms; ++i)
    {
        int length = 0;
        int paramsize = 0;
        GLenum paramtype = 0;
        glGetActiveUniform(mHandle, i, numChars, & length, & paramsize, & paramtype, tempName);

        std::string paramName(tempName);
        paramName = paramName.substr(0, length);

        uint32_t mParamHandle = glGetUniformLocation(mHandle, paramName.c_str());

        mParameters[paramName] = new Parameter(mParamHandle, paramName);

        std::cout << "Found Uniform " << paramName.c_str() << std::endl;
    }

    int numAttributes = 0;
    glGetProgramiv(mHandle, GL_ACTIVE_ATTRIBUTES, & numAttributes);

    for(int i = 0; i < numAttributes; ++i)
    {
        int length = 0;
        int paramsize = 0;
        GLenum paramtype = 0;
        glGetActiveAttrib(mHandle, i, numChars, & length, & paramsize, & paramtype, tempName);

        std::string paramName(tempName);
        paramName = paramName.substr(0, length);

        uint32_t mAttribHandle = glGetAttribLocation(mHandle, paramName.c_str());

        mAttributes[paramName] = new Parameter(mAttribHandle, paramName);

        std::cout << "Found Attribute " << paramName.c_str() << std::endl;
    }

    return (bool)result;
}

void Program::activate()
{
    glUseProgram(mHandle);
}

void Program::deactivate()
{
    glUseProgram(0);
}

void Program::destroy()
{
    GLuint glError;

    for(size_t i = 0; i < mShaders.size(); ++i)
    {
        glDetachShader(mHandle, dynamic_cast<Shader *>(mShaders[i])->getHandle());
        glError = glGetError();

        if (glError != GL_NO_ERROR)
        {
            std::cerr << "Error detaching shader " << getErrorString(glError).c_str() << std::endl;
        }

        dynamic_cast<Shader *>(mShaders[i])->detach();
    }

    mShaders.clear();

    glDeleteProgram(mHandle);
    glError = glGetError();

    if (glError != GL_NO_ERROR)
    {
        std::cerr << "Error deleting program" << getErrorString(glError).c_str() << std::endl;
    }
}
