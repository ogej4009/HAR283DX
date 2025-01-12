#pragma once
#include <map>

#include "HGAMENAME.h"
#include "HGAMESTRING.h"
#include "HPTR.h"
#include "HGAMEDEBUG.h"
#include "HGAMEFILE.h"


template<typename T>
class HMGR : public HGAMEREF, public HGAMENAME
{
public:
	static std::map<HGAMESTRING, HPTR<T>> m_AllOBJ;


public:
	static HPTR<T> Find(const HGAMESTRING& _Name)
	{
		if (m_AllOBJ.end() == m_AllOBJ.find(_Name))
		{
			return nullptr;
		}

		return m_AllOBJ[_Name];
	}

	static void Insert(const HGAMESTRING& _Name, T* _NewObj)
	{
		if (Find(_Name) != nullptr )
		{
			AMSG(_Name + L"이름의 오브젝트가 이미지 존재합니다");
		}

		m_AllOBJ[_Name] = _NewObj;
	}

	// , 함수에 인자가 몇개가 들어올지도 모르고 
	// REST ... _Arg  어떻게 처리될지도 모른다.
	// 전달한다.

	template<typename ... REST>
	static HPTR<T> CreateToInsert(const HGAMESTRING& _Name, REST ... _Arg)
	{
		if (Find(_Name) != nullptr)
		{
			AMSG(_Name + L"이름의 오브젝트가 이미지 존재합니다");
		}

		T* NewObj = new T(_Arg...);
		NewObj->NAME(_Name);
		Insert(_Name, NewObj);
		return NewObj;
	}


	static void Delete(const HGAMESTRING& _Name)
	{
		if (Find(_Name) == nullptr)
		{
			AMSG(_Name + L"이름의 오브젝트가 이미지 존재하지 않습니다.");
		}

		m_AllOBJ.erase(_Name);
		return;
	}

	static void Clear() 
	{
		m_AllOBJ.clear();
	}


public:
	virtual ~HMGR(){}
};

template<typename T>
std::map<HGAMESTRING, HPTR<T>> HMGR<T>::m_AllOBJ;

template<typename T>
class HFILEMGR : public HMGR<T>
{
public:
	HGAMEFILE GameFile;

public:
	template<typename ... REST>
	static HPTR<T> CreateToInsertToFile(const HGAMESTRING& _Path, REST ... _Arg)
	{
		HPTR<T> NewRes = HMGR<T>::CreateToInsert(HGAMEIO::FileName(_Path), _Arg...);
		NewRes->GameFile.SetPath(_Path);
		return NewRes;
	}

	template<typename ... REST>
	static HPTR<T> CreateToInsertToName(const HGAMESTRING& _Path, const HGAMESTRING& _Name, REST ... _Arg)
	{
		HPTR<T> NewRes = HMGR<T>::CreateToInsert(_Name, _Arg...);
		NewRes->GameFile.SetPath(_Path);
		return NewRes;
	}

	template<typename ... REST>
	static HPTR<T> CreateToInsertToFileObj(const HGAMEFILE& _File, REST ... _Arg)
	{
		HPTR<T> NewRes = HMGR<T>::CreateToInsert(_File.FileName(), _Arg...);
		NewRes->GameFile = _File;
		return NewRes;
	}
};

template<typename T>
class HFOBJMGR : public HMGR<T>
{

private:
	static T* FOBJ;



public:
	static T* MAINOBJ()
	{
		return FOBJ;
	}

public:
	template<typename ... REST>
	static HPTR<T> CreateToInsert(const HGAMESTRING& _Name, REST ... _Arg)
	{
		HPTR<T> NewObj = HMGR<T>::CreateToInsert(_Name, _Arg...);
		if (nullptr == FOBJ)
		{
			FOBJ = NewObj;
		}

		return NewObj;
	}


};

template<typename T>
T* HFOBJMGR<T>::FOBJ = nullptr;