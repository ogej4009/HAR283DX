#pragma once
#include <string>
#include <atlstr.h> // char => wchar wchar => char�� ��ȯ�����ִ� �Լ��� ����ִ�.
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
	// ������
	bool IsEmpty() const
	{
		return m_Str.size() == 0;
	}

	// ������
	size_t StrCount() const
	{
		return m_Str.size();
	}

public:
	operator const wchar_t*() const
	{
		// ���ο� �ִ� �迭�� �����͸� �������� �ش�.
		return m_Str.c_str();
	}

	operator std::string() const
	{
		return CW2A(m_Str.c_str()).m_psz;

		// ���ο� �ִ� �迭�� �����͸� �������� �ش�.
		// return m_Str.c_str();
	}

	operator char*() const
	{
		return CW2A(m_Str.c_str()).m_psz;

		// ���ο� �ִ� �迭�� �����͸� �������� �ش�.
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
		// find��� �Լ��� wstring
		// wchar_t*
		return m_Str.find(_Find.m_Str, _Off);
	}

	size_t FindLast(const HGAMESTRING& _Find) const
	{
		// Last �ڿ��� ���� ã�´�.
		return m_Str.find_last_of(_Find.m_Str);
	}

	// ������
	void EraseStr(size_t _Start, size_t _End)
	{
		// m_Str wstring
		// wstring ������ ��ɵ��� �̿��ؼ� ����� �ִ�.
		// Last �ڿ��� ���� ã�´�.
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


	// �Ϻκи� ���ڿ����� ���� ���
	HGAMESTRING RangeToStr(size_t _Start, size_t _End) const
	{
		// �ָ� ���Ͷ�� ������
		std::wstring Str;
		// �̸� ���۸� �Ҵ��ϴ°�
		//         658    658
		Str.resize(_End - _Start - 1);

		// ��𼭺��� ��������.
		m_Str.copy(&Str[0], _End - _Start - 1, _Start + 1);
		return Str; // '\\' ������ �ʴ´�
	}

	HGAMESTRING Cut(size_t _Start, size_t _End) const
	{
		return m_Str.substr(_Start, _End - _Start + 1); // '\\' ������ �ʴ´�
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



// ���� ���۷�����
// ������ٰ��� �����Լ� �����س����� �ȵȴ�.
HGAMESTRING operator+(const wchar_t* _Left, const HGAMESTRING& _Right);
bool operator==(const wchar_t* _Left, const HGAMESTRING& _Right);
bool operator!=(const wchar_t* _Left, const HGAMESTRING& _Right);