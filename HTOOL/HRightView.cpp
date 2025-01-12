﻿// HRightView.cpp: 구현 파일
//

#include "pch.h"
#include "HTOOL.h"
#include "HRightView.h"
#include <HGAMESCENE.h>
#include "HTOOLMAPSCENE.h"
#include <HFBX.h>
#include <HBoneAnimationCom.h>


// HRightView.cpp: 구현 파일
HRightView* HRightView::View;
std::list<HGAMESTRING> HRightView::FbxLoadingData;
// HRightView

IMPLEMENT_DYNCREATE(HRightView, CFormView)

HRightView::HRightView()
	: CFormView(IDD_HRightView)
	, m_StartFrame(0)
	, m_EndFrame(0)
	, m_CurFrame(0)
{

}

HRightView::~HRightView()
{
}

void HRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FBX, m_FbxList);
	DDX_Text(pDX, IDC_STARTFRAME, m_StartFrame);
	DDX_Text(pDX, IDC_ENDFRAME, m_EndFrame);
	DDX_Text(pDX, IDC_CURFRAME, m_CurFrame);
	DDX_Control(pDX, IDC_ANIPLAYBTN, m_PlayBtn);
	DDX_Control(pDX, IDC_PLAYSLIDER, m_PlaySlider);
}

BEGIN_MESSAGE_MAP(HRightView, CFormView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_MESHBTN, &HRightView::OnBnClickedMeshbtn)
	ON_LBN_SELCHANGE(IDC_FBX, &HRightView::OnLbnSelchangeFbx)
	ON_BN_CLICKED(IDC_FBXOBJECTCREATE, &HRightView::OnBnClickedFbxobjectcreate)
	ON_BN_CLICKED(IDC_ANIPLAYBTN, &HRightView::OnBnClickedAniplaybtn)
	ON_EN_CHANGE(IDC_STARTFRAME, &HRightView::OnEnChangeStartframe)
	ON_EN_CHANGE(IDC_CURFRAME, &HRightView::OnEnChangeCurframe)
	ON_EN_CHANGE(IDC_ENDFRAME, &HRightView::OnEnChangeEndframe)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PLAYSLIDER, &HRightView::OnNMCustomdrawPlayslider)
END_MESSAGE_MAP()


// HRightView 진단

#ifdef _DEBUG
void HRightView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void HRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// HRightView 메시지 처리기


int HRightView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;


	HGAMESCENE::Create<HTOOLMAPSCENE>(L"MAPSCENE");
	HGAMESCENE::ChangeScene(L"MAPSCENE");


	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	View = this;
	return 0;
}

//thread_local HGAMESTRING LoadPath;
//thread_local HGAMESTRING FilePath;

struct ThreadLoadData
{
	HGAMESTRING LoadPath;
	HGAMESTRING FilePath;
	HRightView* View;
};

// 전역함수나 정적함수에만 지정해 줄수 있다.
unsigned __stdcall MeshLoadThread(void* _Arg)
{
	ThreadLoadData* Data = (ThreadLoadData*)_Arg;

	HPTR<HSAMPLER> SP = HSAMPLER::Find(L"LWSMP");
	HGAMEDEVICE::MAINOBJ()->Context()->PSSetSamplers(0, 0, &SP->m_State);

	HGAMESTRING FileName = Data->FilePath;
	FileName.ChangeStr(L".FBX", L".HFBX");
	HGAMESTRING CheckPath = Data->LoadPath;
	CheckPath.ChangeStr(L".FBX", L".HFBX");

	{
		if (false == HGAMEPATH::IsExits(CheckPath))
		{
			HGAMEFILE NewFile;
			// 애니메이션을 빠르게 돌리게 하기 위해서
			// 내부에서 134 * 1434 회의 연산을 미리 다 해 놓는다.
			NewFile.SetPath(Data->LoadPath);
			HPTR<HFBX> PTR = HFBX::Load(NewFile);
			PTR->SaveUserFormat(CheckPath);
		}
		else
		{
			HGAMEFILE NewFile;
			// 애니메이션을 빠르게 돌리게 하기 위해서
			// 내부에서 134 * 1434 회의 연산을 미리 다 해 놓는다.
			NewFile.SetPath(Data->LoadPath);
			HFBX::LoadToUserFormat(NewFile, CheckPath);
		}
	}

	FileName.ChangeStr(L".HFBX", L".FBX");


	std::wcout << Data->LoadPath << L" Load End" << std::endl;

	HRightView::FbxLoadingData.push_back(FileName);

	// Data->View->PushFbxList(FileName);

	delete Data;

	//MeshCreateData NewDataData;

	//Data.m_MeshName = Data->FilePath;
	//Data.m_TakeName = L"Take 001";
	//Data.m_Pos = {0, 0, 0};
	//Data.m_Rot = { 0, -90, 0 };
	//Data.m_Scale = { 0.1f, 0.1f, 0.1f };

	//HTOOLMAPSCENE::NewMeshData.push_back(Data);

	return 0;
}

