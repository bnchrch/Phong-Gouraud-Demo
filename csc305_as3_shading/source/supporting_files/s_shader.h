#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <stdint.h>

/**
 *	@class	Shader
 *	@brief	abstract class for an OpenGL shader
 */
class Shader
{
public:

    /**
     *	@brief enum describing the shader types
     */
    typedef enum
    {
        VERTEX		= 0x8B31,	/**< a vertex shader. */
        GEOMETRY	= 0x8DD9,	/**< a geometry shader. */
        FRAGMENT	= 0x8B30	/**< a fragment shader. */
    } type;

    /**
     *	constructor with given parameters
     *	@param	m_File the name of the file
     *	@param	m_ShaderContent the type of the shader
     */
    Shader(std::string m_ShaderContent, type m_Type);

    /**
     *	default destructor
     */
    virtual ~Shader();

    /**
     *	loads the shader
     *	@return	returns if success
     */
    bool load();

    /**
     *	activates the shader
     */
    void activate();

    /**
     * attaches the current object
     */
    void attach();

    /**
     * detaches the current object
     */
    void detach();

    /**
     *	gets the type of the shader
     *	@return	returns the type of the shader
     */
    type getType()
    {
        return mType;
    }

    /**
     *	gets the shader handle
     *	@return	returns the handle of the shader
     */
    uint32_t getHandle()
    {
        return mHandle;
    }

protected:

    uint32_t				mHandle;			/**< the handle to the shader. */
    std::string             mShaderContent;		/**< the shader in string form. */

    type	mType;									/**< the type of the shader. */

    static std::map<uint32_t, uint32_t> mMapAttachment;		/**< static map containing the current attachments. */

};

#endif // SHADER_H
