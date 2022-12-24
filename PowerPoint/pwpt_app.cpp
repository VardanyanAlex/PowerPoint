
#include "pwpt_app.h"

namespace pwpt
{

namespace App
{

PwPtDoc_SPtr CApp::GetDocument() const
{
	return m_pDocument;
}

std::ostream* CApp::GetOutputStreamDevice() const
{
	return m_pOutputStream;
}

} // namespace App

} // namespace pwpt
