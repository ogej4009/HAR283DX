#pragma once
#include <HMGR.h>
#include <HGAMESTRING.h>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <HLISTOBJMGR.h>
#include "HVIRTUALPROGRESS.h"
#include "HGAMECOM.h"
#include "HRenderingDataStructer.h"


class HCAM;
class HCOL;
class HTRANS;
class HLight;
class HRENDERER;
class HSCENECOM;
class HGAMEACTOR;
class HGAMESCENE : public HMGR<HGAMESCENE>
	, public HVIRTUALPROGRESS
	, HUPDATELISTOBJMGR<HGAMEACTOR>
	, HUPDATELISTOBJMGR<HSCENECOM>
{
public:
	static HPTR<HGAMESCENE> m_CurScene;
	static HPTR<HGAMESCENE> m_NextScene;
	static void Progress();

	static HPTR<HGAMESCENE> Create(const HGAMESTRING& _Name)
	{
		HPTR<HGAMESCENE> Res = CreateToInsert(_Name);
		return Res;
	}

	template<typename STARTCOM>
	static HPTR<HGAMESCENE> Create(const HGAMESTRING& _Name)
	{
		HPTR<HGAMESCENE> Res = CreateToInsert(_Name);
		Res->CreateCom<STARTCOM>();
		return Res;
	}
	static void ChangeScene(const HGAMESTRING& _Name);

public:
	HPTR<HGAMEACTOR> CreateActor(const HGAMESTRING& _Name = L"");

	template<typename COMTYPE>
	HPTR<COMTYPE> CreateCom(const HGAMESTRING& _Name = L"")
	{
		HPTR<COMTYPE> NewCom = HLISTOBJMGR<HSCENECOM>::CreateObj<COMTYPE>(_Name);
		NewCom->Scene(this);
		NewCom->Init();
		return NewCom;
	}

	template<typename COMTYPE>
	HPTR<COMTYPE> FindCom(const HGAMESTRING& _Name = L"")
	{
		return HLISTOBJMGR<HSCENECOM>::FindObjType<COMTYPE>();
	}


public:
	void UpdatePrev() 	override;
	void Update() 	override;
	void UpdateNext() 	override;

	void RenderPrev() 	override;
	void Render();
	void RenderNext() 	override;

	void CollisionPrev() override;
	void Collision();
	void CollisionNext() override;

	void SceneChangeEnd() 	override;
	void SceneChangeStart() override;
	void Release() override;


	void ActorClear();
	//////////////////////////////////////////////// trans 관리
private:
	friend HTRANS;
	// 이렇게 따로 모아 놓겠다.
	std::list<HPTR<HTRANS>> m_AllTrans;

	//////////////////////////////////////////////// Renderer 관리

/// <summary>
/// /////////////////////////
/// </summary>
	/// 최상위에는 그룹이 있고
	// int로 한다. 1번 
	// 각 그룹은 랜더러, 라이트

	// 랜더링 자체의 주체는 카메라.

	// 그 그룹을 보는 카메라
	// 
private:
	friend HCAM;
	friend HRENDERER;
	friend HLight;
	HPTR<HCAM> m_MainCam;
	std::map<int, HPTR<HCAM>> m_AllCam;

	//   Camera1 01   Camera2 12
	// 0  List  Camera1
	// 1  List  Camera1 Camera2
	// 2  List  Camera2

	std::map<int, std::vector<HPTR<HLight>>> m_AllLight;
	std::map<int, ObjectLightData> m_AllLightData;

	std::map<int, std::list<HPTR<HRENDERER>>> m_AllRender;

	void PushCam(HPTR<HCAM> _Cam);
	void PushLight(HPTR<HLight> _Light);
	void PushRender(HPTR<HRENDERER> _Render);
	void LightCheck();

	static bool ZSORT(HPTR<HRENDERER>& _Left, HPTR<HRENDERER>& _Right);

public:
	HPTR<HCAM> MainCam();
	void CreateRenderGroupLight(int _Index);
	ObjectLightData* GetLightData(int _Index);
////////////////////////////////////////// COL

private:
	friend HCOL;
	//        플레이어    
	std::map<int, std::set<int>> m_ColLink;
	std::map<int, std::list<HPTR<HCOL>>> m_AllCol;

public:
	void PushCol(HPTR<HCOL> _Col);

public:
	template<typename ... REST>
	void ColLink(int _Order, REST ... _Arg)
	{
		if (m_ColLink.end() == m_ColLink.find(_Order))
		{
			// 찾아봐.
			// 정석
			// m_ColIndex.insert(std::map<int, std::set<int>>::value_type(_Order, std::set<int>()));
			// m_ColIndex.insert(std::make_pair(_Order, std::set<int>()));
			// m_ColIndex[_Order] = std::set<int>();
			m_ColLink[_Order];
		}

		// m_ColIndex : std::map<int, std::set<int>> ;
		// m_ColIndex[_Order] : std::set<int> ;

		ColLinkPush(m_ColLink[_Order], _Arg...);
	}

	template<typename ... REST>
	void ColLinkPush(std::set<int>& _Value, int _PushIndex, REST ... _Arg)
	{
		if (_Value.end() != _Value.find(_PushIndex))
		{
			AMSG(L"같은 그룹과 두번 충돌하려고 했습니다.");
		}

		_Value.insert(_PushIndex);
		ColLinkPush(_Value, _Arg...);
	}

	void ColLinkPush(std::set<int>& _Value, int _PushIndex)
	{
		if (_Value.end() != _Value.find(_PushIndex))
		{
			AMSG(L"같은 그룹과 두번 충돌하려고 했습니다.");
		}

		_Value.insert(_PushIndex);
	}


public:
	HGAMESCENE();
	~HGAMESCENE();
};



