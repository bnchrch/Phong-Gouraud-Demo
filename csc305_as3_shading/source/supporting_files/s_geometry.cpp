#include "geometry.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <iostream>
#include <algorithm>
#include "s_stream.h"
#include "s_tokenizer.h"
#include "s_openglerror.h"

Geometry::~Geometry()
{
    mVertices.clear();
    mNormals.clear();
    mTexCoords.clear();
    mColors.clear();

    glDeleteVertexArrays(1, & mVertexArray);

    glDeleteBuffers(1, & mColorBuffer);
    glDeleteBuffers(1, & mNormalBuffer);
    glDeleteBuffers(1, & mTexCoordBuffer);
    glDeleteBuffers(1, & mVertexBuffer);

}

void Geometry::draw(Matrix4x4 & m_ProjectionMatrix,
                    Matrix4x4 & m_ViewMatrix,
                    bool m_UsePostMultipy,
                    Vector3 & m_LightPos,
                    Vector4 & m_LightCol,
                    uint32_t m_TextureHandle,
                    uint32_t m_BumpTextureHandle,
                    Program * m_Program/* = NULL*/)
{
    // in case no shader is provided we use the default one created in the constructor
    if(!m_Program)
    {
        m_Program = mProgram;
    }

    m_Program->activate();
	
	// querying the uniform parameters of the shader
    Parameter * projectionParam = m_Program->getParameter("projectionMatrix");
    Parameter * viewParam = m_Program->getParameter("viewMatrix");
    Parameter * modelParam = m_Program->getParameter("modelMatrix");
    Parameter * postMultParam = m_Program->getParameter("usePostMultiply");
    Parameter * normalMParam = m_Program->getParameter("normalMatrix");
    Parameter * lightPosParam = m_Program->getParameter("lightPos");
    Parameter * lightColParam = m_Program->getParameter("lightCol");
    Parameter * colorMapParam = m_Program->getParameter("colormap");
    Parameter * bumpMapParam = m_Program->getParameter("bumpmap");
	
    // setting the uniform parameters
    if(projectionParam)
    {
        glUniformMatrix4fv(projectionParam->getHandle(),
                           1,
                           false,
                           & m_ProjectionMatrix.elements[0]);
    }
	
    if(viewParam)
    {
        glUniformMatrix4fv(viewParam->getHandle(),
                           1,
                           false,
                           & m_ViewMatrix.elements[0]);
    }
	
    if(modelParam)
    {
        glUniformMatrix4fv(modelParam->getHandle(),
                           1,
                           false,
                           & mModelMatrix.elements[0]);
    }
	
    if(postMultParam)
    {
        glUniform1i(postMultParam->getHandle(),
                    (int)m_UsePostMultipy);
    }

    if(normalMParam)
    {
        glUniformMatrix3fv(normalMParam->getHandle(),
                           1,
                           false,
                           & mNormalMatrix.elements[0]);
    }

    if(lightPosParam)
    {
        glUniform3fv(lightPosParam->getHandle(),
                     1,
                     & m_LightPos.elements[0]);
    }

    if(lightColParam)
    {
        glUniform4fv(lightColParam->getHandle(),
                     1,
                     & m_LightCol.elements[0]);
    }

    int activeTexture = 0;

    if(colorMapParam)
    {
        glActiveTexture(GL_TEXTURE0 + activeTexture);
        glBindTexture(GL_TEXTURE_2D, m_TextureHandle);

        glUniform1i(colorMapParam->getHandle(),
                    activeTexture);

        activeTexture++;
    }
    if(bumpMapParam)
    {
        glActiveTexture(GL_TEXTURE0 + activeTexture);
        glBindTexture(GL_TEXTURE_2D, m_BumpTextureHandle);

        glUniform1i(bumpMapParam->getHandle(),
                    activeTexture);

        activeTexture++;
    }
	// setting the uniform parameters end

    Parameter * colorParam = m_Program->getAttribute("color");
    Parameter * normalParam = m_Program->getAttribute("normal");
    Parameter * texCoordParam = m_Program->getAttribute("texcoord0");
    Parameter * vertexParam = m_Program->getAttribute("vertex");


    glBindVertexArray(mVertexArray);

    if(colorParam)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, 4 * mColors.size() * sizeof(GLfloat), & mColors[0], GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(colorParam->getHandle());
        glVertexAttribPointer(colorParam->getHandle(),
                              4,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              0);
    }

    if(texCoordParam)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);
        glBufferData(GL_ARRAY_BUFFER, 3 * mTexCoords.size() * sizeof(GLfloat), & mTexCoords[0], GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(texCoordParam->getHandle());
        glVertexAttribPointer(texCoordParam->getHandle(),
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              0);
    }

    if(normalParam)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
        glBufferData(GL_ARRAY_BUFFER, 3 * mNormals.size() * sizeof(GLfloat), & mNormals[0], GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(normalParam->getHandle());
        glVertexAttribPointer(normalParam->getHandle(),
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              0);
    }

    if(vertexParam)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 3 * mVertices.size() * sizeof(GLfloat), & mVertices[0], GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(vertexParam->getHandle());
        glVertexAttribPointer(vertexParam->getHandle(),
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              0);
    }

    glDrawArrays((uint32_t)mPrimitiveType, 0, mVertices.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(vertexParam)
    {
        glDisableVertexAttribArray(vertexParam->getHandle());
    }

    if(normalParam)
    {
        glDisableVertexAttribArray(normalParam->getHandle());
    }

    if(texCoordParam)
    {
        glDisableVertexAttribArray(texCoordParam->getHandle());
    }

    if(colorParam)
    {
        glDisableVertexAttribArray(colorParam->getHandle());
    }

    glBindVertexArray(0);

    if(colorMapParam)
    {
        --activeTexture;
        glActiveTexture(GL_TEXTURE0 + activeTexture);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if(bumpMapParam)
    {
        --activeTexture;
        glActiveTexture(GL_TEXTURE0 + activeTexture);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    m_Program->deactivate();
}

std::string Geometry::getFileName() const
{
    return mFileName;
}

std::string Geometry::getFilePath() const
{
    return mFilePath;
}

void Geometry::parseFile()
{
    // open our given file path in read mode ("r").
    // and text mode ("t")
    Stream input(mFilePath, "rt");

    mFileName = input.getFileName();
	
	std::vector<Vector3>	tempVertices;
	std::vector<Vector3>	tempNormals;
	std::vector<Vector3>	tempTexCoords;
	std::vector<Vector4>	tempColors;

    // we read the file line by line until we are at the end
    while(!input.eof())
    {
        std::string curLine = input.readLine();
        // we have an empty line or a comment (starts with #)
        if(curLine.compare("") == 0 || curLine[0] == '#')
        {
            continue;
        }
        Tokenizer tokenizer(curLine);
        tokenizer.tokenize();

        if(tokenizer.getNumTokens() == 0)
        {
            continue;
        }

        std::vector<std::string> tokens = tokenizer.getTokens();

        // vertices
        if(tokens[0].compare("v") == 0)
        {
            Vector3 curVertex;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curVertex.elements[i - 1] = atof(tokens[i].c_str());
			}

            tempVertices.push_back(curVertex);
        }
        // normals
        else if(tokens[0].compare("vn") == 0)
        {
            Vector3 curNormal;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curNormal.elements[i - 1] = atof(tokens[i].c_str());
			}

            tempNormals.push_back(curNormal);
        }
        // texture coordinates
        else if(tokens[0].compare("vt") == 0)
        {
            Vector3 curTexCoord;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curTexCoord.elements[i - 1] = atof(tokens[i].c_str());
			}
            tempTexCoords.push_back(curTexCoord);
        }
        // colors. this is an extension needed only for the assignments. the standard
        // obj file format does not have vertex colors
        else if(tokens[0].compare("vc") == 0)
        {
			Vector4 curColor;
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				curColor.elements[i - 1] = atof(tokens[i].c_str());
			}
            tempColors.push_back(curColor);
        }
        // faces. in case of quads we convert to two triangles
        else if(tokens[0].compare("f") == 0)
        {
			if(tokens.size() == 4)
			{
				mPrimitiveType = TRIANGLES;
			}
			else if(tokens.size() == 5)
			{
				mPrimitiveType = QUADS;
			}
			// no supported primitive type
			else
			{
				continue;
			}
			
			typedef enum
			{
				vertex = 0,
				texcoord = 1,
				normal = 2,
				color = 3
			}
			facePointParam;
			
			// we loop over every vertex in the face
			for(size_t i = 1; i < tokens.size(); ++i)
			{
				facePointParam curParam = vertex;
				size_t numParams = std::count(tokens[i].begin(), tokens[i].end(), '/');
				size_t lastDelimiterIndex = -1;
				
				std::string remainderString = tokens[i];
				
				// we loop over the v/t/n/c construct part by part by reading until the first
				// occurence of /, converting the string to the index of the component, and then removing this
				// part of the string
				for(size_t j = 0; j < (numParams + 1); ++j)
				{
					size_t firstDelimiter = remainderString.find_first_of("/");
					
					std::string curString = remainderString.substr(lastDelimiterIndex + 1, firstDelimiter);
					
					if(curString.compare("") != 0)
					{					
                        size_t index = atoi(curString.c_str()) - 1;
						switch (curParam) {
							case vertex:
								mVertices.push_back(tempVertices[index]);
								break;
							case texcoord:
								mTexCoords.push_back(tempTexCoords[index]);
								break;
							case normal:
								mNormals.push_back(tempNormals[index]);
								break;
							case color:
								mColors.push_back(tempColors[index]);
								break;
								
							default:
								break;
						}
					}
					
					remainderString = remainderString.substr(firstDelimiter + 1,
															 remainderString.size() - firstDelimiter - 1);
					
                    curParam = (facePointParam)(((uint32_t)curParam) + 1);
					
				}

				// in case we don't get colors, have black as a default color, so it
				// does not crash in glDrawArrays
                if(numParams < 3)
				{
					mColors.push_back(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
				}
			}
        }
        // everything else, we are not interested
        else
        {
            // not handeled
        }
    }
	
	convertQuadsToTriangles();
}

