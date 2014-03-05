/////////////////////////////////////////////////////////////////////////////
// SampleRhinoDockbarDialog.cpp
//

#include "stdafx.h"
#include "SampleRhinoDockbarDialog.h"
#include "SampleDockbarPlugIn.h"

// CSampleRhinoDockbarDialog

IMPLEMENT_SERIAL( CSampleRhinoDockbarDialog, CRhinoUiDockBarDialog, 1)

CSampleRhinoDockbarDialog::CSampleRhinoDockbarDialog(CWnd* pParent /*=NULL*/)
	: CRhinoUiDockBarDialog(CSampleRhinoDockbarDialog::IDD, pParent)
{
}

CSampleRhinoDockbarDialog::~CSampleRhinoDockbarDialog()
{
}

void CSampleRhinoDockbarDialog::DoDataExchange(CDataExchange* pDX)
{
	CRhinoUiDockBarDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSampleRhinoDockbarDialog, CRhinoUiDockBarDialog)
  ON_BN_CLICKED(IDC_BUTTON1, &CSampleRhinoDockbarDialog::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL CSampleRhinoDockbarDialog::OnInitDialog() 
{
	CRhinoUiDockBarDialog::OnInitDialog();
	
  // TODO...

	return TRUE;
}

void CSampleRhinoDockbarDialog::OnBnClickedButton1()
{
  MessageBox( L"Hello Rhino!", SampleDockbarPlugIn().PlugInName(), MB_OK );
}
