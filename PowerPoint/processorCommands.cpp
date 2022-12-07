
#include "processorCommands.hpp"
#include "interpreterRequirments.hpp"



ECommand GetOperator(char cOp)
{
    switch (cOp)
    {
    case '+':
        return ECommand::plus;
        break;
    case '-':
        return ECommand::minus;
        break;
    case '*':
        return ECommand::multiply;
        break;
    case '/':
        return ECommand::divide;
        break;
    default:
        throw UnexpectedOperator{};
        break;
    }
}

