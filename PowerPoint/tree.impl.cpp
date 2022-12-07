

#include <iostream>

#include "tree.hpp"


//creates tree's one node
std::unique_ptr<STree> CreateTree(SToken& sToken, std::unique_ptr<STree> pLeftTreeInit, std::unique_ptr<STree> pRightTreeInit) 
{
    std::unique_ptr<STree> pNewTree = nullptr;
    try
    {
        CTreeException e;
        pNewTree = std::unique_ptr<STree>(new STree) ;
        if(pNewTree == nullptr)
        {
            throw e;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() ;
        exit(1);
    }

    pNewTree->Value = sToken;
    pNewTree->pLeft = std::move(pLeftTreeInit);
    pNewTree->pRight = std::move(pRightTreeInit);

    return std::move(pNewTree);
} 

//prints tabs during tree printing
void PrintTabs(int iNumOfTabs)
{
    for (int i = 0; i < iNumOfTabs-1; ++i)
    {
        std::cout << "\t";
    }
}

//recursively prints all layers of parse tree
void PrintTreeLayers(std::unique_ptr<STree>& pParseTree, int iLevelOfTree)
{
    if(pParseTree == nullptr)
    {
        return;
    }
    PrintTabs(iLevelOfTree);
    std::cout << "value = " <<  pParseTree->Value << std::endl;
    PrintTabs(iLevelOfTree);
    std::cout << "left " << std::endl;
    PrintTreeLayers(pParseTree->pLeft, iLevelOfTree + 1);

    PrintTabs(iLevelOfTree);
    std::cout << "right " << std::endl;
    PrintTreeLayers(pParseTree->pRight, iLevelOfTree + 1);

}

//adapter for "printTreeLayers" funtion
void PrintParseTree(std::unique_ptr<STree>& pParseTree)
{
    PrintTreeLayers(pParseTree, 1);
    std::cout << std::endl << std::endl;
}


