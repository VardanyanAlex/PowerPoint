
#ifndef PROCESSOR_COMMANDS_HPP
#define PROCESSOR_COMMANDS_HPP

#include <map>
#include <string>

//#include "interpreterRequirments.hpp"
#include "typecheckers.hpp"

enum class ECommand : int
{
    plus,
    minus,
    multiply,
    divide,
    assignData,
    assignReg,
    load,
    loadFuncArg,
    call,
    push,
    pop,
    pushSF,
    popSF,
    ret,

    nop
};

inline std::map<ECommand, const std::string> Command{
    {ECommand::plus, "ADD "},
    {ECommand::minus, "SUB "},
    {ECommand::multiply, "MUL "},
    {ECommand::divide, "DIV "},
    {ECommand::assignData, "MOV "},
    {ECommand::assignReg, "MVI "},
    {ECommand::load, "LOAD "},
    {ECommand::loadFuncArg, "LDREL "},
    {ECommand::call, "CALL "},
    {ECommand::push, "PUSH "},
    {ECommand::pop, "POP "},
    {ECommand::pushSF, "PUSHSF "},
    {ECommand::popSF, "POPSF "},
    {ECommand::ret, "RET "}
    
};

class UnexpectedOperator : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\n\tExcpetion thrown:  Unexpected operator \n";
    }
};

ECommand GetOperator(char cOp);



#endif // PROCESSOR_COMMANDS_HPP
