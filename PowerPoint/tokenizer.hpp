
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

#include "SymbolTable.hpp"
#include "tree.hpp"
#include "typecheckers.hpp"

/*
* brief: makes token from lexemme and returns it
*/
SToken nextToken(std::istream& Input, SymbolTable& aSymbolTable);

class CEndOfExprDetection : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: expected ;\n";
    }
};


#endif  //  TOKENIZER_HPP