
#include <cstring>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "tokenizer.hpp"
#include "typecheckers.hpp"

SToken nextToken(std::istream& Input, SymbolTable& aSymbolTable)
{
    std::string sLexemme = nextLexemme(Input);

    SToken sToken;
    if (IsKeyword(sLexemme))
    {
        sToken.eType = ETokenType::KeywordType;
        sToken.TokenKeyword = static_cast<unsigned int>(KeywordId[sLexemme]);
        /*sToken.TokenKeyword = new char[sLexemme.size()];
        strcpy_s(sToken.TokenKeyword, 8, const_cast<char*>(sLexemme.c_str()));*/
    }
    else if(IsOperator(sLexemme[0]))
    {
        sToken.eType = ETokenType::OperatorType;
        sToken.TokenOperator = sLexemme[0];
    }
    else if(IsIdentifier(sLexemme))
    {   
        sToken.eType = ETokenType::IdentifierType;

        /*if (aSymbolTable.isVariableDefined(sLexemme))
        {
            sToken.TokenIdentifierIdx = aSymbolTable.GetIdentifierIdx(sLexemme);
        }
        else
        {
            sToken.TokenIdentifierIdx = aSymbolTable.VariablesNamesCount();
            aSymbolTable.InsertVariableName(sLexemme);
        }*/

        //variableneri texy stugi ete arden define axaca exception tur       !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        sToken.TokenIdentifierIdx = aSymbolTable.VariablesNamesCount();
        aSymbolTable.InsertVariableName(sLexemme);
    }
    else if(IsNumber(sLexemme))
    {
        sToken.eType = ETokenType::NumberType;
        sToken.TokenNumber = stoi(sLexemme);
    }
    else if (IsEndOfExpr(sLexemme[0]))
    {
        sToken.eType = ETokenType::EndOfExprType;
        sToken.TokenEndOfExpr = sLexemme[0];
    }
    else if(IsEndOfStatement(sLexemme[0]))
    {
        sToken.eType = ETokenType::EndOfStatementType;
        sToken.TokenEndOfStatement = sLexemme[0];
    }
    else
    {
        if (sLexemme == "")
        {
            CEndOfExprDetection e;
            throw e;
        }
    }
    
    return sToken;
}

