#pragma once
#include "HGAMESTRING.h"
#include <list>
// 디버깅
// 파일입출력
// 문자열 
// 파일 입출력과 문자열은 같이 엮일때가 많다.

// 경로에 필요한 기능들을 담당하는 클래스

// 로드할때 이 경로 찾아야 할것 아닌가?
// 그런데 게임을 설칠하는곳이 항상 같나?
// 달라져도 그때그때 마다의 경로를 찾아가야 한다.
// D:\AR28\AR28API\AR28API\HGAMEBASE\BIN\RES
class HGAMEPATH
{
public:
	HGAMESTRING m_Str;

public:
	// 그 경로가 존재하느냐 안하느냐?
	static bool IsExits(const HGAMESTRING& _Str)
	{
		// 0 그파일이 있느냐 없느냐?
		// 2 그 파일이 읽기 전용이냐 아니냐?
		if (0 == _waccess_s(_Str, 0))
		{
			return true;
		}

		return false;
	}

public:
	HGAMEPATH() {

	}


	HGAMEPATH(const wchar_t* _Path)  : m_Str(_Path)
	{

	}

	HGAMEPATH(const HGAMESTRING& _Path) : m_Str(_Path)
	{

	}
	~HGAMEPATH() {

	}
};

class HGAMEIO 
{
protected:
	HGAMEPATH m_Path;

public:
	HGAMESTRING PlusFileName(const HGAMESTRING& _Path)
	{
		return m_Path.m_Str + L"\\" + _Path;
	}

	static HGAMESTRING FileName(const HGAMESTRING& _Path) 
	{
		size_t Start1 = _Path.FindLast(L"\\");

		if (Start1 == std::string::npos)
		{
			Start1 = 0;
		}

		size_t Start2 = _Path.FindLast(L"/");

		if (Start2 == std::string::npos)
		{
			Start2 = 0;
		}

		size_t Start = std::string::npos;

		if (Start1 > Start2)
		{
			Start = Start1;
		}
		else {
			Start = Start2;
		}

		if (Start == std::string::npos)
		{
			Start = 0;
		}
		size_t End = _Path.StrCount();
		// 마지막 폴더 경로죠?
		HGAMESTRING Name = _Path.RangeToStr(Start, End);
		return Name;
	}


	const wchar_t* PCONSTWCHAR() 
	{
		return m_Path.m_Str;
	}

	HGAMESTRING IOName() const
	{
		return HGAMEIO::FileName(m_Path.m_Str);
	}

	HGAMESTRING DirPath() const
	{
		// "c::aaa.text"
		// "aaa.text"

		HGAMESTRING Path = m_Path.m_Str;
		Path.EraseStr(HGAMEIO::FileName(m_Path.m_Str));
		return Path;
	}

	void SetPath(const HGAMESTRING& _Path)
	{
		m_Path = _Path;
	}

	HGAMEIO() {

	}
};


// 둘다 경로를 잘 들고 있다.
// 디렉토리
class HGAMEFILE;
class HGAMEDIRECTORY : public HGAMEIO
{
public:
	void MoveParent();
	// 요이름의 폴더가 있을때까지 올라가라.
	void MoveParent(const HGAMESTRING& _Folder);
	void Move(const HGAMESTRING& _Folder);

	std::list<HGAMEFILE> DirAllFile(const wchar_t* _Ext = L"", const wchar_t* _Name = L"");


	HGAMESTRING FolderName();

	bool IsFileExits(const HGAMESTRING& _FileName);

	// 이녀석은 생성되면
	// 무조건 m_Path를 지금 실행되는 경로를 자신의 경로로 삼게 만든다.
public:
	HGAMEDIRECTORY();
	~HGAMEDIRECTORY();
};
