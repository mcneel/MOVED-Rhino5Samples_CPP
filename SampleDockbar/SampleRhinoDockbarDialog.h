/////////////////////////////////////////////////////////////////////////////
// SampleRhinoDockbarDialog.h
//

#pragma once

#include "Resource.h"

// CSampleRhinoDockbarDialog

class CSampleRhinoDockbarDialog : public CRhinoUiDockBarDialog
{
	DECLARE_SERIAL( CSampleRhinoDockbarDialog )

public:
	CSampleRhinoDockbarDialog( CWnd* pParent = NULL );
	virtual ~CSampleRhinoDockbarDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
  virtual BOOL OnInitDialog();
	virtual void DoDataExchange( CDataExchange* pDX );
  afx_msg void OnBnClickedButton1();
	DECLARE_MESSAGE_MAP()
};
