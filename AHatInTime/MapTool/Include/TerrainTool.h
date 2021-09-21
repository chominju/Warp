#pragma once
#include "afxwin.h"
#include "Engine_Define.h"

// CTerrainTool ��ȭ �����Դϴ�.

class CTerrainTool : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainTool)

public:
	CTerrainTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTerrainTool();

	BYTE m_drawID;
	_tchar* m_objectKey;
	_tchar* m_stateKey;
	vector<CString> m_textureName;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox m_textureListBox;
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	CStatic m_pictureControl;
};
