#include "HGAMESCENE.h"
#include "HGAMEACTOR.h"
#include "HGAMEDEVICE.h"
#include "HTRANS.h"
#include "HCAM.h"
#include "HRENDERER.h"
#include "HCOL.h"
#include "H3DDEBUG.h"
#include <HGAMEINPUT.h>
#include <HGAMETIME.h>
#include <HGAMEMOVIE.h>
#include "HRenderTarget.h"
#include "HLight.h"

HPTR<HGAMESCENE> HGAMESCENE::m_CurScene = nullptr;
HPTR<HGAMESCENE> HGAMESCENE::m_NextScene = nullptr;

HGAMESCENE::HGAMESCENE() {

}
HGAMESCENE::~HGAMESCENE() {

}

void HGAMESCENE::ChangeScene(const HGAMESTRING& _Name) 
{
	m_NextScene = Find(_Name);

	if (nullptr == m_NextScene)
	{
		AMSG(L"�������� �ʴ� ���� ü���� �Ϸ��� �߽��ϴ�.");
	}

}

HPTR<HGAMEACTOR> HGAMESCENE::CreateActor(const HGAMESTRING& _Name) 
{
	// HUPDATELISTOBJMGR<HGAMEACTOR>::m_ObjList

	HPTR<HGAMEACTOR> Actor = HUPDATELISTOBJMGR<HGAMEACTOR>::CreateObj<HGAMEACTOR>(_Name);
	// �̰� ����־��ִϱ� ���ʹ� ��ġ�� �����ϰ� �ȴ�.
	// ������Ʈ ���������� ��ġ��� �͵� ���(������Ʈ)�̴�.
	// ���� �˰������ �װ� ������ �������� ���� �Ҽ� �ִ�.
	Actor->m_SCENE = this;
	Actor->CreateCom<HTRANS>();
	return Actor;
}

void HGAMESCENE::Progress() 
{
	if (nullptr != m_NextScene)
	{
		// ����
		if (nullptr == m_CurScene)
		{
			m_CurScene = m_NextScene;
			m_CurScene->SceneChangeStart();
			m_NextScene = nullptr;
			HGAMETIME::TimeReset();
		}
		else 
		{
			m_CurScene->SceneChangeEnd();
			m_CurScene = m_NextScene;
			m_CurScene->SceneChangeStart();
			m_NextScene = nullptr;
			HGAMETIME::TimeReset();
		}
	}

	HGAMEINPUT::Update();
	HGAMETIME::Update();

	m_CurScene->UpdatePrev();
	m_CurScene->Update();
	m_CurScene->UpdateNext();

	m_CurScene->RenderPrev();

	m_CurScene->Render();
	m_CurScene->RenderNext();


	m_CurScene->CollisionPrev();
	m_CurScene->Collision();
	// �ݸ���
	m_CurScene->CollisionNext();

	m_CurScene->Release();
}

bool HGAMESCENE::ZSORT(HPTR<HRENDERER>& _Left, HPTR<HRENDERER>& _Right)
{
	HVECTOR LeftZ = _Left->WPOS();
	HVECTOR RightZ = _Right->WPOS();

	// �������� Ʈ�������� ��ӹ��� ����
	return _Left->WPOS().z > _Right->WPOS().z;
}


