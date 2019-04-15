#pragma once


// CREGISTERDlg dialog

class CREGISTERDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CREGISTERDlg)

public:
	CREGISTERDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CREGISTERDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTERUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegisternow();
};
