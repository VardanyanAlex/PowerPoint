
#ifndef _POWERPOINT_OBJECT_SHAPE_HPP_
#define _POWERPOINT_OBJECT_SHAPE_HPP_

#include <string>

namespace pwpt
{

class CShape
{
public:
	enum class EShape
	{
		None,

		Line,
		Rectangle,
		Triangle,
		Circular,
		TextBox
	};

	explicit CShape(EShape);
	CShape(std::string const&);

	std::string ToString() const;

	EShape GetShape() const;

	void SetShape(EShape);
	void SetShape(std::string const&);

private:
	EShape m_eShape;
	std::string m_sShape;
};

} // namespace pwpt

#endif // _POWERPOINT_OBJECT_SHAPE_HPP_