void HGAMESCENE::Collision() 
{
	// ������������ �浹�ؾ� �ϴ°�?
	// std::map<int, std::set<int>> m_ColLink;
	// �� �׷��� �̰Ŵ�.
	// std::map<int, std::list<HPTR<HCOL>>> m_AllCol;
	// std::list<HPTR<HCOL>>

	for (auto& LeftIndex : m_ColLink)
	{
		// std::map<int, std::set<int>> m_ColLink;
		// std::map<int == �÷��̾�׷�
		// ColIndex.first

		// std::set<int> == ���� �׷��, ���׷�
		// ColIndex.second

		// �÷��̾� �׷�
		std::map<int, std::list<HPTR<HCOL>>>::iterator LeftGroup = m_AllCol.find(LeftIndex.first);
		if (LeftGroup == m_AllCol.end())
		{
			continue;
		}

		// �ڷ��� std::list<HPTR<HCOL>>
		if (true == LeftGroup->second.empty())
		{
			continue;
		}

		for (int RightIndex : LeftIndex.second)
		{
			std::map<int, std::list<HPTR<HCOL>>>::iterator RightGroup = m_AllCol.find(RightIndex);

			if (RightGroup == m_AllCol.end())
			{
				continue;
			}

			if (true == RightGroup->second.empty())
			{
				continue;
			}


			if (LeftIndex.first == RightIndex)
			{
				std::list<HPTR<HCOL>>::iterator LeftStart = LeftGroup->second.begin();

				if (false == (*LeftStart)->IsUpdate())
				{
					continue;
				}

				std::list<HPTR<HCOL>>::iterator LeftEnd = RightGroup->second.end();
				--LeftEnd;


				// 0 1 2 
				for (; LeftStart != LeftEnd; ++LeftStart)
				{
					std::list<HPTR<HCOL>>::iterator RightStart = LeftStart;
					std::list<HPTR<HCOL>>::iterator RightEnd = RightGroup->second.end();
					++RightStart;

					for (; RightStart != RightEnd; ++RightStart)
					{
						if (false == (*RightStart)->IsUpdate())
						{
							continue;
						}

						(*LeftStart)->ColCheck(*RightStart);
					}
				}


			}
			else 
			{


				// �ڱ� �׷���� �浹�� ���� ���Ѱ̴ϴ�.
				for (auto& LeftCol : LeftGroup->second)
				{

					if (false == LeftCol->IsUpdate())
					{
						continue;
					}

					for (auto& RightCol : RightGroup->second)
					{
						if (false == RightCol->IsUpdate())
						{
							continue;
						}

						LeftCol->ColCheck(RightCol);
					}
				}
			}


		}

		// ���� �� �׷��� �浹�Ҽ� ����.
	}


}

void HGAMESCENE::UpdatePrev() 			  
{
	HUPDATELISTOBJMGR<HSCENECOM>::UpdatePrev();
	HUPDATELISTOBJMGR<HGAMEACTOR>::UpdatePrev();
}
void HGAMESCENE::Update() 				  
{
	HUPDATELISTOBJMGR<HSCENECOM>::Update();
	HUPDATELISTOBJMGR<HGAMEACTOR>::Update();
}
void HGAMESCENE::UpdateNext() 			  
{
	HUPDATELISTOBJMGR<HSCENECOM>::UpdateNext();
	HUPDATELISTOBJMGR<HGAMEACTOR>::UpdateNext();

}
void HGAMESCENE::RenderPrev() 			  
{
	HUPDATELISTOBJMGR<HSCENECOM>::RenderPrev();
	HUPDATELISTOBJMGR<HGAMEACTOR>::RenderPrev();

	// �θ� ���� ���� �ֻ��� Ʈ�������� ��Ƴ��� �ڷᱸ���ΰ��̴�.
	for (auto& _TransForm : m_AllTrans)
	{
		_TransForm->TransUpdate();
	}
}
void HGAMESCENE::RenderNext() 			  
{
	HUPDATELISTOBJMGR<HSCENECOM>::RenderNext();
	HUPDATELISTOBJMGR<HGAMEACTOR>::RenderNext();
}
void HGAMESCENE::CollisionPrev()		  
{
	HUPDATELISTOBJMGR<HSCENECOM>::CollisionPrev();
	HUPDATELISTOBJMGR<HGAMEACTOR>::CollisionPrev();
}
void HGAMESCENE::CollisionNext()		  
{
	HUPDATELISTOBJMGR<HSCENECOM>::CollisionNext();
	HUPDATELISTOBJMGR<HGAMEACTOR>::CollisionNext();
}
void HGAMESCENE::SceneChangeEnd() 		  
{
	HUPDATELISTOBJMGR<HSCENECOM>::SceneChangeEnd();
	HUPDATELISTOBJMGR<HGAMEACTOR>::SceneChangeEnd();
}
void HGAMESCENE::SceneChangeStart() 	  
{
	HUPDATELISTOBJMGR<HSCENECOM>::SceneChangeStart();
	HUPDATELISTOBJMGR<HGAMEACTOR>::SceneChangeStart();
}

