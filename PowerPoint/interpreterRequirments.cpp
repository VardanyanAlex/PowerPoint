
#include <bitset>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <windows.h>   // WinApi header

#include "interpreterRequirments.hpp"

std::string SInstruction::GetString(const SymbolTable& aSymbolTable) const
{
    std::string sCommand = Command[eOpCode];
    if (iOperandscount == 1)
    {
        sCommand += sOperand1.GetString(aSymbolTable);
    }
    else if (iOperandscount == 2)
    {
        sCommand += sOperand1.GetString(aSymbolTable) + " " + sOperand2.GetString(aSymbolTable);
    }

    return sCommand;
}

void Load(Memory& RAM, SCode& sCodeSegment, VariablesData& aData, CInterpreter& cInterpreter)
{
    const int iDataSize = aData.size() * 4;  // DATA size
    int iCodeSize{};

    // Getting CODE size
    for (size_t i = 0; i < sCodeSegment.aFunctions.size(); ++i)
    {
        iCodeSize += sCodeSegment.aFunctions[i].size() * iInstructionSize;
    }

    RAM = new std::byte[iDataSize + iCodeSize + iStackSize];

    // Loading Code in RAM
    int iOffset{};
    for (size_t i = 0; i < sCodeSegment.aFunctions.size(); ++i)
    {
        memcpy(&RAM[0 + iOffset], reinterpret_cast<const void*>(&sCodeSegment.aFunctions[i][0]), iInstructionSize * sCodeSegment.aFunctions[i].size());
        iOffset += iInstructionSize * sCodeSegment.aFunctions[i].size();
    }

    // Loading Data in RAM
    memcpy(&RAM[0 + iCodeSize], reinterpret_cast<const void*>(&aData[0]), iDataSize);

    /////////////
    /*   Code  */
    /*_________*/
    /*   Data  */
    /*_________*/
    /*  Stack  */
    /*         */
    /*         */
    /*_________*/
    cInterpreter.SetCodeAddr(0);
    cInterpreter.SetDataAddr(iCodeSize);
    cInterpreter.SetStackAddr(iCodeSize + iDataSize);
}

template<template < class > class Predicate, class T>
void Registers::CalculateAndSetFlags(int& iNum1, int& iNum2 )
{
    if (std::signbit(iNum1 + 0.0) == std::signbit(iNum2 + 0.0))
    {
        if (std::abs(iNum1) + std::abs(iNum2) > MAX_NUMBER)
        {
            OverflowFlag = 1;
        }
    }
    int iOpRes = Predicate<T>()(iNum1, iNum2);
    SignFlag = std::signbit(iOpRes + 0.0);
    ZeroFlag = !(iOpRes | 0);
    if (iOpRes > 0 && (((iOpRes << 15) >> 31) & 1))
    {
        CarryFlag = 1;
    }

    iNum1 = iOpRes;
}

void PrintRegisters(Registers& aRegisters)
{
    std::cout << std::endl;
    std::cout << "Flag Registers---------------------------------------------------------------------\n";
    std::cout << "OF(" << aRegisters.OverflowFlag << ")  ZF(" << aRegisters.ZeroFlag << ")  CF(" << aRegisters.CarryFlag << ")  SF(" << aRegisters.SignFlag << ")" << std::endl;
    std::cout << "Special Registers------------------------------------------------------------------\n";
    std::cout << "IP = " << std::bitset<16>(aRegisters.iIPReg / iInstructionSize) << "\t RIP = " << std::bitset<16>(aRegisters.iRIPReg / iInstructionSize) << std::endl;
    std::cout << "SF = " << std::bitset<16>(aRegisters.iSFReg / iInstructionSize) << "\t SP  = " << std::bitset<16>(aRegisters.iSPReg  / iInstructionSize) << std::endl;
    std::cout << "General purpose Registers----------------------------------------------------------\n";
    for (size_t i = 0; i < 4; ++i)
    {
        std::cout << "R" << 2 * i << " = " << std::bitset<16>(aRegisters.aGenPurposeRegisters[2 * i]) << "\t R" << 2 * i + 1 << "  = " << std::bitset<16>(aRegisters.aGenPurposeRegisters[2 * i + 1]) << std::endl;
    }
}

