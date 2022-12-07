

#include <cassert>
#include <string>
#include <vector>

#include "SymbolTable.hpp"

void SymbolTable::InsertVariableName(const std::string& sVariableName)
{
	m_aVariablesTable.push_back(sVariableName);
}

std::string SymbolTable::GetVariableName(const size_t Index) const
{
	return m_aVariablesTable[Index];
}

void SymbolTable::InsertFunctionInfo(const std::string& sFunctionName, size_t NumberOfArgs, bool bIsDefined)
{
	if (isDeclaredFunction(sFunctionName))
	{
		int iFuncIdx = GetFunctionIdtfIdx(sFunctionName);
		m_aFunctionArgsCount[iFuncIdx] = NumberOfArgs;
		m_aExistingFunctions[iFuncIdx] = bIsDefined;
	}
	else
	{
		m_aFunctionsTable.push_back(sFunctionName);
		m_aFunctionArgsCount.push_back(NumberOfArgs);
		m_aExistingFunctions.push_back(bIsDefined);
	}
}

std::string SymbolTable::GetFunctionName(const size_t Index) const
{
	return m_aFunctionsTable[Index];
}

int SymbolTable::GetFunctionArgsCount(const size_t Index) const
{
	return m_aFunctionArgsCount[Index];
}


void SymbolTable::PopVariableName()
{
	m_aVariablesTable.pop_back();
}

void SymbolTable::PopFunctionName()
{
	m_aFunctionsTable.pop_back();
}

size_t SymbolTable::VariablesNamesCount() const
{
	return m_aVariablesTable.size();
}

size_t SymbolTable::FunctionNamesCount() const
{
	return m_aFunctionsTable.size();
}

size_t SymbolTable::FunctionsCount() const
{
	return m_aFunctionsOffsets.size();
}

std::string SymbolTable::VariableNameBack() const
{
	return m_aVariablesTable.back();
}

std::string SymbolTable::FunctionNameBack() const
{
	return m_aFunctionsTable.back();
}

bool SymbolTable::isDefinedVariable(const std::string& sIdtfName)
{
	return (m_aVariablesTable.size() > 0 && std::find(m_aVariablesTable.begin(), m_aVariablesTable.end() - 1, sIdtfName) != m_aVariablesTable.end() - 1);
}

bool SymbolTable::isDeclaredFunction(const std::string& sIdtfName)
{
	return (std::find(m_aFunctionsTable.begin(), m_aFunctionsTable.end(), sIdtfName) != m_aFunctionsTable.end());
}

bool SymbolTable::isDefinedFunction(int idx) const
{
	return m_aExistingFunctions[idx];
}

size_t SymbolTable::GetVariableIdtfIdx(const std::string& sName) const
{
	return std::distance(m_aVariablesTable.begin(), std::find(m_aVariablesTable.begin(), m_aVariablesTable.end() - 1, sName) );
}

size_t SymbolTable::GetFunctionIdtfIdx(const std::string& sName) const
{
	return std::distance(m_aFunctionsTable.begin(), std::find(m_aFunctionsTable.begin(), m_aFunctionsTable.end(), sName));
}

void SymbolTable::ResetFuncArgNamesCount(const int iFuncIdx)
{
	m_aExistingFunctions[iFuncIdx] = 0;
}

int SymbolTable::GetMainFunctionOffset()
{
	auto itMainFunc = std::find(m_aFunctionsTable.begin(), m_aFunctionsTable.end(), "main");
	if (itMainFunc == m_aFunctionsTable.end())
	{
		throw CMainFuncDetectionException{};
	}

	return m_aFunctionsOffsets[std::distance(m_aFunctionsTable.begin(), itMainFunc)];
}

int SymbolTable::GetFunctionOffset(int iFuncIdtx) const noexcept
{
	assert(iFuncIdtx < m_aFunctionsOffsets.size());
	return m_aFunctionsOffsets[iFuncIdtx];
}

void SymbolTable::SetFuncOffset(int iFuncSize)
{
	m_aFunctionsOffsets.push_back(m_iFuncOffset);
	m_iFuncOffset += iFuncSize;
}

bool SymbolTable::IsVariableName(const std::string& sIdtfName) const
{
	return std::find(m_aVariablesTable.begin(), m_aVariablesTable.end(), sIdtfName) != m_aVariablesTable.end();
}

int SymbolTable::GetVariableIndex(const std::string& sIdtfName) const
{
	if (IsVariableName(sIdtfName))
	{
		return std::distance(m_aVariablesTable.begin(), std::find(m_aVariablesTable.begin(), m_aVariablesTable.end(), sIdtfName));
	}
	
	return -1;
}
