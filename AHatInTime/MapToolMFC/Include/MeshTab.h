#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMeshTab 대화 상자입니다.

class CMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CMeshTab)

public:
	CMeshTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMeshTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	BYTE m_meshListIndex;
	BYTE m_addMeshListIndex;

	CGraphicDev*			m_pDeviceClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	CSpriteDev * m_spriteDev;

	vector<CString> m_meshNameVector;
	vector<int> m_meshIndexVector;
	//vector<CTerrain*> m_addMeshVector;

	CManagement*			m_pManagementClass;

	CListBox m_meshList;
	CListBox m_addMeshList;
	float m_posX;
	float m_posY;
	float m_posZ;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnLbnSelchangeListAdd();
	CTreeCtrl m_tree;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	void InitTreeCtrl();
};