void CInterpreter::PrintLogo() noexcept
{
    //// set code page to utf8
    SetConsoleOutputCP(CP_UTF8);                        

    //// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    //setvbuf(stdout, nullptr, _IOFBF, 1000);
    std::cout << "\n\n\n\t\t────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n";
    std::cout << "\t\t  ─████████████───██████████████─██████████████───██████──██████─██████████████─██████████████─██████████████─████████████████───██████──██████────────██████████████─  \n";
    std::cout << "\t\t  ─██░░░░░░░░████─██░░░░░░░░░░██─██░░░░░░░░░░██───██░░██──██░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░░░██───██░░██──██░░██────────██░░░░░░░░░░██─  \n";
    std::cout << "\t\t  ─██░░████░░░░██─██░░██████████─██░░██████░░██───██░░██──██░░██─██░░██████████─██░░██████████─██░░██████████─██░░████████░░██───██░░██──██░░██────────██░░██████████─  \n";
    std::cout << "\t\t  ─██░░██──██░░██─██░░██─────────██░░██──██░░██───██░░██──██░░██─██░░██─────────██░░██─────────██░░██─────────██░░██────██░░██───██░░██──██░░██────────██░░██─────────  \n";
    std::cout << "\t\t  ─██░░██──██░░██─██░░██████████─██░░██████░░████─██░░██──██░░██─██░░██─────────██░░██─────────██░░██████████─██░░████████░░██───██░░██──██░░██────────██░░██████████─  \n";
    std::cout << "\t\t  ─██░░██──██░░██─██░░░░░░░░░░██─██░░░░░░░░░░░░██─██░░██──██░░██─██░░██──██████─██░░██──██████─██░░░░░░░░░░██─██░░░░░░░░░░░░██───██░░██──██░░██────────██░░░░░░░░░░██─  \n";
    std::cout << "\t\t  ─██░░██──██░░██─██░░██████████─██░░████████░░██─██░░██──██░░██─██░░██──██░░██─██░░██──██░░██─██░░██████████─██░░██████░░████───██░░██──██░░██────────██░░██████░░██─  \n";
    std::cout << "\t\t  ─██░░██──██░░██─██░░██─────────██░░██────██░░██─██░░██──██░░██─██░░██──██░░██─██░░██──██░░██─██░░██─────────██░░██──██░░██─────██░░░░██░░░░██────────██░░██──██░░██─  \n";
    std::cout << "\t\t  ─██░░████░░░░██─██░░██████████─██░░████████░░██─██░░██████░░██─██░░██████░░██─██░░██████░░██─██░░██████████─██░░██──██░░██████─████░░░░░░████─██████─██░░██████░░██─  \n";
    std::cout << "\t\t  ─██░░░░░░░░████─██░░░░░░░░░░██─██░░░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░██──██░░░░░░██───████░░████───██░░██─██░░░░░░░░░░██─  \n";
    std::cout << "\t\t  ─████████████───██████████████─████████████████─██████████████─██████████████─██████████████─██████████████─██████──██████████─────██████─────██████─██████████████─  \n";
    std::cout << "\t\t────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n\n\n\n";
    
}

inline void CInterpreter::PrintTextDebugMode() noexcept
{
    std::cout << std::endl << "\t DEBUG MODE" << std::endl << std::endl;
}

