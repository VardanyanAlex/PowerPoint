

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <map>

struct STokenFunc
{
    int FuncIdentifierIdx{};
    std::vector<int> aFuncArgs;
    std::vector<std::string> aFuncArgNames;

    STokenFunc() {}

    STokenFunc(int iIdtfIdx)
        : FuncIdentifierIdx{ iIdtfIdx }
    {}

    STokenFunc(int iIdtfIdx, std::vector<int> aArgs, std::vector<std::string> aArgNames)
        : FuncIdentifierIdx{ iIdtfIdx }
        , aFuncArgs{ aArgs }
        , aFuncArgNames{aArgNames}
    {}

    //STokenFunc(STokenFunc&& sFunc)
    //    : FuncIdentifierIdx{ sFunc.FuncIdentifierIdx }
    //    , aFuncArgs{ std::move(sFunc.aFuncArgs) }
    //    , aFuncArgNames{ std::move(sFunc.aFuncArgNames) }
    //{}

    //STokenFunc(const STokenFunc& sFunc)
    //    : FuncIdentifierIdx{ sFunc.FuncIdentifierIdx }
    //    , aFuncArgs{ sFunc.aFuncArgs }
    //    , aFuncArgNames{ sFunc.aFuncArgNames }
    //{}

};

enum EKeywordType : int
{
    func = 1,
    var = 2,
    constexp = 4,
    begin = 8,
    end = 16
};

inline std::map<std::string, EKeywordType> KeywordId{
    {"func", EKeywordType::func},
    {"var", EKeywordType::var},
    {"constexpr", EKeywordType::constexp},
    {"begin", EKeywordType::begin},
    {"end", EKeywordType::end}
};

enum class ETokenType
{
    IdentifierType,
    NumberType,
    OperatorType,
    FunctionType,
    FunctionArgType,
    EndOfExprType,
    EndOfStatementType,
    KeywordType
};

struct SToken
{
    ETokenType eType ;
    union
    {
        int TokenIdentifierIdx;
        int TokenNumber;
        char         TokenOperator;
        char         TokenEndOfStatement;
        char         TokenEndOfExpr;
        unsigned int TokenKeyword;
    };

    STokenFunc TokenFunction;

    SToken(ETokenType eTypeToken = ETokenType::NumberType, int iValue = 0) :
        eType(eTypeToken),
        TokenNumber(iValue)
    {};


    

    friend std::ostream& operator<<(std::ostream& Output, SToken& sToken)
    {
        if(sToken.eType == ETokenType::NumberType)
        {
            Output << sToken.TokenNumber << " ";
        }
        else if(sToken.eType == ETokenType::IdentifierType)
        {
            Output << sToken.TokenIdentifierIdx << " ";
        }
        else if(sToken.eType == ETokenType::OperatorType)
        {
            Output << sToken.TokenOperator << " ";
        }
        else if(sToken.eType == ETokenType::EndOfStatementType)
        {
            Output << sToken.TokenEndOfStatement << " ";
        }
        else if (sToken.eType == ETokenType::EndOfExprType)
        {
            Output << sToken.TokenEndOfExpr << " ";
        }
        return Output;
    }
    
};


#endif  //TOKEN_HPP

