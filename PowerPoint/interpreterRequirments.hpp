
#ifndef INTERPRETER_REQUIRMENTS_HPP
#define INTERPRETER_REQUIRMENTS_HPP

#include <deque>
#include <filesystem>

#include "processorCommands.hpp"

constexpr int MAX_NUMBER = 65535;

constexpr int iInstructionSize = 28;
constexpr int iStackSize = 1024;

using Memory = std::byte*;

struct Registers
{
    bool ZeroFlag{};
    bool CarryFlag{};
    bool OverflowFlag{};
    bool SignFlag{};
    // general purpose registers
    std::vector<int> aGenPurposeRegisters;
    // special registers
    int iIPReg{};
    int iRIPReg{};
    int iSFReg{};
    int iSPReg{};

    Registers()
    {
        aGenPurposeRegisters = std::vector<int>(8, 0);
    }

    template<template < class > class Predicate, class T>
    void CalculateAndSetFlags(int& iNum1, int& iNum2);
};

 
struct SOperand
{
    enum class EOperandType : int
    {
        numberType,
        variableType,
        registerType,
        stackFrameAddrType,
        FunctionType,
        FunctionArgType,
        MemorySizeType,
    };

    /*union UValue
    {
        int iNumber;
        int iVariableIdtx;
        int iRegIdtx;
        int iOffset;
        int iFuncindex;
        int iMemSize;

        friend std::ostream& operator<<(std::ostream& out, const UValue& uValue)
        {
            out << uValue.
        }
    };*/

    EOperandType eOperandType;
    int iValue;

    SOperand(EOperandType eOpTypeRHS = EOperandType::numberType, int iOperandValue = 0)
        : eOperandType{ eOpTypeRHS }
        , iValue{ iOperandValue }
    {}

    std::string GetString(const SymbolTable& aSymbolTable) const
    {
        switch (eOperandType)
        {
        case EOperandType::numberType:
        case EOperandType::FunctionArgType:
            return std::to_string(iValue);
            break;
        case EOperandType::variableType:
            return aSymbolTable.GetVariableName(iValue);
            break;
        case EOperandType::registerType:
            return "R" + std::to_string(iValue);
            break;
        case EOperandType::stackFrameAddrType:
            return "SF " + std::to_string(iValue);
            break;
        case EOperandType::FunctionType:
            return aSymbolTable.GetFunctionName(iValue);
            break;
        case EOperandType::MemorySizeType:
            return std::to_string(iValue);
            break;
        }
    }
};

struct SInstruction
{
    SInstruction() {}

    SInstruction(ECommand eOpCodeRHS)
        : eOpCode{ eOpCodeRHS }
        , iOperandscount{ 0 }
    {}

    SInstruction(ECommand eOpCodeRHS, SOperand&& sOperand)
        : eOpCode{ eOpCodeRHS }
        , iOperandscount{ 1 }
        , sOperand1{ sOperand }
    {}
    SInstruction(ECommand eOpCodeRHS, SOperand&& sOperand1RHS, SOperand&& sOperand2RHS)
        : eOpCode{ eOpCodeRHS }
        , iOperandscount{ 2 }
        , sOperand1{ sOperand1RHS }
        , sOperand2{ sOperand2RHS }
    {}

    SInstruction(const SInstruction& sInsRHS)
        : eOpCode{ sInsRHS.eOpCode }
        , iOperandscount{ sInsRHS.iOperandscount }
        , sOperand1{ sInsRHS.sOperand1 }
        , sOperand2{ sInsRHS.sOperand2 }
    {}

    const SInstruction& operator=(SInstruction& sInsRHS)
    {
        eOpCode = sInsRHS.eOpCode;
        iOperandscount = sInsRHS.iOperandscount;
        sOperand1 = sInsRHS.sOperand1;
        sOperand2 = sInsRHS.sOperand2;
        return *this;
    }

