
// MapToolMFCView.h : CMapToolMFCView Ŭ������ �������̽�
//

#pragma once

class CDynamicCamera;
class CTerrain;
class CStage;

class CMapToolMFCDoc;
class CMapToolMFCView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMapToolMFCView();
	DECLARE_DYNCREATE(CMapToolMFCView)

// Ư���Դϴ�.
public:
	CMapToolMFCDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	bool m_isUpdate;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC = nullptr);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMapToolMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;


	map<const _tchar*, CLayer*>		m_mapLayer;
	CDynamicCamera* m_pCamera;
	CTerrain*		m_pTerrain;
	CStage* m_pScene;
	CManagement*			m_pManagementClass;

	CGraphicDev*			m_pDeviceClass;
	LPDIRECT3DDEVICE9		m_pGraphicDev;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);


	void Render_View();
};

#ifndef _DEBUG  // MapToolMFCView.cpp�� ����� ����
inline CMapToolMFCDoc* CMapToolMFCView::GetDocument() const
   { return reinterpret_cast<CMapToolMFCDoc*>(m_pDocument); }
#endif

