#pragma once


// CColliderTab ��ȭ �����Դϴ�.

class CColliderTab : public CDialogEx
{
	DECLARE_DYNAMIC(CColliderTab)

public:
	CColliderTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CColliderTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
};
