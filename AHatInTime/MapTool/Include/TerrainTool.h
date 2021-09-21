#pragma once
#include "afxwin.h"
#include "Engine_Define.h"

// CTerrainTool 대화 상자입니다.

class CTerrainTool : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainTool)

public:
	CTerrainTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTerrainTool();

	BYTE m_drawID;
	_tchar* m_objectKey;
	_tchar* m_stateKey;
	vector<CString> m_textureName;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox m_textureListBox;
	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	CStatic m_pictureControl;
};
