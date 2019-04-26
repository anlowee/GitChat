#pragma once

// CCHATDlg dialog
#include <string>

class CCHATDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCHATDlg)

public:
	CCHATDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCHATDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSend();
	CString AddRecord(CString, CString);
	std::string AddRecord(std::string strUsername, std::string  strMessageInput);
	// Using to indicate new records
	void IndicateRecord(CString);
};
