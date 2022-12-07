
#include "outputconsole.h"

namespace pwpt
{

void COutputStream::Draw(IObject_SPtr pObject)
{
	auto oGeom = pObject->GetGeometry();
	*m_pStream << "(" << oGeom.first.x() << "," << oGeom.first.y() << ")";

	*m_pStream << " ";

	*m_pStream << pObject->GetColor().name().toStdString();
}

} // namespace pwpt
