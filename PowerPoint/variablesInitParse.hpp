
#ifndef VARIABLESINITPARSE_HPP
#define VARIABLESINITPARSE_HPP

#include "tokenizer.hpp"

Tree&& ParseVarInit(VariablesData&, FunctionsData&, std::istream& Input, SymbolTable&);

#endif // VARIABLESINITPARSE_HPP