
#ifndef GETCONSOLEARGUMENTS_HPP
#define GETCONSOLEARGUMENTS_HPP

#include <string>

enum class EIOMode
{
    EFile,
    EConsole
};

void GetConsoleArguments(int iCountOfInputArgs, char** pInputArgs, std::unique_ptr<std::ostream>& OuputStream, std::unique_ptr<std::istream>& InputStream);

class CFileDetectionException : public std::exception
{
public:
    const char* what() const throw()  override
    {
        return "\n\tException thrown: File detection error\n";
    }
};


class CInputProgramException : public std::exception
{
public:
    const char* what() const throw()  override
    {
        return "\n\tException thrown: Unrecogonized input source program\n";
    }
};

class CWrongArgsException : public std::exception
{
public:
    const char* what() const throw()  override
    {
        return "\n\tException thrown: Unrecogonized arguments (syntax error)\n";
    }
};

#endif //GETCONSOLEARGUMENTS_HPP
