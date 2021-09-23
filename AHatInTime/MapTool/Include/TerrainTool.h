#pragma once
#include "afxwin.h"
#include "Engine_Define.h"

// CTerrainTool ��ȭ �����Դϴ�.

class CTerrain;

class CTerrainTool : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainTool)

public:
	CTerrainTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTerrainTool();

	BYTE m_drawID;
	_tchar* m_objectKey;
	_tchar* m_stateKey;

	BYTE m_textureListIndex;
	BYTE m_addListIndex;


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
	CListBox m_addList;



	CGraphicDev*			m_pDeviceClass;// = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphicDev;// = nullptr;


	vector<CString> m_textureNameVector;
	vector<CTerrain*> m_addTextureVector;
	vector<CTerrainTex*> m_textureTexVector;


	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();

	float m_posX;
	float m_posY;
	float m_rotX;
	float m_rotY;
	float m_rotZ;
	float m_countX;
	float m_countZ;
	float m_posZ;
};
