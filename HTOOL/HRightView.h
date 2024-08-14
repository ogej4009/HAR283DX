#pragma once
#include <HGAMESTRING.h>
#include <list>


// HRightView 폼 보기

class HRightView : public CFormView
{
	DECLARE_DYNCREATE(HRightView)


protected:
	HRightView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~HRightView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HRightView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedMeshbtn();


// public:
	// unsigned __stdcall MeshLoadThread(void* _Arg);

	static HRightView* View;
	static std::list<HGAMESTRING> FbxLoadingData;
	CListBox m_FbxList;

public:
	void PushFbxList();
	afx_msg void OnLbnSelchangeFbx();
	afx_msg void OnBnClickedFbxobjectcreate();
	afx_msg void OnBnClickedAniplaybtn();




	int m_StartFrame;
	int m_EndFrame;
	int m_CurFrame;
	afx_msg void OnEnChangeStartframe();
	afx_msg void OnEnChangeCurframe();
	afx_msg void OnEnChangeEndframe();


public:
	void CurFrame(int _Frame);
	void RangeSetting(int _StartFrame, int _EndFrame);
	afx_msg void OnNMCustomdrawPlayslider(NMHDR* pNMHDR, LRESULT* pResult);
	CButton m_PlayBtn;
	CSliderCtrl m_PlaySlider;

public:
	void StartFbxListCheck();
};


