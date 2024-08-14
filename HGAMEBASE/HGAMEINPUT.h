#pragma once
#include <vector>
#include <assert.h>
#include "HGAMESTRING.h"
#include <map>
#include "HGAMEMATH.h"

class HGAMEINPUT
{
public:
	class HGAMEKEY
	{
	public:
		friend HGAMEINPUT;

	public:
		HGAMESTRING Name;
		std::vector<int> m_KeyVec;

		bool Down; // ó�� ���ȴ�
		bool Press; // ��� ������ �ִ�
		bool Up; // Ű�� ������
		bool Free; // ��� ���� ���´�

	private:
		bool KeyCheck();
		void Update();

	private:
		HGAMEKEY() : Down(false), Press(false), Up(false), Free(true) {}
		~HGAMEKEY() {}
		// 0 != GetAsyncKeyState('A')
	};




public:
	class HGAMESTATIC
	{
	public:
		HGAMESTATIC();
		~HGAMESTATIC();
	};
	// ����� ������ �����̴�.
	static HGAMESTATIC StaticInst;

private:
	static std::map<HGAMESTRING, HGAMEKEY*> AllKey;

public:
	static HGAMEKEY* FindKey(const HGAMESTRING& _KeyName)
	{
		if (AllKey.end() == AllKey.find(_KeyName))
		{
			return nullptr;
		}

		// �����ε� �ٷ� ���� �������ش�.
		return AllKey[_KeyName];
	}

	static bool IsKey(const HGAMESTRING& _KeyName)
	{
		return nullptr != FindKey(_KeyName);
	}

	template<typename ... REST>
	static void CreateKey(const HGAMESTRING& _KeyName, REST ... Arg)
	{
		HGAMEKEY* NewKey = FindKey(_KeyName);

		if (nullptr != NewKey)
		{
			assert(false);
		}

		NewKey = new HGAMEKEY();
		NewKey->Name = _KeyName;
		NewKey->m_KeyVec.reserve(sizeof...(Arg));
		PushKey(NewKey, Arg...);
	}

private:
	template<typename T, typename ... REST>
	static void PushKey(HGAMEKEY* _NewKey, T _Value, REST ... Arg)
	{
		_NewKey->m_KeyVec.push_back(_Value);
		PushKey(_NewKey, Arg...);
	}

	static void PushKey(HGAMEKEY* _NewKey)
	{
		AllKey.insert(std::map<HGAMESTRING, HGAMEKEY*>::value_type(_NewKey->Name, _NewKey));
	}

public:
	static bool Down(const HGAMESTRING& _Key)
	{
		HGAMEKEY* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Down;
	}
	static bool Press(const HGAMESTRING& _Key) {
		HGAMEKEY* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Press;
	}
	static bool Up(const HGAMESTRING& _Key) {
		HGAMEKEY* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Up;
	}
	static bool Free(const HGAMESTRING& _Key) {
		HGAMEKEY* Ptr = FindKey(_Key);
		if (nullptr == Ptr) { assert(false); }
		return Ptr->Free;
	}

private:
	static HVECTOR PrevPos;
	static HVECTOR MouseDir;
public:
	static HVECTOR MousePos3D();
	static HVECTOR MouseDir3D();
	static HVECTOR MouseDir3DNormal();

public:
	static void Update();

};