void CInterpreter::PrintFunctionsOffsets(const SymbolTable& aSymbolTable)
{
    std::cout << "\n\t" << "Address\t\t" << " Name\t\t\t" << "Instr. Count" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    for (int i = 0; i < aSymbolTable.FunctionsCount() - 1; ++i)
    {
        std::cout << "|\t" << aSymbolTable.GetFunctionOffset(i) << "\t\t| ";
        std::cout.width(14);
        std::cout << std::left << aSymbolTable.GetFunctionName(i) << "\t| ";
        std::cout.width(5);
        std::cout << std::left << (aSymbolTable.GetFunctionOffset(i + 1) - aSymbolTable.GetFunctionOffset(i)) / iInstructionSize << "|" << std::endl;
    }
    std::cout << "|\t" << aSymbolTable.GetFunctionOffset(aSymbolTable.FunctionsCount() - 1) << "\t\t| ";
    std::cout.width(14);
    std::cout << std::left << aSymbolTable.GetFunctionName(aSymbolTable.FunctionsCount() - 1) << "\t| ";
    std::cout.width(5);
    std::cout << std::left << (m_iDataAddrOffset - aSymbolTable.GetFunctionOffset(aSymbolTable.FunctionsCount() - 1)) / iInstructionSize << "|" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl << std::endl;
}

inline void CInterpreter::PrintTextProgramFinished() noexcept
{
    std::cout << "\t Program debug finished ! \n\n";
}

void CInterpreter::SetStackAddr(const int StackAddrOffset) noexcept
{
    m_iStackAddrOffset = StackAddrOffset;
}

void CInterpreter::SetDataAddr(const int DataAddrOffset) noexcept
{
    m_iDataAddrOffset = DataAddrOffset;
}

void CInterpreter::SetCodeAddr(const int CodeAddrOffset) noexcept
{
    m_iCodeAddrOffset = CodeAddrOffset;
}

inline void CInterpreter::PrintCommand(const SInstruction& sInstruction, const SymbolTable& aSymbolTable, ECommandSpecifier eCommandInfoSpecifier)
{
    std::cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;
    switch (eCommandInfoSpecifier)
    {
    case ECommandSpecifier::Last:
        std::cout << "\t Last Command: ";
        break;
    case ECommandSpecifier::Next:
        std::cout << "\t Next Command: ";
        break;
    }
    std::cout << sInstruction.GetString(aSymbolTable) << std::endl << std::endl;
}

inline CInterpreter::EDebugCommand CInterpreter::GetCommand()
{
    std::cout << "Debug --> ";
    std::string sDebugInputCommand{};
    std::getline(std::cin, sDebugInputCommand);
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (sDebugInputCommand.empty())
    {
        return GetCommand();
    }
    else
    {
        return mCommand.find(sDebugInputCommand) != mCommand.end() ? mCommand[sDebugInputCommand] : EDebugCommand::Unrecognized;
    }
}

SInstruction CInterpreter::NextInstruction(const Memory& RAM, const int iIPReg)
{
    SInstruction sInstruction;
    memcpy(&sInstruction, reinterpret_cast<const void*>((RAM + iIPReg)), iInstructionSize);
    return sInstruction;
}

void CInterpreter::GetRegsValuesFromStack(Memory& RAM, Registers& aRegisters)
{
    for (int i = 0; i < m_aCurrRegs.back(); ++i)
    {
        aRegisters.iSPReg -= 4;
        memcpy(&aRegisters.aGenPurposeRegisters[m_aCurrRegs.back() - 1 - i], reinterpret_cast<const void*>(RAM + aRegisters.iSPReg), 4);
    }
}

void CInterpreter::SetRegsValuesInStack(Memory& RAM, Registers& aRegisters, const SInstruction& sInstruction)
{
    for (int i = 0; i < sInstruction.sOperand1.iValue; ++i)
    {
        memcpy(RAM + aRegisters.iSPReg, reinterpret_cast<const void*>(&aRegisters.aGenPurposeRegisters[i]), 4);
        aRegisters.iSPReg += 4;
    }
}

bool CInterpreter::IsValidOffset(int iOffset)
{
    return (iOffset >= 0 && iOffset < m_iDataAddrOffset && (iOffset% iInstructionSize == 0));
}

