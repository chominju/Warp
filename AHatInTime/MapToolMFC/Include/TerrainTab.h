#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTerrainTab 대화 상자입니다.

class CTerrain;

class CTerrainTab : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainTab)

public:
	CTerrainTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTerrainTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_textureListBox;
	CListBox m_addTextureList;
	CStatic m_pictureControl;


	BYTE m_textureListIndex;
	BYTE m_addListIndex;

	CGraphicDev*			m_pDeviceClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev; 
	CSpriteDev * m_spriteDev;

	vector<CString> m_textureNameVector;
	vector<CTerrain*> m_addTextureVector;
	vector<int> m_addTextrueIndexVector;

	CManagement*			m_pManagementClass;

	afx_msg void OnLbnSelchangeList1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	float m_posX;
	float m_posY;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
	int m_countX;
	int m_countZ;

	void CreateTerrain();
	afx_msg void OnLbnSelchangeListAdd();
	afx_msg void OnBnClickedButtonApply();
	int m_posZ;
	CTreeCtrl m_tree;
	void InitTreeCtrl();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
};