#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

void HRightView::OnBnClickedMeshbtn()
{
	// int Buffer[1000];
	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);

	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	HGAMEDIRECTORY Dic;
	Dic.MoveParent(L"HAR283DX");
	Dic.Move(L"RES");
	Dic.Move(L"MESH");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFile = p;
	ofn.Flags |= OFN_ALLOWMULTISELECT;
	ofn.lpstrInitialDir = Dic.PCONSTWCHAR();
	ofn.lpstrFilter = L"FBX Files(*.FBX)\0*.FBX\0)";

	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	dlgFile.DoModal();
	fileName.ReleaseBuffer();

	CString FileName = dlgFile.GetFileName();

	ThreadLoadData* Data = new ThreadLoadData();

	Data->FilePath = FileName;

	//OPENFILENAME ofn;       // common dialog box structure
	//char szFile[MAX_PATH] = "";  // buffer for file name
	//ZeroMemory(&ofn, sizeof(OPENFILENAME));
	//ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = NULL;
	//ofn.lpstrFile = szFile;
	//ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = _T("Avi Files(*.avi)\0*.avi\0All Files (*.*)\0*.*\0");
	//ofn.nFilterIndex = 1;
	//ofn.lpstrFileTitle = NULL;
	//ofn.nMaxFileTitle = 0;
	//ofn.lpstrInitialDir = NULL;
	//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	//if (::GetOpenFileName(&ofn) == false) return 0;

	Data->LoadPath = Dic.PlusFileName(FileName.GetString());
	Data->View = this;


	_beginthreadex(nullptr, 0, &MeshLoadThread, Data, 0, nullptr);


	// 이 구조체 안에 내가 선택한 파일네임이 담겨져 있다.
	// ofn

	//wchar_t* pBufEnd = p + FILE_LIST_BUFFER_SIZE - 2;
	//wchar_t* start = p;
	//while ((p < pBufEnd) && (*p))
	//	p++;

	//if (p > start)
	//{
	//	_tprintf(_T("Path to folder where files were selected:  %s\r\n\r\n"), start);
	//	p++;

	//	int fileCount = 1;
	//	while ((p < pBufEnd) && (*p))
	//	{
	//		start = p;
	//		while ((p < pBufEnd) && (*p))
	//			p++;
	//		if (p > start)
	//			_tprintf(_T("%2d. %s\r\n"), fileCount, start);
	//		p++;
	//		fileCount++;
	//	}
	//}

	// 
}

void HRightView::PushFbxList()
{
	if (0 == FbxLoadingData.size())
	{
		return;
	}

	UpdateData(TRUE);
	for (auto& FbxName : FbxLoadingData)
	{
		m_FbxList.AddString(FbxName);
	}

	FbxLoadingData.clear();
	UpdateData(FALSE);
}


void HRightView::OnLbnSelchangeFbx()
{
	int a = 0;
}