void CInterpreter::Work(Registers& aRegisters, Memory& RAM, SymbolTable& aSymbolTable)
{
    //PrintTextDebugMode();
    PrintLogo();
    EDebugCommand eCommand = GetCommand();
    SetInitialState(RAM, aRegisters, aSymbolTable);

    SInstruction sInstruction = NextInstruction(RAM, aRegisters.iIPReg);;
    /*memcpy(&sInstruction, reinterpret_cast<const void*>((RAM + aRegisters.iIPReg)), iInstructionSize);*/
    while (eCommand != EDebugCommand::Exit)
    {
        if (eCommand == EDebugCommand::Unrecognized)
        {
            std::cout << "Unrecognized command: type \"help\" and see commands list !" << std::endl << std::endl;
        }
        else
        {
            switch (eCommand)
            {
            case EDebugCommand::Help:
                std::cout << std::ifstream(sHelpFilePath).rdbuf() << std::endl << std::endl;
                break;
            case EDebugCommand::Info:
                PrintCurrentInfo(aRegisters, RAM, aSymbolTable);
                break;
            case EDebugCommand::StepForward:
                Trace(sInstruction, RAM, aRegisters, aSymbolTable);
                PrintRegisters(aRegisters);
                PrintCommand(sInstruction, aSymbolTable, ECommandSpecifier::Last);

                if (MainReturned(aRegisters.iSPReg)) break;
                aRegisters.iIPReg += iInstructionSize;
                sInstruction = NextInstruction(RAM, aRegisters.iIPReg);
                PrintCommand(sInstruction , aSymbolTable, ECommandSpecifier::Next);
                break;
            case EDebugCommand::Run:
                Run(sInstruction, RAM, aRegisters, aSymbolTable);
                break;
            case EDebugCommand::Reset:
                SetInitialState(RAM, aRegisters, aSymbolTable);
                sInstruction = NextInstruction(RAM, aRegisters.iIPReg);
                break;
            case EDebugCommand::FuncAddrs:
                PrintFunctionsOffsets(aSymbolTable);
                break;
            case EDebugCommand::SetBreakpoint:
                SetBreakpoint();
                break;
            case EDebugCommand::UnsetBreakpoints:
                UnsetBreakpoints();
                break;
            case EDebugCommand::ShowBreakpoints:
                ShowBreakpoints(RAM, aSymbolTable);
                break;
            case EDebugCommand::Watch:
                Watch(RAM, aSymbolTable);
                break;
            case EDebugCommand::Print:
                PrintFromRAM(RAM, aSymbolTable);
                break;
            case EDebugCommand::Exit:
                PrintTextProgramFinished();
                continue;
                break;
            }
        }

        if (MainReturned(aRegisters.iSPReg)) break;
        eCommand = GetCommand();
    }
    PrintTextProgramFinished();
}

