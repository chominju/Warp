#pragma once


// CColliderTab 대화 상자입니다.

class CColliderTab : public CDialogEx
{
	DECLARE_DYNAMIC(CColliderTab)

public:
	CColliderTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CColliderTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
};