void HRightView::OnBnClickedFbxobjectcreate()
{
	UpdateData(TRUE);
	int Test = m_FbxList.GetCurSel();

	if (-1 == Test)
	{
		return;
	}

	MeshCreateData Data;

	CString FbxName;

	m_FbxList.GetText(Test, FbxName);

	Data.m_MeshName = FbxName;
	Data.m_TakeName = L"Take 001";
	HTOOLMAPSCENE::Inst->CreateFBXObject(Data);


	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void HRightView::OnBnClickedAniplaybtn()
{
	if (nullptr == HTOOLMAPSCENE::AniCom)
	{
		return;
	}




	CString Text;
	m_PlayBtn.GetWindowTextW(Text);
	if (Text == L"다시 재생")
	{
		UpdateData(TRUE);
		HTOOLMAPSCENE::AniCom->CurAni()->Reset();
		HTOOLMAPSCENE::AniCom->Play();
		m_PlayBtn.SetWindowTextW(L"정지");
		UpdateData(FALSE);
		return;
	}



	if (true == HTOOLMAPSCENE::AniCom->IsPlay())
	{
		UpdateData(TRUE);
		m_PlayBtn.SetWindowTextW(L"재생");
		HTOOLMAPSCENE::AniCom->Stop();
		UpdateData(FALSE);
	}
	else 
	{
		UpdateData(TRUE);
		m_PlayBtn.SetWindowTextW(L"정지");
		HTOOLMAPSCENE::AniCom->Play();
		UpdateData(FALSE);
	}



	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void HRightView::OnEnChangeStartframe()
{
	if (nullptr == HTOOLMAPSCENE::AniCom)
	{
		return;
	}

	UpdateData(TRUE);
	HTOOLMAPSCENE::AniCom->CurAni()->SetStartFrame(m_StartFrame);

	if (m_StartFrame > m_EndFrame)
	{
		m_StartFrame = HTOOLMAPSCENE::AniCom->CurAni()->m_Start;
		m_EndFrame = HTOOLMAPSCENE::AniCom->CurAni()->m_End;
		UpdateData(FALSE);
		return;
	}

	m_PlaySlider.SetRange(m_StartFrame, m_EndFrame);
	UpdateData(FALSE);
}


void HRightView::OnEnChangeCurframe()
{

}


void HRightView::OnEnChangeEndframe()
{
	if (nullptr == HTOOLMAPSCENE::AniCom)
	{
		return;
	}

	UpdateData(TRUE);
	HTOOLMAPSCENE::AniCom->CurAni()->SetEndFrame(m_EndFrame);

	if (m_EndFrame < m_StartFrame)
	{
		UpdateData(FALSE);
		return;
	}

	m_PlaySlider.SetRangeMax(m_EndFrame);
	UpdateData(FALSE);
}


void HRightView::CurFrame(int _Frame)
{
	UpdateData(TRUE);
	m_CurFrame = _Frame;
	m_PlaySlider.SetPos(m_CurFrame);
	UpdateData(FALSE);
}

void HRightView::RangeSetting(int _StartFrame, int _EndFrame)
{
	UpdateData(TRUE);
	m_StartFrame = _StartFrame;
	m_EndFrame = _EndFrame;
	m_PlaySlider.SetRange(m_StartFrame, m_EndFrame);
	UpdateData(FALSE);
}

void HRightView::OnNMCustomdrawPlayslider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;

	if (nullptr == HTOOLMAPSCENE::AniCom)
	{
		return;
	}

	if (false == HTOOLMAPSCENE::AniCom->IsPlay())
	{
		m_PlaySlider.SetPos(m_PlaySlider.GetPos());
		HTOOLMAPSCENE::AniCom->SetCurFrame(m_PlaySlider.GetPos());
	}
}





void HRightView::StartFbxListCheck() 
{

	{
		// NewFile.SetPath(Data->LoadPath);
		// HFBX::LoadToUserFormat(NewFile, CheckPath);


		HGAMEDIRECTORY Dic;

		Dic.MoveParent(L"HAR283DX");
		Dic.Move(L"RES");
		Dic.Move(L"MESH");

		auto FileList = Dic.DirAllFile(L"HFBX");
		for (auto& _File : FileList)
		{

			HGAMESTRING FILENAME = _File.FileName();
			FILENAME.ChangeStr(L".HFBX", L".FBX");

			HGAMESTRING FullPath = _File.FullPath();
			FullPath.ChangeStr(L".HFBX", L".FBX");
			HGAMEFILE FbxFile = FullPath;

			HFBX::LoadToUserFormat(FbxFile, _File.FullPath());

			m_FbxList.AddString(FILENAME);
		}
	}

}