void CInterpreter::Trace(SInstruction& sInstruction, Memory& RAM, Registers& aRegisters, const SymbolTable& aSymbolTable)
{
    switch (sInstruction.eOpCode)
    {
    case ECommand::pushSF:
        aRegisters.iSFReg = aRegisters.iSPReg;
        memcpy(RAM + aRegisters.iSPReg, reinterpret_cast<const void*>(&aRegisters.iSPReg), 4);
        aRegisters.iSPReg += 4;
        break;
    case ECommand::popSF:
        aRegisters.iSPReg -= 4;
        memcpy(&aRegisters.iSFReg, reinterpret_cast<const void*>(RAM + aRegisters.iSPReg), 4);
        break;
    case ECommand::ret:
        memcpy(&aRegisters.iRIPReg, reinterpret_cast<const void*>(RAM + aRegisters.iSPReg - 4), 4);
        aRegisters.iSPReg -= 4;
        aRegisters.iSPReg -= sInstruction.sOperand1.iValue;
        aRegisters.iIPReg = aRegisters.iRIPReg;
        aRegisters.aGenPurposeRegisters[m_aCurrRegs.back()] = aRegisters.aGenPurposeRegisters[0];

        // reseting other registers' values
        std::fill(std::next(aRegisters.aGenPurposeRegisters.begin(), m_aCurrRegs.back() + 1), aRegisters.aGenPurposeRegisters.end(), 0);

        GetRegsValuesFromStack(RAM, aRegisters);

        m_aCurrRegs.pop_back();

        if (aRegisters.iSPReg != m_iStackAddrOffset)
        {
            memcpy(&sInstruction, reinterpret_cast<const void*>((RAM + aRegisters.iIPReg)), iInstructionSize);
        }

        break;
    case ECommand::assignData:
        switch (sInstruction.sOperand2.eOperandType)
        {
        case SOperand::EOperandType::variableType:
            memcpy(&aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue], reinterpret_cast<const void*>(&sInstruction.sOperand2.iValue), 4);
            break;
        case SOperand::EOperandType::numberType:
            aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue] = sInstruction.sOperand2.iValue;
            break;
        }
        break;
    case ECommand::assignReg:
        switch (sInstruction.sOperand2.eOperandType)
        {
        case SOperand::EOperandType::FunctionType:
            aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue] = aSymbolTable.GetFunctionOffset(sInstruction.sOperand2.iValue);
            SetRegsValuesInStack(RAM, aRegisters, sInstruction);

            // keeping that register's index which will contain result of calling function 
            m_aCurrRegs.push_back(sInstruction.sOperand1.iValue);
            break;
        }
        break;
    case ECommand::load:
        memcpy(&aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue], reinterpret_cast<const void*>(RAM + m_iDataAddrOffset + 4 * aRegisters.aGenPurposeRegisters[sInstruction.sOperand2.iValue]), 4);
        break;
    case ECommand::loadFuncArg:
        memcpy(&aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue], reinterpret_cast<const void*>(RAM + aRegisters.iSFReg + sInstruction.sOperand2.iValue), 4);
        break;
    case ECommand::multiply:
        aRegisters.CalculateAndSetFlags<std::multiplies, int>(aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue],
            aRegisters.aGenPurposeRegisters[sInstruction.sOperand2.iValue]);
        break;
    case ECommand::divide:
        aRegisters.CalculateAndSetFlags<std::divides, int>(aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue],
            aRegisters.aGenPurposeRegisters[sInstruction.sOperand2.iValue]);
        break;
    case ECommand::plus:
        aRegisters.CalculateAndSetFlags<std::plus, int>(aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue],
            aRegisters.aGenPurposeRegisters[sInstruction.sOperand2.iValue]);
        break;
    case ECommand::minus:
        aRegisters.CalculateAndSetFlags<std::minus, int>(aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue],
            aRegisters.aGenPurposeRegisters[sInstruction.sOperand2.iValue]);
        break;
    case ECommand::push:
        memcpy(RAM + aRegisters.iSPReg, reinterpret_cast<const void*>(&sInstruction.sOperand1.iValue), 4);
        aRegisters.iSPReg += 4;
        break;
    case ECommand::pop:
        aRegisters.iSPReg -= 4;
        memcpy(&aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue], reinterpret_cast<const void*>(RAM + aRegisters.iSPReg), 4);
        break;
    case ECommand::call:
        // pushing RIP addres
        memcpy(RAM + aRegisters.iSPReg, reinterpret_cast<const void*>(&aRegisters.iIPReg), 4);
        aRegisters.iSPReg += 4;

        aRegisters.iIPReg = aRegisters.aGenPurposeRegisters[sInstruction.sOperand1.iValue] - iInstructionSize;
        break;
    }
}

