#pragma once
#include <string>
#include <atlstr.h> // char => wchar wchar => char로 변환시켜주는 함수가 들어있다.
#include <list>

class HSTRINGDATA;
class HGAMESTRING
{
private:
	std::wstring m_Str;

public:
	const wchar_t* PointerStr() 
	{
		return m_Str.c_str();
	}

	template<typename FmtType, typename... TemplateTypes>
	void Appendf(const FmtType& Fmt, TemplateTypes... Args)
	{
		AppendfInternal(Fmt, Args...);
	}

	void AppendfInternal(const char* fmt, ...);
	void AppendfInternal(const wchar_t* fmt, ...);



public:
	// 마지막
	bool IsEmpty() const
	{
		return m_Str.size() == 0;
	}

	// 마지막
	size_t StrCount() const
	{
		return m_Str.size();
	}

public:
	operator const wchar_t*() const
	{
		// 내부에 있는 배열의 포인터를 리턴해주 준다.
		return m_Str.c_str();
	}

	operator std::string() const
	{
		return CW2A(m_Str.c_str()).m_psz;

		// 내부에 있는 배열의 포인터를 리턴해주 준다.
		// return m_Str.c_str();
	}

	operator char*() const
	{
		return CW2A(m_Str.c_str()).m_psz;

		// 내부에 있는 배열의 포인터를 리턴해주 준다.
		// return m_Str.c_str();
	}


	bool operator==(const wchar_t* _Other) const
	{
		return m_Str == _Other;
	}

	bool operator!=(const wchar_t* _Other) const
	{
		return m_Str != _Other;
	}

	bool operator==(const HGAMESTRING& _Other) const
	{
		return _Other.m_Str == m_Str;
	}

	bool operator!=(const HGAMESTRING& _Other) const
	{
		return _Other.m_Str != m_Str;
	}

	bool operator>(const HGAMESTRING& _Other) const
	{
		return _Other.m_Str > m_Str;
	}

	bool operator<(const HGAMESTRING& _Other) const
	{
		return _Other.m_Str < m_Str;
	}


	HGAMESTRING& operator=(const wchar_t* _Ptr) 
	{
		m_Str = _Ptr;

		return *this;
	}

	HGAMESTRING& operator=(const HGAMESTRING& _Other)
	{
		m_Str = _Other.m_Str;

		return *this;
	}

	HGAMESTRING operator+(const wchar_t* _Other) const 
	{
		return m_Str + _Other;
	}

	HGAMESTRING operator+(const HGAMESTRING& _Other) const
	{
		return m_Str + _Other.m_Str;
	}

	HGAMESTRING& operator+=(const HGAMESTRING& _Other)
	{
		m_Str += _Other.m_Str;
		return *this;
	}

	size_t Find(const HGAMESTRING& _Find, size_t _Off = 0) const
	{
		// find라는 함수가 wstring
		// wchar_t*
		return m_Str.find(_Find.m_Str, _Off);
	}

	size_t FindLast(const HGAMESTRING& _Find) const
	{
		// Last 뒤에서 부터 찾는다.
		return m_Str.find_last_of(_Find.m_Str);
	}

	// 지워라
	void EraseStr(size_t _Start, size_t _End)
	{
		// m_Str wstring
		// wstring 내부의 기능들을 이용해서 만들고 있다.
		// Last 뒤에서 부터 찾는다.
		m_Str.replace(_Start, _End, L"");
	}

	void EraseStr(const HGAMESTRING& _Other)
	{
		size_t Start = Find(_Other, 0);
		EraseStr(Start, Start + _Other.StrCount());
	}

	void ChangeStr(const HGAMESTRING& _OldStr, const HGAMESTRING& _NewStr)
	{
		size_t Start = Find(_OldStr, 0);
		EraseStr(Start, Start + _OldStr.StrCount());
		m_Str.insert(Start, _NewStr);
	}


	// 일부분만 문자열에서 뜯어내는 기능
	HGAMESTRING RangeToStr(size_t _Start, size_t _End) const
	{
		// 애를 벡터라고 봤을때
		std::wstring Str;
		// 미리 버퍼를 할당하는것
		//         658    658
		Str.resize(_End - _Start - 1);

		// 어디서부터 어디까지다.
		m_Str.copy(&Str[0], _End - _Start - 1, _Start + 1);
		return Str; // '\\' 원하지 않는다
	}

	HGAMESTRING Cut(size_t _Start, size_t _End) const
	{
		return m_Str.substr(_Start, _End - _Start + 1); // '\\' 원하지 않는다
	}


	std::list<HSTRINGDATA> AllFindData(const HGAMESTRING& _Name, size_t _Offset = 0);
	std::list<HSTRINGDATA> RerversAllFindData(const HGAMESTRING& _Name, size_t _Offset = 0);

	size_t RerversTrimPos(size_t _Pos);
	size_t RerversFindTrimPos(size_t _Pos);

	size_t TrimPos(size_t _Pos);
	size_t FindTrimPos(size_t _Pos);

	HSTRINGDATA RerversTrimToTrim(size_t _Pos);
	HSTRINGDATA TrimToTrim(size_t _Pos);

	wchar_t At(size_t _Pos) 
	{
		return m_Str.at(_Pos);
	}

	HGAMESTRING ToUpperReturn();

public:
	HGAMESTRING() : m_Str()
	{
	}

	HGAMESTRING(const char* _Ptr) : m_Str(CA2W(_Ptr).m_psz)
	{
	}

	HGAMESTRING(const wchar_t* _Ptr) : m_Str(_Ptr)
	{
	}

	HGAMESTRING(std::wstring _Str) : m_Str(_Str)
	{
	}

	HGAMESTRING(const HGAMESTRING& _Str) : m_Str(_Str)
	{
	}
};


class HSTRINGDATA
{
public:
	HGAMESTRING Text;
	size_t StartPos;
	size_t EndPos;
};



// 전역 오퍼레이팅
// 헤더에다가는 전역함수 구현해놓으면 안된다.
HGAMESTRING operator+(const wchar_t* _Left, const HGAMESTRING& _Right);
bool operator==(const wchar_t* _Left, const HGAMESTRING& _Right);
bool operator!=(const wchar_t* _Left, const HGAMESTRING& _Right);