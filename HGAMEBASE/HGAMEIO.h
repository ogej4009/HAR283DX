#pragma once
#include "HGAMESTRING.h"
#include <list>
// �����
// ���������
// ���ڿ� 
// ���� ����°� ���ڿ��� ���� ���϶��� ����.

// ��ο� �ʿ��� ��ɵ��� ����ϴ� Ŭ����

// �ε��Ҷ� �� ��� ã�ƾ� �Ұ� �ƴѰ�?
// �׷��� ������ ��ĥ�ϴ°��� �׻� ����?
// �޶����� �׶��׶� ������ ��θ� ã�ư��� �Ѵ�.
// D:\AR28\AR28API\AR28API\HGAMEBASE\BIN\RES
class HGAMEPATH
{
public:
	HGAMESTRING m_Str;

public:
	// �� ��ΰ� �����ϴ��� ���ϴ���?
	static bool IsExits(const HGAMESTRING& _Str)
	{
		// 0 �������� �ִ��� ������?
		// 2 �� ������ �б� �����̳� �ƴϳ�?
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
		// ������ ���� �����?
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


// �Ѵ� ��θ� �� ��� �ִ�.
// ���丮
class HGAMEFILE;
class HGAMEDIRECTORY : public HGAMEIO
{
public:
	void MoveParent();
	// ���̸��� ������ ���������� �ö󰡶�.
	void MoveParent(const HGAMESTRING& _Folder);
	void Move(const HGAMESTRING& _Folder);

	std::list<HGAMEFILE> DirAllFile(const wchar_t* _Ext = L"", const wchar_t* _Name = L"");


	HGAMESTRING FolderName();

	bool IsFileExits(const HGAMESTRING& _FileName);

	// �̳༮�� �����Ǹ�
	// ������ m_Path�� ���� ����Ǵ� ��θ� �ڽ��� ��η� ��� �����.
public:
	HGAMEDIRECTORY();
	~HGAMEDIRECTORY();
};