void CInterpreter::Run(SInstruction& sInstruction, Memory& RAM, Registers& aRegisters, const SymbolTable& aSymbolTable)
{
    while (true)
    {
        if (std::find(m_aBreakpointsList.begin(), m_aBreakpointsList.end(), aRegisters.iIPReg) != m_aBreakpointsList.end())
        {
            PrintRegisters(aRegisters);
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "\n\tHere is set breakpoint on offset " << aRegisters.iIPReg << std::endl << std::endl;
            SetConsoleTextAttribute(hConsole, 4);
            std::cout << "\t\t" << "●";
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << " " << sInstruction.GetString(aSymbolTable) << std::endl << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        Trace(sInstruction, RAM, aRegisters, aSymbolTable);
        if (MainReturned(aRegisters.iSPReg)) break;
        aRegisters.iIPReg += iInstructionSize;
        sInstruction = NextInstruction(RAM, aRegisters.iIPReg);

    } 
    PrintRegisters(aRegisters);
}

void CInterpreter::PrintCurrentInfo(Registers& aRegisters, Memory& RAM, const SymbolTable& aSymbolTable)
{
    std::cout << std::endl;
    std::cout << "\tinstruction pointer:  " << aRegisters.iIPReg << std::endl;
    std::cout << "\tStack pointer      :  " << aRegisters.iSPReg << std::endl;
    std::cout << "\tStack frame pointer:  " << aRegisters.iSFReg << std::endl;
    std::cout << "\tReturn IP          :  " << aRegisters.iRIPReg << std::endl;
    SInstruction sInstruction = NextInstruction(RAM, aRegisters.iIPReg);
    PrintCommand(sInstruction, aSymbolTable, ECommandSpecifier::Next);
    if (sInstruction.iOperandscount == 1 && sInstruction.sOperand1.eOperandType == SOperand::EOperandType::variableType)
    {
        std::cout << "\t" << aSymbolTable.GetVariableName(sInstruction.sOperand1.iValue) << " = ";
        int iValue{};
        memcpy(&iValue, reinterpret_cast<const void*>(RAM + m_iDataAddrOffset + 4 * sInstruction.sOperand1.iValue), 4);
        std::cout << iValue << ";" << std::endl << std::endl;
    }
    else if (sInstruction.iOperandscount == 2 && sInstruction.sOperand2.eOperandType == SOperand::EOperandType::variableType)
    {
        std::cout << "\t" << aSymbolTable.GetVariableName(sInstruction.sOperand2.iValue) << " = ";
        int iValue{};
        memcpy(&iValue, reinterpret_cast<const void*>(RAM + m_iDataAddrOffset + 4 * sInstruction.sOperand2.iValue), 4);
        std::cout << iValue << ";" << std::endl << std::endl;
    }
}

void CInterpreter::SetBreakpoint()
{
    std::cout << "\tSet Instr. offset : ";
    std::string sInstrOffsetInput{};
    std::getline(std::cin, sInstrOffsetInput);
    int iOffset;
    try
    {
        iOffset = std::stoi(sInstrOffsetInput);
        if (IsValidOffset(iOffset))
        {
            m_aBreakpointsList.push_back(iOffset);
            std::cout << "\tYou set breakpoint on offset: " << iOffset << std::endl << std::endl;
        }
        else throw std::exception{};
        
    }
    catch (...)
    {
        std::cout << "\tinvalid input!" << std::endl << std::endl;
    }
}

void CInterpreter::UnsetBreakpoints()
{
    m_aBreakpointsList.clear();
    std::cout << "\t\t All breakpoints have been removed succesfully!";
}

void CInterpreter::ShowBreakpoints(Memory& RAM, const SymbolTable& aSymbolTable)
{
    std::cout << std::endl;
    SInstruction sInstruction;
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < m_aBreakpointsList.size(); ++i)
    {
        memcpy(&sInstruction, reinterpret_cast<const void*>(RAM + m_aBreakpointsList[i]), iInstructionSize);
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << "\tBreakpoints" << std::endl;
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << "\toffset: ";
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << m_aBreakpointsList[i] << "\t\t";
        SetConsoleTextAttribute(hConsole, 4);
        std::cout << "●" << ' ';
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << sInstruction.GetString(aSymbolTable) << std::endl << std::endl;
        SetConsoleTextAttribute(hConsole, 15);
    }
}

