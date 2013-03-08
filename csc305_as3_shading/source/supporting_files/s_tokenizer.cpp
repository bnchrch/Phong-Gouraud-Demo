#include "s_tokenizer.h"

Tokenizer::Tokenizer() : mBaseString(), mDelimiters(" \"',()"), mTokens()
{

}

Tokenizer::Tokenizer(std::string m_BaseString) : mBaseString(m_BaseString), mDelimiters(" \"',()"), mTokens()
{

}

Tokenizer::Tokenizer(std::string m_BaseString, std::string m_Delimiters) : mBaseString(m_BaseString), mDelimiters(m_Delimiters), mTokens()
{

}

Tokenizer::~Tokenizer()
{
    mTokens.clear();
}

bool Tokenizer::tokenize(std::string m_BaseString)
{
    mBaseString = m_BaseString;
    return tokenize();
}

bool Tokenizer::tokenize()
{
    state curState = TOKEN;
    char * curDelimiterPtr = NULL;
    char curDelimiter;
    std::string curToken;

    for(size_t i = 0; i < mBaseString.length(); ++i)
    {
        char curChar = mBaseString[i];

        switch (curState)
        {
            case TOKEN:
                if((mDelimiters.find(curChar) != std::string::npos))
                {
                    if(curDelimiterPtr)
                    {
                        if(curDelimiter == '(' && curChar == ')')
                        {

                        }
                        else if(curDelimiter != curChar)
                        {
                            curToken += curChar;
                            break;
                        }
                    }
                    curState = DELIMITER;
                    curDelimiter = curChar;
                    curDelimiterPtr = & curDelimiter;
                    if(curToken.length() > 0)
                    {
                        mTokens.push_back(curToken);
                        curToken = "";
                    }
                }
                else
                {
                    curToken += curChar;
                }
                break;
            case DELIMITER:
                if((mDelimiters.find(curChar) != std::string::npos))
                {
                    curDelimiter = curChar;
                    curDelimiterPtr = & curDelimiter;
                }
                else
                {
                    curToken += curChar;
                    curState = TOKEN;
                }

                break;
            default:
                return false;
                break;
        }
    }
    if(curToken.length() > 0)
    {
        mTokens.push_back(curToken);
    }

    return true;
}

std::vector<std::string>::iterator Tokenizer::begin()
{
    return mTokens.begin();
}

std::vector<std::string>::iterator Tokenizer::end()
{
    return mTokens.end();
}

std::vector<std::string> Tokenizer::getTokens()
{
    return mTokens;
}

size_t Tokenizer::getNumTokens()
{
    return mTokens.size();
}

