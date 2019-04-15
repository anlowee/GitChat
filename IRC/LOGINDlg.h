#pragma once


// CLOGINDlg dialog

class CLOGINDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLOGINDlg)

public:
	CLOGINDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CLOGINDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetin();
};
