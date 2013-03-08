#ifndef STREAM_H
#define STREAM_H

#include <string>

/**
 *	@class	Stream
 *	@brief	class wrapping FILE * to provide a more std::istream like behaviour
 */
class Stream
{
public:

    /**
     *	constructor having the file path as the argument
     *	@param	m_Path	path to the input file
     *	@param	m_Mode the mode to open, as defined in fopen
     */
    Stream(std::string m_Path, std::string m_Mode);

    /**
     *	copy constructor
     *	@param	m_Other the other object
     */
    Stream(const Stream & m_Other);

    /**
     *	default destructor
     */
    virtual ~Stream();

    /**
     *	method to read data from the file into the given data
     *	@param	m_Data the pointer where we want to read into
     *	@param	m_NumberOfElements the number of elements that we want to read
     *	@return	returns if read successful
     */
    template <class T>
    bool read(T * m_Data, size_t m_NumberOfElements = 1)
    {
        size_t result = fread(m_Data, sizeof(T), m_NumberOfElements, mFile);
        return (result == m_NumberOfElements);
    }

    /**
     *	method to write data into the file from the given data
     *	@param	m_Data the pointer what we want to write
      *	@param	m_NumberOfElements the number of elements that we want to read
     *	@return	returns if write successful
     */
    template <class T>
    bool write(T * m_Data, size_t m_NumberOfElements = 1)
    {
        size_t result = fwrite(m_Data, sizeof(T), m_NumberOfElements, mFile);
        return (result == m_NumberOfElements);
    }

    /**
     *	seeks to a given position in the file
     *	always assumed from beginning of file
     *	@param	m_Position the new position in the file
     *	@return	returns if seek was successful
     */
    bool seek(size_t m_Position);

    /**
     *	resets the file pointer to the origin
     *	@return	returns if reset was successful
     */
    bool reset();

    /**
     *	checks for end of file
     *	@return	returns true if end of file is reached
     */
    bool eof();

    /**
     *	flushes the file
     *	@return	returns true if flush was sucessful
     */
    bool flush();

    /**
     *	reads one line from the stream
     *	@return	returns a string containing the line
     */
    std::string readLine();

    /**
     *	writes a line to the stream
     *	@param	m_Line the line to write
     *	@return	returns if writing was successful
     */
    bool writeLine(std::string m_Line);

    /**
     *	writes a string to the stream
     *	@param	m_String the string to write
     *	@return	returns if writing was successful
     */
    bool writeString(std::string m_String);

    /**
     *	assignment operator
     *	@param	m_Other the other Stream object
     *	@return	returns reference to self
     */
    Stream & operator=(const Stream & m_Other);

    /**
     *	returns the path where the stream points to
     *	@return	returns the path
     */
    const std::string getPath() const;

    /**
     *	returns the filename without the rest of the path where the stream points to
     *	@return	returns the filename
     */
    const std::string getFileName() const;

    /**
     *	returns the c style FILE pointer
     *	for situations where it is needed (etc. libpng)
     *	@return	returns the pointer
     */
    FILE * getPointer();

private:

    /**
     *	method to open file
     */
    void open();

    /**
     *	method to close file
     */
    void close();

    std::string		mPath;				/**< path to the file. */
    std::string		mMode;				/**< file open mode. */
    FILE			* mFile;			/**< FILE pointer that is used for reading. */
};


#endif // STREAM_H
