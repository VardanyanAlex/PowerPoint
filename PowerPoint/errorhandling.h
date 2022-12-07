
#ifndef _POWERPOINT_ERRORS_HANDLING_HPP_
#define _POWERPOINT_ERRORS_HANDLING_HPP_

#include <exception>
#include <string>

class CError : public std::exception
{
public:
	CError(std::string const& sErrorMsg = "Unknown error occurred");

	char const* what() const override;

private:
	std::string m_sErrorMsg;
};

#endif // !_POWERPOINT_ERRORS_HANDLING_HPP_
