
#ifndef CALCEXPR_HPP
#define CALCEXPR_HPP

#include <deque>

#include "functionParse.hpp"
#include "tokenizer.hpp"

int CalcSimpleExpr(std::istream& InputStream, VariablesData&, SymbolTable&, SToken&);

void calcConstExpFunc(std::istream& InputStream, SFunction&, VariablesData&, SymbolTable&, SToken&);

int EvaluateTree(const Tree&, const FunctionArgsValues&, FunctionsData&, const VariablesData&);

#endif // CALCEXPR_HPP