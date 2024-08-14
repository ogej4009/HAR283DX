#pragma once
#include "HGAMEIO.h"
#include "HGAMESTRING.h"

// ����
class HGAMEFILE : public HGAMEIO
{
public:
	bool m_IsOpen;
	FILE* FILEPOINTER;

public:
	bool IsOpen() {
		return m_IsOpen;
	}

public:
	HGAMESTRING FullPath() const
	{
		return m_Path.m_Str;
	}

	HGAMESTRING FileName() const
	{
		return IOName();
	}

	HGAMESTRING Ext() const;

public:
	template<typename T>
	void operator>>(T& _Value)
	{
		fread_s(&_Value, sizeof(T), sizeof(T), 1, FILEPOINTER);
	}


	void operator>>(HGAMESTRING& _Value)
	{
		int Size = (int)_Value.StrCount();
		fread_s(&Size, sizeof(int), sizeof(int), 1, FILEPOINTER);
		wchar_t* Str = new wchar_t[Size];
		fread_s(Str, sizeof(wchar_t) * Size, sizeof(wchar_t) * Size, 1, FILEPOINTER);
		_Value = Str;
		delete[] Str;
	}

	template<typename T>
	void operator<<(const T& _Value)
	{
		fwrite(&_Value, sizeof(T), 1, FILEPOINTER);
	}

	void operator<<(HGAMESTRING& _Value)
	{
		int Size = (int)_Value.StrCount();
		Size += 1;
		fwrite(&Size, sizeof(int), 1, FILEPOINTER);
		fwrite(_Value.PointerStr(), sizeof(wchar_t) * Size, 1, FILEPOINTER);
	}


	template<typename T>
	void SaveValue(const T& _Value) 
	{
		fwrite(&_Value, sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void SavePointer(T* _Value, int _Count)
	{
		fwrite(_Value, sizeof(T) * _Count, 1, FILEPOINTER);
	}

	template<typename T>
	void LoadValue(T& _Value)
	{
		int Value = sizeof(T);

		fread_s(&_Value, sizeof(T), sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void LoadPointer(T* _Value, int _Count)
	{
		fread_s(_Value, sizeof(T) * _Count, sizeof(T) * _Count, 1, FILEPOINTER);
	}

	HGAMESTRING AllText() 
	{
		// �̵���Ű�°ǵ�.
		fseek(FILEPOINTER, 0, SEEK_END);

		// ������ ���ۿ������� �űⰡ ������
		// ���κ��̽�.
		long size = ftell(FILEPOINTER);
		// �ٽ� ���ʷ� ������.
		fseek(FILEPOINTER, 0, SEEK_SET);
		char* NewPtr = new char[(long)size];
		LoadPointer(NewPtr, size);
		NewPtr[size - 1] = 0;

		std::string StrText = NewPtr;

		// ��Ƽ����Ʈ <> �����ڵ�
		// �ƽ�Ű�ڵ� <> ���̵����Ʈ
		// HGAMESTRING Str = CA2W( NewPtr).m_psz;
		HGAMESTRING Str = CA2W(NewPtr, CP_UTF8).m_psz;
		delete[] NewPtr;
		return Str;
	}

public:
	HGAMEFILE(const HGAMESTRING& _FilePath, const HGAMESTRING& _FileMode) : FILEPOINTER(nullptr), m_IsOpen(false)
	{
		_wfopen_s(&FILEPOINTER, _FilePath, _FileMode);

		if (nullptr != FILEPOINTER)
		{
			m_IsOpen = true;
		}

		// FILE* PTR;
	// int 1
	// == b 0000 0001 0000 0000 0000 0000 0000 0000
	//      '1'

	// "rb" 
	// "rt"
	// "wb"
	// "wt"
	// fopen_s(PTR, "C:DJKALFSDJFKLDASJFKLA.PNG", "wb");

	}

	HGAMEFILE() : m_IsOpen(false), FILEPOINTER(nullptr)
	{

	}

	HGAMEFILE(const HGAMESTRING& _FilePath) : m_IsOpen(false), FILEPOINTER(nullptr)
	{
		SetPath(_FilePath);
	}

	HGAMEFILE(const wchar_t* _Path) : m_IsOpen(false), FILEPOINTER(nullptr)
	{
		SetPath(_Path);
	}
	~HGAMEFILE() 
	{
		if (nullptr != FILEPOINTER)
		{
			// �ڿ������� ������.
			fclose(FILEPOINTER);
		}
	}
};
