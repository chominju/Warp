#pragma once


// CNaviMeshTab ��ȭ �����Դϴ�.

class CNaviMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CNaviMeshTab)

public:
	CNaviMeshTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNaviMeshTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