void Geometry::convertQuadsToTriangles()
{
	if(mPrimitiveType == QUADS)
    {
        /**
         *	we need to change quads to triangles, since OpenGL3.2 Core
         *	does not support quads any more
         */
        std::vector<Vector3>	tempVertices;
        std::vector<Vector3>	tempNormals;
        std::vector<Vector3>	tempTexCoords;
        std::vector<Vector4>	tempColors;
		
        for(size_t i = 0; i < mVertices.size(); i += 4)
        {
            /**
             *	Triangle 1 from Quad.
             *	index 0-1-3
             */
            size_t index = i;
			
            tempVertices.push_back(mVertices[index]);
			if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
			if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 1;
			
            tempVertices.push_back(mVertices[index]);
			if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 3;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            /**
             *	triangle 2 from quad
             *	index 1-2-3
             */
			
            index = i + 1;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 2;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
			
            index = i + 3;
			
            tempVertices.push_back(mVertices[index]);
            if(index < mNormals.size())
				tempNormals.push_back(mNormals[index]);
            if(index < mTexCoords.size())
				tempTexCoords.push_back(mTexCoords[index]);
            if(index < mColors.size())
				tempColors.push_back(mColors[index]);
        }
		
        mVertices.swap(tempVertices);
        mNormals.swap(tempNormals);
        mTexCoords.swap(tempTexCoords);
        mColors.swap(tempColors);
		
        mPrimitiveType = TRIANGLES;
    }
    else if(mPrimitiveType == QUAD_STRIP)
    {
        /**
         *	luckily quad strips and triangle strips seem to require the same
         *	data
         */
        mPrimitiveType = TRIANGLE_STRIP;
    }
}

