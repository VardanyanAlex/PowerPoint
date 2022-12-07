
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "getConsoleArguments.hpp"

namespace
{

    EIOMode GetInputMode(int iCountOfInputArgs, char** pInputArgs)
    {
        EIOMode eInputMode = EIOMode::EConsole; // by default
        if ((iCountOfInputArgs >= 2) && static_cast<std::string>(pInputArgs[1]) == "--file")
        {
            eInputMode = EIOMode::EFile;
        }
        else if ((iCountOfInputArgs >= 2) && static_cast<std::string>(pInputArgs[1]) == "--console")
        {
            eInputMode = EIOMode::EConsole;
        }
        else
        {
            throw CInputProgramException{};
        }
        return eInputMode;
    }

    EIOMode GetOutputMode(int iCountOfInputArgs, char** pInputArgs)
    {
        EIOMode eOutputMode = EIOMode::EConsole; // by default
        if ((iCountOfInputArgs == 6) && static_cast<std::string>(pInputArgs[3]) == "--output" && static_cast<std::string>(pInputArgs[4]) == "-file")
        {
            eOutputMode = EIOMode::EFile;
        }
        else if ((iCountOfInputArgs == 5) && static_cast<std::string>(pInputArgs[3]) == "--output" && static_cast<std::string>(pInputArgs[4]) == "-console")
        {
            eOutputMode = EIOMode::EConsole;
        }
        else if ((iCountOfInputArgs == 3))
        {
            eOutputMode = EIOMode::EConsole;    //by default output must be in console
        }
        else
        {
             throw CWrongArgsException{};
        }
        return eOutputMode;
    }

    void GetProgramStream(std::string sProgramSource, EIOMode& eInputMode, std::unique_ptr<std::istream>& InputStream)
    {
        
        switch (eInputMode)
        {
        case EIOMode::EConsole:
            
            InputStream = std::move(std::make_unique<std::stringstream>(std::stringstream{ sProgramSource }));

            break;
        case EIOMode::EFile:

            if( std::filesystem::exists(sProgramSource) )
            {
                InputStream = std::move(std::make_unique<std::ifstream>(std::ifstream{ sProgramSource }));
            }
            else
            {
                 throw CFileDetectionException{};
            }

            break;
        default:
            break;
        }
    }

}  // unnamed namespace

void GetConsoleArguments(int iCountOfInputArgs, char** pInputArgs, std::unique_ptr<std::ostream>& OuputStream, std::unique_ptr<std::istream>& InputStream)
{

    EIOMode eInputMode = GetInputMode(iCountOfInputArgs, pInputArgs);

    //std::string sProgramSource = pInputArgs[2];  // can be program file or source code from console

    GetProgramStream(std::string(pInputArgs[2]), eInputMode, InputStream);


    EIOMode eOutputMode = GetOutputMode(iCountOfInputArgs, pInputArgs);

    switch (eOutputMode)
    {
    case EIOMode::EFile:
        OuputStream = std::move(std::make_unique<std::ofstream>(std::ofstream{ pInputArgs[5] }));
        break;
    case EIOMode::EConsole:
        OuputStream = std::move(std::make_unique<std::stringstream>(std::stringstream{}));
        break;
    default:
        break;
    }

}
