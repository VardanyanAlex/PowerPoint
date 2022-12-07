

#ifndef TREE_HPP
#define TREE_HPP

#include <exception>
#include <memory>
#include <vector>

#include "token.hpp"

struct STree
{
    SToken Value;
    //size_t IdxInTokens;
    std::unique_ptr<STree> pLeft = nullptr;
    std::unique_ptr<STree> pRight = nullptr;
};

using Tree = std::unique_ptr<STree>;
using Trees = std::map<std::string, Tree>;

//creates tree's one node
std::unique_ptr<STree> CreateTree(SToken& sToken, std::unique_ptr<STree> = nullptr, std::unique_ptr<STree> = nullptr ) ;

//prints tabs during tree printing
void PrintTabs(int iNumOfTabs);

//recursively prints all layers of parse tree
void PrintTreeLayers(std::unique_ptr<STree>& pParseTree, int iLevelOfTree);

//adapter for "printTreeLayers" funtion
void PrintParseTree(std::unique_ptr<STree>& pParseTree);


class CTreeException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\n\tExcpetion thrown:  Can't allocate memory for STree \n";
    }
};


#endif  // TREE_HPP