typedef std::list<HUPDATELISTOBJMGR<HSCENECOM>::LISTDATA>::iterator SceneComIter;
typedef std::list<HUPDATELISTOBJMGR<HGAMEACTOR>::LISTDATA>::iterator ActorIter;


void HGAMESCENE::Release()
{
	// SceneComRelease
	{
		SceneComIter Start = HUPDATELISTOBJMGR<HSCENECOM>::m_ObjList.begin();
		SceneComIter End = HUPDATELISTOBJMGR<HSCENECOM>::m_ObjList.end();

		for (; Start != End; )
		{
			if (true == Start->Obj->IsDeath())
			{
				Start = HUPDATELISTOBJMGR<HSCENECOM>::m_ObjList.erase(Start);
			}
			else
			{
				++Start;
			}
		}
	}

	// Actor
	{
		// ���� ������ �ִ� �༮�� ���� �������� �������°� ����.
		// �������� �����.

		// Trans
		{
			std::list<HPTR<HTRANS>>::iterator Start = m_AllTrans.begin();
			std::list<HPTR<HTRANS>>::iterator End = m_AllTrans.end();

			for (; Start != End; )
			{
				if (true == (*Start)->IsDeath())
				{
					Start = m_AllTrans.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}

		// Col
		{
			std::map<int, std::list<HPTR<HCOL>>>::iterator Start = m_AllCol.begin();
			std::map<int, std::list<HPTR<HCOL>>>::iterator End = m_AllCol.end();

			// std::map<int, std::list<HPTR<HRENDERER>>>:: Iterator
			// first == int, second == std::list<HPTR<HRENDERER>>

			for (; Start != End; ++Start)
			{
				std::list<HPTR<HCOL>>::iterator StartCol = Start->second.begin();
				std::list<HPTR<HCOL>>::iterator EndCol = Start->second.end();

				for (; StartCol != EndCol; )
				{
					if (true == (*StartCol)->IsDeath())
					{
						StartCol = Start->second.erase(StartCol);
					}
					else
					{
						++StartCol;
					}

				}

			}
		}
		// Cam
		{
			std::map<int, HPTR<HCAM>>::iterator Start = m_AllCam.begin();
			std::map<int, HPTR<HCAM>>::iterator End = m_AllCam.end();

			for (; Start != End; )
			{
				if (true == Start->second->IsDeath())
				{
					if (m_MainCam == Start->second)
					{
						m_MainCam = nullptr;
					}
					Start = m_AllCam.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}
		// Renderer
		{
			std::map<int, std::list<HPTR<HRENDERER>>>::iterator Start = m_AllRender.begin();
			std::map<int, std::list<HPTR<HRENDERER>>>::iterator End = m_AllRender.end();

			// std::map<int, std::list<HPTR<HRENDERER>>>:: Iterator
			// first == int, second == std::list<HPTR<HRENDERER>>

			for (; Start != End; ++Start)
			{
				std::list<HPTR<HRENDERER>>::iterator StartRender = Start->second.begin();
				std::list<HPTR<HRENDERER>>::iterator EndRender = Start->second.end();

				for (; StartRender != EndRender; )
				{
					if (true == (*StartRender)->IsDeath())
					{
						StartRender = Start->second.erase(StartRender);
					}
					else
					{
						++StartRender;
					}

				}

			}
		}

		// Light
		{
			bool LightReCheck = false;

			std::map<int, std::vector<HPTR<HLight>>>::iterator Start = m_AllLight.begin();
			std::map<int, std::vector<HPTR<HLight>>>::iterator End = m_AllLight.end();

			// std::map<int, std::list<HPTR<HRENDERER>>>:: Iterator
			// first == int, second == std::list<HPTR<HRENDERER>>

			for (; Start != End; ++Start)
			{
				std::vector<HPTR<HLight>>::iterator StartRender = Start->second.begin();
				std::vector<HPTR<HLight>>::iterator EndRender = Start->second.end();

				for (; StartRender != EndRender; )
				{
					if (true == (*StartRender)->IsDeath())
					{
						LightReCheck = true;
						// ����Ʈ�� ����Ʈ ������ �ֱ� ������ �̰� ������ ����.
						// �����Ϳ� ���ؼ� �������� ����� �Ѵ�.
						StartRender = Start->second.erase(StartRender);
					}
					else
					{
						++StartRender;
					}

				}

			}

			if (true == LightReCheck)
			{
				LightCheck();
			}

			// LightReCheck = true;
		}


		{
			ActorIter Start = HUPDATELISTOBJMGR<HGAMEACTOR>::m_ObjList.begin();
			ActorIter End = HUPDATELISTOBJMGR<HGAMEACTOR>::m_ObjList.end();

			for (; Start != End; )
			{
				if (true == Start->Obj->IsDeath())
				{
					Start->Obj->Release();
					Start = HUPDATELISTOBJMGR<HGAMEACTOR>::m_ObjList.erase(Start);
				}
				else
				{
					++Start;
				}
			}
		}
	}
}

void HGAMESCENE::PushCam(HPTR<HCAM> _Cam) 
{
	if (m_AllCam.end() != m_AllCam.find(_Cam->Order()))
	{
		AMSG(L"ī�޶��� ������ ���ƽ��ϴ�.");
	}

	for (int Value : _Cam->m_VIEWRENDERERS)
	{
		CreateRenderGroupLight(Value);
	}

	if (nullptr == m_MainCam)
	{
		m_MainCam = _Cam;
	}

	m_AllCam[_Cam->Order()] = _Cam;
}

ObjectLightData* HGAMESCENE::GetLightData(int _Index)
{
	return &(m_AllLightData[_Index]);
}

void HGAMESCENE::CreateRenderGroupLight(int _Index) 
{
	if (m_AllRender.end() != m_AllRender.find(_Index))
	{
		return;
	}
	// ����Ʈ�� ����ϴ�.
	m_AllRender.insert(
		std::map<int, std::list<HPTR<HRENDERER>>>::value_type(_Index,
			std::list<HPTR<HRENDERER>>()));

	m_AllLight.insert(
		std::map<int, std::vector<HPTR<HLight>>>::value_type(_Index,
			std::vector<HPTR<HLight>>()));

	m_AllLightData.insert( std::map<int, ObjectLightData>::value_type(_Index, ObjectLightData()));
}

void HGAMESCENE::PushLight(HPTR<HLight> _Light) 
{
	// Ȥ�ó� �׷��� ������ �����.
	for (int Value : _Light->m_VIEWRENDERERS)
	{
		CreateRenderGroupLight(Value);
	}

	for (int Value : _Light->m_VIEWRENDERERS)
	{
		m_AllLight[Value].push_back(_Light);
		LightData& LightData = m_AllLightData[Value].ArrLightData[m_AllLightData[Value].LightCount[0]];
		_Light->DataList.push_back(&LightData);

		++m_AllLightData[Value].LightCount[0];
	}
}

void HGAMESCENE::PushRender(HPTR<HRENDERER> _Render)
{
	if (m_AllRender.end() == m_AllRender.find(_Render->Order()))
	{
		CreateRenderGroupLight(_Render->Order());
	}

	m_AllRender[_Render->Order()].push_back(_Render);
}

void HGAMESCENE::PushCol(HPTR<HCOL> _Col) 
{
	if (m_AllCol.end() == m_AllCol.find(_Col->Order()))
	{
		m_AllCol.insert(
			std::map<int, std::list<HPTR<HCOL>>>::value_type(_Col->Order(),
				std::list<HPTR<HCOL>>()));
	}

	m_AllCol[_Col->Order()].push_back(_Col);
}



void HGAMESCENE::ActorClear() 
{
	m_AllCol.clear();
	m_AllCam.clear();
	m_AllRender.clear();
	m_AllTrans.clear();
	HUPDATELISTOBJMGR<HGAMEACTOR>::m_ObjList.clear();
	m_MainCam = nullptr;
}

HPTR<HCAM> HGAMESCENE::MainCam() {
	return m_MainCam;
}