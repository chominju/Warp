#pragma once


// CMeshTool ��ȭ �����Դϴ�.

class CMeshTool : public CDialogEx
{
	DECLARE_DYNAMIC(CMeshTool)

public:
	CMeshTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMeshTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
