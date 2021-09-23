
// MapToolView.h : CMapToolView Ŭ������ �������̽�
//

#pragma once

class CMapToolDoc;
class CDynamicCamera;
class CTerrain;
class CStage;

class CMapToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMapToolView();
	DECLARE_DYNCREATE(CMapToolView)

// Ư���Դϴ�.
public:
	CMapToolDoc* GetDocument() const;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);


public:
	map<const _tchar*, CLayer*>		m_mapLayer;
	CDynamicCamera* m_pCamera;
	CTerrain*		m_pTerrain;
	CStage* m_pScene;
	CManagement*			m_pManagementClass;

	CGraphicDev*			m_pDeviceClass;// = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphicDev;// = nullptr;
};

#ifndef _DEBUG  // MapToolView.cpp�� ����� ����
inline CMapToolDoc* CMapToolView::GetDocument() const
   { return reinterpret_cast<CMapToolDoc*>(m_pDocument); }
#endif
