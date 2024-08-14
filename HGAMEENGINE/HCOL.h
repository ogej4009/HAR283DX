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
	// �Ϲ������� �����Ʈ���� �º��� ������.
	// �乮�ڿ��� ��쿡��
	// �ʹ� �Ű澵 �ʿ�� ����.
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
			AMSG(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));
	}
	template<typename T>
	void PushStayFunc(T* _Obj, void(T::* _Ptr)(HCOL*, HCOL*)) {
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}
	template<typename T>
	void PushExitFunc(T* _Obj, void(T::* _Ptr)(HCOL*, HCOL*)) {
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_ExitFunc.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1, std::placeholders::_2));

	}

	void PushEnterFunc(void(*_Ptr)(HCOL*, HCOL*))
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_EnterFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}
	void PushStayFunc(void(*_Ptr)(HCOL*, HCOL*)) 
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
		}

		m_StayFunc.push_back(std::bind(_Ptr, std::placeholders::_1, std::placeholders::_2));
	}
	void PushExitFunc(void(*_Ptr)(HCOL*, HCOL*)) {
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr�� �Լ��� �־�����ϴ�. �����Ҽ� �����ϴ�.");
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


