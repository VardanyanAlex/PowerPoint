
#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <vector>
#include <string>

class SymbolTable
{
public:

	void		InsertVariableName(const std::string&);
	std::string GetVariableName(const size_t Index) const;

	void		InsertFunctionInfo(const std::string&, size_t NumberOfArgs, bool bIsDefined);
	std::string GetFunctionName(const size_t Index) const;
	int			GetFunctionArgsCount(const size_t Index) const;

	void		PopVariableName();
	void		PopFunctionName();

	std::string VariableNameBack() const;
	std::string FunctionNameBack() const;

	size_t		VariablesNamesCount() const;
	size_t		FunctionNamesCount() const;
	size_t		FunctionsCount() const;

	bool		isDefinedVariable(const std::string& sIdtfName);
	bool		isDeclaredFunction(const std::string& sIdtfName);
	bool		isDefinedFunction(int idx) const ;

	size_t		GetVariableIdtfIdx(const std::string&) const;
	size_t		GetFunctionIdtfIdx(const std::string&) const;

	void		ResetFuncArgNamesCount(const int iFuncIdx);

	int			GetMainFunctionOffset();
	int			GetFunctionOffset(int iFuncIdtx) const noexcept;

	void		SetFuncOffset(int iFuncSize);

	bool		IsVariableName(const std::string& sIdtfName) const;
	int			GetVariableIndex(const std::string& sIdtfName) const;

protected:
	int			m_iFuncOffset{};

private:
	std::vector<std::string> m_aVariablesTable;
	std::vector<std::string> m_aFunctionsTable;
	std::vector<int> m_aExistingFunctions;

	// Functions' offsets in code segment
	std::vector<int> m_aFunctionsOffsets;

	std::vector<size_t> m_aFunctionArgsCount;
};

class CMainFuncDetectionException : public std::exception
{
public:
	const char* what() const throw() override
	{
		return "\tExcpetion thrown: Can't find main() function \n";
	}
};

#endif // SYMBOLTABLE_HPP
