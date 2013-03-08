#ifndef PARAMETER_H
#define PARAMETER_H

#include "vector.h"
#include "matrix.h"
#include <stdint.h>
#include <string>
#include <vector>

/**
 *	@class	Parameter
 *	@brief	class representing a gpu shader parameter
 */
class Parameter
{
public:

    /**
     *	default constructor
     */
    Parameter();

    /**
     *	constructor with given values
     *	@param	m_Handle the handle in the shader file
     *	@param	m_Name	the name of the parameter in the shader file
     */
    Parameter(uint32_t m_Handle, std::string m_Name);

    /**
     *	default destructor
     */
    virtual ~Parameter();

    /**
     *	method to query the parameter handle
     *	@return	returns the member
     */
    inline uint32_t getHandle() const
    {
        return mHandle;
    }


protected:

    uint32_t		mHandle;		/**< the api side handle to the parameter. */
    std::string     mName;			/**< the name of the parameter in the shader file. */
};

#endif // PARAMETER_H
