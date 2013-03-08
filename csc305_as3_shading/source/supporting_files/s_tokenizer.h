#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

/**
 *	@class	Tokenizer
 *	@brief	class to tokenize a string based on given delimiters
 */
class Tokenizer
{
public:

    /**
     *	default constructor
     */
    Tokenizer();

    /**
     *	constructor with given BaseString
     *	the delimiters are filled with default values
     *	@param	m_BaseString the string to tokenize
     */
    Tokenizer(std::string m_BaseString);

    /**
     *	constructor with given BaseString and Delimiters
     *	@param	m_BaseString the string to tokenize
     *	@param	m_Delimiters a set of string delimiters
     */
    Tokenizer(std::string m_BaseString, std::string m_Delimiters);

    /**
     *	default destructor
     */
    ~Tokenizer();

    /**
     *	tokenizes the given string
     *	@param	m_BaseString the string to tokenize
     *	@return	returns if success
     */
    bool tokenize(std::string m_BaseString);

    /**
     *	tokenizes the string that is currently set
     */
    bool tokenize();

    /**
     *	gets the iterator to the first token
     *	@return	iterator to begin
     */
    std::vector<std::string>::iterator begin();

    /**
     *	gets the iterator to the last token
     *	@return	iterator to end
     */
    std::vector<std::string>::iterator end();

    /**
     *	gets a reference to the tokens
     *	@return	returns the full vector
     */
    std::vector<std::string> getTokens();

    /**
     *	gets the number of tokens
     *	@return	returns the number of tokens
     */
    size_t getNumTokens();

private:

    /**
     *	@brief	private enum for handling the tokenizer state
     */
    typedef enum
    {
        TOKEN,		/**< if the tokenizer is currently reading a token. */
        DELIMITER	/**< if the tokenizer is currently reading a delimiter, which can potentially change the delimiter char. */
    } state;

    std::string			mBaseString;	/**< the string to tokenize. */
    std::string			mDelimiters;	/**< vector containing all of the delimiters. */

    std::vector<std::string> mTokens;	/**< the tokens after tokenizing. */
};

#endif // TOKENIZER_H
