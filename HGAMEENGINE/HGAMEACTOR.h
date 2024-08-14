#pragma once
#include <HLISTOBJMGR.h>
#include "HVIRTUALPROGRESS.h"

// 이녀석은 기능을 관리하는 기능만 존재한다.
// 이 엑터는 주인공이 될꺼야.
class HTRANS;
class HACTORCOM;
class HGAMESCENE;
class HGAMEACTOR : public HGAMEREF, public HVIRTUALPROGRESS, public HUPDATELISTOBJMGR<HACTORCOM>
{
public:
	template< typename _Type > 
	friend class HUPDATELISTOBJMGR;

	friend HGAMESCENE;
	friend HTRANS;

public:
	template<typename COMTYPE, typename ... REST>
	HPTR<COMTYPE> CreateComName(const HGAMESTRING& _Name = L"", REST ... _ARG)
	{
		HPTR<COMTYPE> NewCom = HLISTOBJMGR<HACTORCOM>::CreateObj<COMTYPE>(_Name);
		NewCom->ACTOR(this);
		NewCom->Init(_ARG...);
		return NewCom;
	}

	template<typename COMTYPE, typename ... REST>
	HPTR<COMTYPE> CreateCom(REST ... _ARG)
	{
		HPTR<COMTYPE> NewCom = HLISTOBJMGR<HACTORCOM>::CreateObj<COMTYPE>();
		NewCom->ACTOR(this);
		NewCom->Init(_ARG...);
		return NewCom;
	}

private:
	HGAMESCENE* m_SCENE;
	HTRANS* m_TRANS;

public:
	HTRANS* TRANS();
	HGAMESCENE* SCENE();

public:
	template<typename FINDTYPE>
	FINDTYPE* FindComName(std::wstring _Name)
	{
		return FindObjName<FINDTYPE>(_Name);
	}


	template<typename FINDTYPE>
	HPTR<FINDTYPE> FindComType()
	{
		return FindObjType<FINDTYPE>();
	}

	template<typename FINDTYPE>
	std::list<HPTR<FINDTYPE>> FindComTypeAll()
	{
		return FindObjTypeAll<FINDTYPE>();
	}

private:
	void UpdatePrev() 	override;
	void Update() 	override;
	void UpdateNext() 	override;
	void RenderPrev() 	override;
	void RenderNext() 	override;
	void CollisionPrev() override;
	void CollisionNext() override;
	void SceneChangeEnd() 	override;
	void SceneChangeStart() override;
	void Release() override;


};

