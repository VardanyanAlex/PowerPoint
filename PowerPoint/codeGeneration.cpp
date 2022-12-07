
#include <fstream>
#include <iostream>

#include "codeGeneration.hpp"
#include "interpreterRequirments.hpp"
#include "processorCommands.hpp"
#include "token.hpp"

#define TAB "\t"
#define REGISTER "R"

using Regst = int;
constexpr const int uSizeOfVar = 4;

namespace
{   
    void CodeGeneratorExpression(Tree& pParseTree, std::ostream& OutputProgram, std::vector< SInstruction >& aInstructions, SymbolTable& aSymbolTable, CRegisterAllocator& aRegisters, std::vector<SToken>& stackFrame)
    {
        if (pParseTree != nullptr)
        {
            CodeGeneratorExpression(pParseTree->pLeft, OutputProgram, aInstructions, aSymbolTable, aRegisters, stackFrame);

            CodeGeneratorExpression(pParseTree->pRight, OutputProgram, aInstructions, aSymbolTable, aRegisters ,stackFrame);

            switch (pParseTree->Value.eType)
            {
            case ETokenType::OperatorType:
            {
                Regst uRegister = aRegisters.LastUsedRegister();
                for (int iReg = uRegister; uRegister - iReg < 2 && iReg >= 0; --iReg)
                {
                    if (!aRegisters.IsBusy(iReg) && !stackFrame.empty())
                    {
                        SToken sToken = stackFrame.back();
                        stackFrame.pop_back();

                        OutputProgram << TAB << Command[ECommand::pop] << REGISTER << iReg << std::endl;
                        aInstructions.emplace_back(ECommand::pop, std::move(SOperand{ SOperand::EOperandType::registerType, iReg }));
                        aRegisters.PutInRegister(sToken, iReg);
                    }
                }

                OutputProgram << TAB << Command[GetOperator(pParseTree->Value.TokenOperator)];
                size_t i = 2;
                std::vector<int> aRegistersNumbers{ 2, 0 };
                for (i; i != 0; --i)
                {
                    int iLastUsedReg = aRegisters.LastUsedRegister();
                    OutputProgram << REGISTER << iLastUsedReg << " ";
                    aRegistersNumbers[i - 1] = iLastUsedReg;
                    if (i != 1)
                    {
                        aRegisters.UnloadRegister();
                    }
                }
                aInstructions.emplace_back(GetOperator(pParseTree->Value.TokenOperator),
                                            std::move(SOperand{ SOperand::EOperandType::registerType, aRegistersNumbers[0] }),
                                            std::move(SOperand{ SOperand::EOperandType::registerType, aRegistersNumbers[1] }));
                aRegistersNumbers.clear();
                OutputProgram << std::endl;
            }
                break;
            case ETokenType::NumberType:
                if (aRegisters.HaveFreeRegister())
                {
                    Regst uFreeRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uFreeRegister);

                    OutputProgram << TAB << Command[ECommand::assignData] << REGISTER << uFreeRegister << " " << pParseTree->Value << std::endl;
                    aInstructions.emplace_back(ECommand::assignData,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uFreeRegister }),
                        std::move(SOperand{ SOperand::EOperandType::numberType, pParseTree->Value.TokenNumber }));
                }
                else if (stackFrame.empty())
                {
                    aRegisters.SetInitialState();
                    stackFrame.push_back(aRegisters.GetFirstReg());

                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);
                    OutputProgram << TAB << Command[ECommand::push] << " R" << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::push,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));

                    OutputProgram << TAB << Command[ECommand::assignData] << REGISTER << uRegister << " " << pParseTree->Value << std::endl;
                    aInstructions.emplace_back(ECommand::assignData,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::numberType, pParseTree->Value.TokenNumber }));
                }
                else
                {
                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);
                    
                    stackFrame.push_back(aRegisters[uRegister]);
                    
                    OutputProgram << TAB << Command[ECommand::push] <<  " R" << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::push,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));

                    OutputProgram << TAB << Command[ECommand::assignData] << REGISTER << uRegister << " " << pParseTree->Value << std::endl;
                    aInstructions.emplace_back(ECommand::assignData,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::numberType, pParseTree->Value.TokenNumber }));
                }
                break;
            case ETokenType::IdentifierType:
                if (aRegisters.HaveFreeRegister())
                {
                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);

                    OutputProgram << TAB << Command[ECommand::assignData] << REGISTER << uRegister << " [" << aSymbolTable.GetVariableName(pParseTree->Value.TokenIdentifierIdx) << "]" << std::endl;
                    aInstructions.emplace_back(ECommand::assignData,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::variableType, pParseTree->Value.TokenIdentifierIdx }));

                    OutputProgram << TAB << Command[ECommand::load] << REGISTER << uRegister << " " << REGISTER << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::load,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));
                }
                else if(stackFrame.empty())
                {                               //pParseTree->Value
                    aRegisters.SetInitialState();
                    stackFrame.push_back(aRegisters.GetFirstReg());

                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);
                    
                    OutputProgram << TAB << Command[ECommand::assignData] << REGISTER << uRegister << " [" << aSymbolTable.GetVariableName(pParseTree->Value.TokenIdentifierIdx) << "]" << std::endl;
                    aInstructions.emplace_back(ECommand::assignData,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::variableType, pParseTree->Value.TokenIdentifierIdx }));

                    OutputProgram << TAB << Command[ECommand::load] << REGISTER << uRegister << " R" << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::load,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));
                }

                break;
            case ETokenType::FunctionArgType:
                if (aRegisters.HaveFreeRegister())
                {
                    Regst uFreeRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uFreeRegister);

                    OutputProgram << TAB << Command[ECommand::loadFuncArg] << REGISTER << uFreeRegister << " SF " << -4 * pParseTree->Value.TokenIdentifierIdx - 8 << std::endl;
                    aInstructions.emplace_back(ECommand::loadFuncArg,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uFreeRegister }),
                        std::move(SOperand{ SOperand::EOperandType::stackFrameAddrType, -4 * pParseTree->Value.TokenIdentifierIdx - 8 }));
                }
                else if (stackFrame.empty())
                {
                    aRegisters.SetInitialState();
                    stackFrame.push_back(aRegisters.GetFirstReg());

                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);
                    OutputProgram << TAB << Command[ECommand::push] << " R" << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::push,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));

                    OutputProgram << TAB << Command[ECommand::loadFuncArg] << REGISTER << uRegister << " SF " << -4 * pParseTree->Value.TokenIdentifierIdx - 8 << std::endl;
                    aInstructions.emplace_back(ECommand::loadFuncArg,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::stackFrameAddrType, -4 * pParseTree->Value.TokenIdentifierIdx - 8 }));
                }
                else
                {
                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);
                    
                    stackFrame.push_back(aRegisters[uRegister]);

                    OutputProgram << TAB << Command[ECommand::push] << " R" << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::push,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));

                    OutputProgram << TAB << Command[ECommand::loadFuncArg] << REGISTER << uRegister << " SF " << -4 * pParseTree->Value.TokenIdentifierIdx - 8 << std::endl;
                    aInstructions.emplace_back(ECommand::loadFuncArg,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::stackFrameAddrType, -4 * pParseTree->Value.TokenIdentifierIdx - 8 }));
                }
                break;
            case ETokenType::FunctionType:
                if (aRegisters.HaveFreeRegister())
                {
                    Regst uFreeRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uFreeRegister);

                    OutputProgram << TAB << Command[ECommand::assignReg] << REGISTER << uFreeRegister << " " << aSymbolTable.GetFunctionName(pParseTree->Value.TokenFunction.FuncIdentifierIdx) << "()" << std::endl;
                    aInstructions.emplace_back(ECommand::assignReg,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uFreeRegister }),
                        std::move(SOperand{ SOperand::EOperandType::FunctionType, pParseTree->Value.TokenFunction.FuncIdentifierIdx }));

                    for (int i = pParseTree->Value.TokenFunction.aFuncArgs.size() - 1; i >= 0 ; --i)
                    {
                        OutputProgram << TAB << Command[ECommand::push] << pParseTree->Value.TokenFunction.aFuncArgs[i] << std::endl;
                        aInstructions.emplace_back(ECommand::push,
                            std::move(SOperand{ SOperand::EOperandType::FunctionArgType, pParseTree->Value.TokenFunction.aFuncArgs[i] }));
                    }

                    OutputProgram << TAB << Command[ECommand::call] << REGISTER << uFreeRegister << std::endl;
                    aInstructions.emplace_back(ECommand::call,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uFreeRegister }));
                }
                else if (stackFrame.empty())
                {
                    aRegisters.SetInitialState();
                    stackFrame.push_back(aRegisters.GetFirstReg());

                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);
                    
                    OutputProgram << TAB << Command[ECommand::assignReg] << REGISTER << uRegister << " " << aSymbolTable.GetFunctionName(pParseTree->Value.TokenIdentifierIdx) << "()" << std::endl;
                    aInstructions.emplace_back(ECommand::assignReg,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::FunctionType, pParseTree->Value.TokenIdentifierIdx }));

                    OutputProgram << TAB << Command[ECommand::call] << REGISTER << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::call,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));
                }
                else
                {
                    Regst uRegister = aRegisters.GiveRegister();
                    aRegisters.PutInRegister(pParseTree->Value, uRegister);

                    stackFrame.push_back(aRegisters[uRegister]);

                    OutputProgram << TAB << Command[ECommand::assignReg] << REGISTER << uRegister << " " << aSymbolTable.GetFunctionName(pParseTree->Value.TokenIdentifierIdx) << "()" << std::endl;
                    aInstructions.emplace_back(ECommand::assignReg,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }),
                        std::move(SOperand{ SOperand::EOperandType::FunctionType, pParseTree->Value.TokenIdentifierIdx }));

                    OutputProgram << TAB << Command[ECommand::call] << REGISTER << uRegister << std::endl;
                    aInstructions.emplace_back(ECommand::call,
                        std::move(SOperand{ SOperand::EOperandType::registerType, uRegister }));
                }
                break;
            default:
                break;
            }
        }
    }

    std::vector< SInstruction > GenerateFunctionBodyCode(FunctionsData::iterator itFunction, const int iFuncIdx, std::ostream& OutputProgram, SymbolTable& aSymbolTable, CRegisterAllocator& aRegisters, std::vector<SToken>& stackFrame)
    {
        std::vector< SInstruction > aFuncInstructions;
        OutputProgram << TAB << Command[ECommand::pushSF] << std::endl;
        aFuncInstructions.emplace_back(ECommand::pushSF);
        // push args in stack
        CodeGeneratorExpression(*itFunction, OutputProgram, aFuncInstructions, aSymbolTable, aRegisters, stackFrame);

        OutputProgram << TAB << Command[ECommand::popSF] << std::endl;
        aFuncInstructions.emplace_back(ECommand::popSF);

        OutputProgram << TAB << Command[ECommand::ret] << aSymbolTable.GetFunctionArgsCount(iFuncIdx) * uSizeOfVar << std::endl;
        aFuncInstructions.emplace_back(ECommand::ret, std::move(SOperand{ SOperand::EOperandType::MemorySizeType, aSymbolTable.GetFunctionArgsCount(iFuncIdx) * uSizeOfVar }));
        aSymbolTable.SetFuncOffset(aFuncInstructions.size() * iInstructionSize);
        
        return aFuncInstructions;
    }

    void CodeGeneratorVariable(std::ostream& OutputProgram, VariablesData& aData, SymbolTable& aSymbolTable)
    {
        OutputProgram << "\n.DATA\n";
        for (auto it = aData.begin(); it != aData.end(); std::advance(it, 1))
        {
            OutputProgram << aSymbolTable.GetVariableName(std::distance(aData.begin(), it)) << " = ";
            OutputProgram << *it;
            OutputProgram << std::endl;
        }
    }

    void CodeGeneratorFunctions(FunctionsData& aFunctions, SCode& sCodeSegment, std::ostream& OutputProgram, SymbolTable& aSymbolTable)
    {
        OutputProgram << "\n.CODE\n";
        for (FunctionsData::iterator itFunction = aFunctions.begin(); itFunction != aFunctions.end(); std::advance(itFunction, 1))
        {
            if (*itFunction)
            {
                CRegisterAllocator aRegisters(8);
                std::vector<SToken> stackFrame;
                const int iFuncIdx = std::distance(aFunctions.begin(), itFunction);
                OutputProgram << aSymbolTable.GetFunctionName(iFuncIdx) << "(): \n";
                sCodeSegment.aFunctions.push_back( GenerateFunctionBodyCode(itFunction, iFuncIdx, OutputProgram, aSymbolTable, aRegisters, stackFrame) );
                OutputProgram << "EndF \n\n";
            }
        }
    }

    void CodeGeneratorProgram(FunctionsData& aFunctions, VariablesData& aVariables, SCode& sCodeSegment, std::ostream& OutputProgram, SymbolTable& aSymbolTable)
    {
        OutputProgram << "\n.STACK = 1024\n";


        CodeGeneratorVariable(OutputProgram, aVariables, aSymbolTable);
        CodeGeneratorFunctions(aFunctions, sCodeSegment, OutputProgram, aSymbolTable);
    }
} // unnamed namespace

void CodeGenerator(FunctionsData& aFunctions, VariablesData& aVariables, SCode& sCodeSegment, std::ostream& OutputStream, SymbolTable& aSymbolTable)
{
    CodeGeneratorProgram(aFunctions, aVariables, sCodeSegment, OutputStream, aSymbolTable);

    if (typeid(OutputStream).name() != "class std::basic_ofstream<char,struct std::char_traits<char> >")
    {
        //std::cout << OutputStream.rdbuf() << std::endl;
    }
}