    SInstruction& operator=(SInstruction&& sInsRHS) noexcept
    {
        eOpCode = sInsRHS.eOpCode;
        iOperandscount = sInsRHS.iOperandscount;
        sOperand1 = sInsRHS.sOperand1;
        sOperand2 = sInsRHS.sOperand2;

        return *this;
    }

    std::string GetString(const SymbolTable& aSymbolTable) const;

    ECommand eOpCode{ECommand::nop };             // 4 bytes

    // instruction extension
    const int iOperandSize = 8;   // 4 bytes
    int iOperandscount{};         // 4 bytes

    SOperand sOperand1{};         // 8 bytes
    SOperand sOperand2{};         // 8 bytes
};

struct SCode
{
    std::vector<std::vector<SInstruction>> aFunctions;
};

class CInterpreter
{
public:

    void        Work(Registers&, Memory&, SymbolTable&);
    void        PrintCurrentInfo(Registers&, Memory& RAM, const SymbolTable&);
    void        Trace(SInstruction&, Memory& RAM, Registers&, const SymbolTable&);
    void        Run(SInstruction&, Memory& RAM, Registers&, const SymbolTable&);
    void        SetBreakpoint();
    void        UnsetBreakpoints();
    void        ShowBreakpoints(Memory& RAM, const SymbolTable&);
    void        SetInitialState(Memory&, Registers&, SymbolTable&);
    void        Watch(Memory&, const SymbolTable&);
    void        PrintFromRAM(Memory&, const SymbolTable&);
    inline bool MainReturned(const int iSPReg);

    void SetStackAddr(const int StackAddrOffset) noexcept;
    void SetDataAddr(const int DataAddrOffset) noexcept;
    void SetCodeAddr(const int CodeAddrOffset) noexcept;

protected:
    enum class EDebugCommand
    {
        Help,
        Info,
        StepForward,
        Run,
        Reset,
        FuncAddrs,
        SetBreakpoint,
        UnsetBreakpoints,
        ShowBreakpoints,
        Watch,
        Print,
        Exit,

        Unrecognized
    };

    std::map<std::string, EDebugCommand> mCommand{
        { "help", EDebugCommand::Help } ,
        { "info", EDebugCommand::Info },
        { "t", EDebugCommand::StepForward } ,
        { "run", EDebugCommand::Run } ,
        { "reset", EDebugCommand::Reset } ,
        { "addrs", EDebugCommand::FuncAddrs },
        { "set bp", EDebugCommand::SetBreakpoint },
        { "unset bps", EDebugCommand::UnsetBreakpoints },
        { "sh all bps", EDebugCommand::ShowBreakpoints },
        { "watch", EDebugCommand::Watch },
        { "print", EDebugCommand::Print },
        { "exit", EDebugCommand::Exit } ,
    };

    enum class ECommandSpecifier : short
    {
        Last,
        Next
    };

protected:
    EDebugCommand GetCommand();
    SInstruction NextInstruction(const Memory& RAM, const int iIPReg);
    void GetRegsValuesFromStack(Memory& RAM, Registers&);
    void SetRegsValuesInStack(Memory& RAM, Registers&, const SInstruction&);

    bool IsValidOffset(int iOffset);

    std::filesystem::path sHelpFilePath{ "files/interpreter.HELP.txt" };

private:
    void PrintLogo() noexcept;
    void PrintTextDebugMode() noexcept;
    void PrintFunctionsOffsets(const SymbolTable&);
    void PrintTextProgramFinished() noexcept;
    void PrintCommand(const SInstruction&, const SymbolTable&, ECommandSpecifier);

private:
    int m_iStackAddrOffset{};
    int m_iStackFreeAddrOffset{};
    int m_iDataAddrOffset{};
    int m_iCodeAddrOffset{};

    std::deque<int> m_aBreakpointsList{};

    std::vector<int> m_aCurrRegs{ 0 };
};

void Load(Memory& RAM, SCode& sCodeSegment, VariablesData& aData, CInterpreter&);

void PrintRegisters(Registers&);

#endif // INTERPRETER_REQUIRMENTS_HPP
