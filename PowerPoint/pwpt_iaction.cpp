
#include "errorhandling.h"
#include "pwpt_iaction.h"

namespace pwpt
{

	void IAction::SetDocument(PwPtDoc_SPtr& pDoc)
	{
		m_pDoc = pDoc;
	}

	void IAction::CheckDocumentValidity() const
	{
		if (m_pDoc == nullptr)
			throw CError{ "There is no document to work with..." };
	}

} // namespace pwpt
