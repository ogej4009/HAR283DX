#pragma once
#include <list>
#include "HPTR.h"
#include "HGAMESTRING.h"


// ���൵�� �Ϲ������� �˼� ���� Ÿ����
// �˼��ְ� ���ִ� �����
// RTTI REAL TIME TYPE INFOMATION


template<typename MGRTYPE>
class HLISTOBJMGR
{
	// �̸����ε� ã��
	// Ÿ������ ã��
	// ����

public:
	class LISTDATA 
	{
	public:
		HGAMESTRING Name;
		const type_info* Type;
		HPTR<MGRTYPE> Obj;
	};


protected:
	// �������� ���ڴ�.
	std::list<LISTDATA> m_ObjList;

public:
	HLISTOBJMGR() {}
	virtual ~HLISTOBJMGR() {}

public:
	template<typename CREATETYPE>
	HPTR<CREATETYPE> CreateObj(const HGAMESTRING& _Name = L"")
	{
		LISTDATA DATA;
		DATA.Name = _Name;
		DATA.Type = &typeid(CREATETYPE);

		// HPTR<HSCENECOM> Obj => HPTR<HTITLECOM>;
		CREATETYPE* NewPtr = new CREATETYPE();
		DATA.Obj = NewPtr;
		m_ObjList.push_back(DATA);
		return NewPtr;
	}


	template<typename FINDTYPE>
	HPTR<FINDTYPE> FindObjName(std::wstring _Name)
	{
		for (auto& _Value : m_ObjList)
		{
			if (_Value.Name == _Name)
			{
				return _Value.Obj;
			}
		}

		return nullptr;
	}


	template<typename FINDTYPE>
	HPTR<FINDTYPE> FindObjType()
	{
		// RTTI�� ���ؼ� ���ΰ� ���� Ÿ�������� ���س��°��̴�.
		for (auto& _Value : m_ObjList)
		{
			if (_Value.Type == &typeid(FINDTYPE))
			{
				// _Value.Obj�� Ÿ��

				return _Value.Obj;
			}
		}
		return nullptr;
	}

	template<typename FINDTYPE>
	std::list<HPTR<FINDTYPE>> FindObjTypeAll()
	{
		std::list<HPTR<FINDTYPE>> List;
		for (auto& _Value : m_ObjList)
		{
			if (_Value.Type == &typeid(FINDTYPE))
			{
				List.push_back((FINDTYPE*)_Value.Obj);
			}
		}
		return List;
	}

};


template<typename MGRTYPE>
class HUPDATELISTOBJMGR : public HLISTOBJMGR<MGRTYPE>
{
public:
	void UpdatePrev() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->UpdatePrev();
		}
	}
	void Update() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->Update();
		}
	}
	void UpdateNext() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->UpdateNext();
		}
	}
	void RenderPrev() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->RenderPrev();
		}

	}
	void RenderNext() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->RenderNext();
		}

	}
	void CollisionPrev() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->CollisionPrev();
		}

	}
	void CollisionNext() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->CollisionNext();
		}
	}
	void SceneChangeEnd() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->SceneChangeEnd();
		}
	}
	void SceneChangeStart() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			if (false == Value.Obj->IsUpdate())
			{
				continue;
			}
			Value.Obj->SceneChangeStart();
		}
	}
	void Release() 
	{
		for (auto& Value : HLISTOBJMGR<MGRTYPE>::m_ObjList)
		{
			Value.Obj->Release();
		}
	}
};
