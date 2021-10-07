
// MapToolMFCView.h : CMapToolMFCView 클래스의 인터페이스
//

#pragma once

class CDynamicCamera;
class CTerrain;
class CStage;

class CMapToolMFCDoc;
class CMapToolMFCView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMapToolMFCView();
	DECLARE_DYNCREATE(CMapToolMFCView)

// 특성입니다.
public:
	CMapToolMFCDoc* GetDocument() const;

// 작업입니다.
public:
	bool m_isUpdate;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC = nullptr);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
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

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);


	void Render_View();
};

#ifndef _DEBUG  // MapToolMFCView.cpp의 디버그 버전
inline CMapToolMFCDoc* CMapToolMFCView::GetDocument() const
   { return reinterpret_cast<CMapToolMFCDoc*>(m_pDocument); }
#endif