void Geometry::initOpenGLBuffers()
{
	glGenVertexArrays(1, & mVertexArray);
    glBindVertexArray(mVertexArray);
	
    glGenBuffers(1, & mColorBuffer);
    glGenBuffers(1, & mNormalBuffer);
    glGenBuffers(1, & mTexCoordBuffer);
    glGenBuffers(1, & mVertexBuffer);
	
    glBindVertexArray(0);

}

bool Geometry::initDefaultShader()
{

    const std::string vertexShader =
            "#version 150\n"
            "uniform mat4 projectionMatrix;\n"
            "uniform mat4 viewMatrix;\n"
            "uniform mat4 modelMatrix;\n"
            "uniform int usePostMultiply;\n"
            "in vec3 vertex;\n"
            "in vec4 color;\n"
            "out vec4 vColor;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);\n"
            "   vColor = color;\n"
            "}";

    const std::string fragmentShader = "#version 150\n"
            "in vec4 vColor;\n"
            "out vec4 fColor;\n"
            "void main()\n"
            "{\n"
            "   fColor = vColor;\n"
            "}";
	
	
    mProgram = new Program();
	
    Shader * vShader = new Shader(vertexShader, Shader::VERTEX);
    vShader->load();
    Shader * fShader = new Shader(fragmentShader, Shader::FRAGMENT);
    fShader->load();
	
    mProgram->push_back(vShader);
    mProgram->push_back(fShader);
	
    return mProgram->link();
}
