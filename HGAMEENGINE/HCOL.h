#pragma once
#include "HTRANS.h"
#include <unordered_set>
#include <functional>
#include <list>
#include "HGAMEDEBUG.h"

class HCOL : public HTRANS
{
private:
	COLTYPE m_Type;

public:
	void ColType(COLTYPE _Type)
	{
		m_Type = _Type;
	}

private:
	// 일반적으로 레드블랙트리인 셋보다 빠르다.
	// 긴문자열인 경우에는
	// 너무 신경쓸 필요는 없다.
	std::unordered_set<HCOL*> m_ColSet;

private:
	std::list<std::function<void(HCOL*, HCOL*)>> m_EnterFunc;
	std::list<std::function<void(HCOL*, HCOL*)>> m_StayFunc;
	std::list<std::function<void(HCOL*, HCOL*)>> m_ExitFunc;

public:
	template<typename T>
	void PushEnterFunc(T* _Obj, void(T::*_Ptr)(HCOL*, HCOL*)) 
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));
	}
	template<typename T>
	void PushStayFunc(T* _Obj, void(T::* _Ptr)(HCOL*, HCOL*)) {
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}
	template<typename T>
	void PushExitFunc(T* _Obj, void(T::* _Ptr)(HCOL*, HCOL*)) {
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_ExitFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}

	void PushEnterFunc(void(*_Ptr)(HCOL*, HCOL*))
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}
	void PushStayFunc(void(*_Ptr)(HCOL*, HCOL*)) 
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}
	void PushExitFunc(void(*_Ptr)(HCOL*, HCOL*)) {
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		m_ExitFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}



private:
	void CallEnter(HCOL* _Other);
	void CallStay(HCOL* _Other);
	void CallExit(HCOL* _Other);

public:
	void ColCheck(HPTR<HCOL> _Other);

	void Release() override;

public:
	void Init(int _Order = 0);
};


