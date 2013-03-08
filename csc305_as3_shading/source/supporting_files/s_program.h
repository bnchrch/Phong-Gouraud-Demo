#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <map>
#include "supporting_files/s_shader.h"
#include "supporting_files/s_parameter.h"

/**
 *	@class	Program
 *	@brief	class representing an abstract gpu program, being a collection of shaders
 */
class Program
{
public:

    /**
     *	default constructor
     */
    Program();

    /**
     *	constructor with given shaders
     */
    Program(std::vector<Shader *> m_Shaders);

    /**
     *	default destructor
     */
    virtual ~Program();

    /**
     *	adds a shader to the program
     *	@param	m_Shader the new shader
     */
    void push_back(Shader * m_Shader)
    {
        mShaders.push_back(m_Shader);
    }

    /**
     *	links all programs together
     *	@return	returns if success
     */
    bool link();

    /**
     *	activates the program
     */
    void activate();

    /**
     *	deactivates the program
     */
    void deactivate();

    /**
     *	gets the iterator pointing to the start of the parameters
     *	@return	returns the iterator
     */
    std::map<std::string, Parameter *>::iterator getParameterBegin()
    {
        return mParameters.begin();
    }

    /**
     *	gets the iterator pointing to the end of the parameters
     *	@return	returns the iterator
     */
    std::map<std::string, Parameter *>::iterator getParameterEnd()
    {
        return mParameters.end();
    }

    /**
     *	gets the parameter with the name
     *	@param	m_Name the name of the parameter
     *	@return	returns the pointer to the parameter
     */
    Parameter * getParameter(std::string m_Name)
    {
        if(mParameters.find(m_Name) != mParameters.end())
        {
            return mParameters[m_Name];
        }
        return NULL;
    }

    /**
     *	gets the iterator pointing to the start of the attributes
     *	@return	returns the iterator
     */
    std::map<std::string, Parameter *>::iterator getAttributeBegin()
    {
        return mAttributes.begin();
    }

    /**
     *	gets the iterator pointing to the end of the attributes
     *	@return	returns the iterator
     */
    std::map<std::string, Parameter *>::iterator getAttributesEnd()
    {
        return mAttributes.end();
    }

    /**
     *	gets the attribute with the name
     *	@param	m_Name the name of the parameter
     *	@return	returns the pointer to the parameter
     */
    Parameter * getAttribute(std::string m_Name)
    {
        if(mAttributes.find(m_Name) != mAttributes.end())
        {
            return mAttributes[m_Name];
        }
        return NULL;
    }

protected:

    /**
     *	destroys the program object
     */
    void destroy();

    uint32_t								mHandle;			/**< the program handle. */

    std::vector<Shader *>				mShaders;			/**< the shaders used in the program. */
    std::map<std::string, Parameter *>	mParameters;		/**< the parameters in the program. */
    std::map<std::string, Parameter *>	mAttributes;		/**< the attributes in the program. */

};
#endif // PROGRAM_H