void CInterpreter::SetInitialState(Memory& RAM,Registers& aRegisters, SymbolTable& aSymbolTable)
{
    std::fill(aRegisters.aGenPurposeRegisters.begin(), aRegisters.aGenPurposeRegisters.end(), 0);
    aRegisters.iIPReg = aSymbolTable.GetMainFunctionOffset();
    aRegisters.iRIPReg = 0;
    
    memcpy(RAM + m_iStackAddrOffset, reinterpret_cast<const void*>(&aRegisters.iRIPReg), 4);
    aRegisters.iSPReg = m_iStackAddrOffset + 4;
    aRegisters.iSFReg = m_iStackAddrOffset;
}

void CInterpreter::Watch(Memory& RAM, const SymbolTable& aSymbolTable)
{
    std::cout << "\n\tInsert variable name(s) to watch: ";
    std::string sInput{};
    std::getline(std::cin, sInput);
    std::cout << std::endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(sInput == "all")
    {
        for (int i = 0; i < aSymbolTable.VariablesNamesCount(); ++i)
        {
            int iVarValue{};
            memcpy(&iVarValue, reinterpret_cast<const void*>(RAM + m_iDataAddrOffset + 4 * i), 4);
            SetConsoleTextAttribute(hConsole, 14);
            std::cout << "\t" << aSymbolTable.GetVariableName(i) << " = " << iVarValue << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
    else
    {
        std::list<std::string> aVarNames{};
        std::istringstream iss(sInput);
        std::copy(std::istream_iterator<std::string>(iss)
                , std::istream_iterator<std::string>()
                , std::back_inserter(aVarNames)
        );
        
        for (auto& sVarName : aVarNames)
        {
            if (aSymbolTable.IsVariableName(sVarName))
            {
                int iVarValue{};
                memcpy(&iVarValue, reinterpret_cast<const void*>(RAM + m_iDataAddrOffset + 4 * aSymbolTable.GetVariableIndex(sVarName)), 4);
                SetConsoleTextAttribute(hConsole, 14);
                std::cout << "\t" << sVarName << " = " << iVarValue << std::endl;
                SetConsoleTextAttribute(hConsole, 15);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 4);
                std::cout << "\t" << sVarName << " isn't a variable name!" << std::endl;
                SetConsoleTextAttribute(hConsole, 15);
            }
        }
    }
    
    std::cout << std::endl;
}

void CInterpreter::PrintFromRAM(Memory& RAM, const SymbolTable& aSymbolTable)
{
    std::cout << "input segment name(data or code): ";
    std::string sInput;
    std::getline(std::cin, sInput);
    if (sInput == "data")
    {
        std::cout << "\n\tDATA.\n";
        for (int i = 0; i < aSymbolTable.VariablesNamesCount(); ++i)
        {
            int iVarValue{};
            memcpy(&iVarValue, reinterpret_cast<const void*>(RAM + m_iDataAddrOffset + 4 * i), 4);
            std::cout << "\t\t" << aSymbolTable.GetVariableName(i) << " = " << iVarValue << std::endl;
        }
    }
    else if (sInput == "code")
    {
        std::cout << "\n\tCODE.\n";

        int iInstructionOffset{};
        SInstruction sInstruction;
        for (int i = 0; i < aSymbolTable.FunctionsCount(); ++i)
        {
            std::cout << "\n\t" << aSymbolTable.GetFunctionName(i) << "():" << std::endl;
            while (sInstruction.eOpCode != ECommand::ret)
            {
                sInstruction = NextInstruction(RAM, iInstructionOffset);
                std::cout << "\t\t" << sInstruction.GetString(aSymbolTable) << std::endl;
                iInstructionOffset += iInstructionSize;
            }
            sInstruction = NextInstruction(RAM, iInstructionOffset);
        }
    }
    else
    {
        std::cout << "\tinvalid input!\n\n";
    }
}

inline bool CInterpreter::MainReturned(const int iSPReg)
{
    return (iSPReg == m_iStackAddrOffset);
}
