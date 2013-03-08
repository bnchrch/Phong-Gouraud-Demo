#include "s_stream.h"
#include <sstream>
#include <stdexcept>

Stream::Stream(std::string m_Path, std::string m_Mode) : mPath(m_Path), mMode(m_Mode), mFile(NULL)
{
    this->open();
}

Stream::Stream(const Stream & m_Other) : mPath(m_Other.mPath), mMode(m_Other.mMode), mFile(NULL)
{
    this->open();
}

Stream::~Stream()
{
    this->close();
}

bool Stream::seek(size_t m_Position)
{
    return (fseek(mFile, m_Position, SEEK_SET) == 0);
}

bool Stream::reset()
{
    return this->seek(0);
}

bool Stream::eof()
{
    return feof(mFile);
}

bool Stream::flush()
{
    return (fflush(mFile) == 0);
}

std::string Stream::readLine()
{
    std::stringstream result;
    char current;
    while (((current = fgetc(mFile)) != '\n') && !eof())
    {
        result << current;
    }

    return result.str();
}

bool Stream::writeLine(std::string m_Line)
{
    bool result = true;

    for(size_t i = 0; i < m_Line.length(); ++i)
    {
        result = m_Line[i] == fputc(m_Line[i], mFile);
        if(!result)
        {
            break;
        }
    }
    result = '\n' == fputc('\n', mFile);

    return result;
}

bool Stream::writeString(std::string m_String)
{
    bool result = true;

    for(size_t i = 0; i < m_String.length(); ++i)
    {
        result = m_String[i] == fputc(m_String[i], mFile);
        if(!result)
        {
            break;
        }
    }

    return result;
}

Stream & Stream::operator=(const Stream & m_Other)
{
    if(this != & m_Other)
    {
        close();
        mPath = m_Other.mPath;
        mMode = m_Other.mMode;
        this->open();
    }
    return *this;
}

const std::string Stream::getPath() const
{
    return mPath;
}

const std::string Stream::getFileName() const
{
    return mPath.substr(mPath.find_last_of("/") + 1, mPath.length() - mPath.find_last_of("/"));
}

FILE * Stream::getPointer()
{
    return mFile;
}

void Stream::open()
{
    mFile = fopen(mPath.c_str(), mMode.c_str());
    if(mFile == NULL)
    {
        throw std::exception();
    }
}

void Stream::close()
{
    fclose(mFile);
    mFile = NULL;
}
