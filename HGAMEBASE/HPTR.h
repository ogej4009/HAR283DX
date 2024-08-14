#pragma once

class HGAMEREF
{
public:
	int REFCOUNT;

public:
	void ADDREFCOUNT() {
		++REFCOUNT;
	}
	void DECREFCOUNT(/*HREF* const this*/)
	{
		--REFCOUNT;
		if (0 >= REFCOUNT)
		{
			delete this;
		}
	}

public:
	HGAMEREF() : REFCOUNT(0) {}
	virtual ~HGAMEREF() {}
};

template<typename T>
class HPTR
{
public:
	T* PTR;

public:
	// ������ ������ �����ε�
	T* operator->()
	{
		return PTR;
	}

	operator T*()
	{
		return PTR;
	}

	// ������ ��ȯ�ϸ� ���������� �ʴ�.
	// ��ũ�� �巡���� �Ǿ������ ���°� �߻��Ѵ�.
	// const_cast; 
	// const�� const�� �ƴϰ� �����. ������� ������
	// static_cast;
	// �̳༮�� �츮�� �˰� �ִ� �Ϲ����� mamcpy�� ���� ĳ��Ʈ�� �ٸ� ����.
	// ũ��˻縸 �ϴ� ĳ���ÿ� ������.
	// reinterpret_cast;
	// ���� ��ﵵ �ȳ�. 
	// dynamic_cast;
	// ��Ӱ����϶��� ĳ������ ���ش�
	// ������ �����Լ� ���̺��� ���� ������� ĳ������ ���ֱ� ������
	// VIRTUAL�� �θ��ʿ� �־�� �Ѵ�.
	// �����Ҷ��� ����ϰڴ�
	template<typename OTHERTYPE>
	operator HPTR<OTHERTYPE>()
	{
		return dynamic_cast<OTHERTYPE*>(PTR);
	}

	bool operator==(void* _nullptr) const
	{
		return PTR == _nullptr;
	}

	bool operator==(const HPTR<T>& _Other) const
	{
		return PTR == _Other.PTR;
	}


	bool operator!=(void* _nullptr) const
	{
		return PTR != _nullptr;
	}

	HPTR& operator=(const HPTR<T>& _Other)
	{
		if (nullptr != PTR)
		{
			PTR->DECREFCOUNT();
		}


		PTR = _Other.PTR;
		if (nullptr != PTR)
		{
			PTR->ADDREFCOUNT();
		}
		return *this;
	}

	HPTR& operator=(T* const _Other)
	{
		if (nullptr != PTR)
		{
			PTR->DECREFCOUNT();
		}


		PTR = _Other;
		if (nullptr != PTR)
		{
			PTR->ADDREFCOUNT();
		}
		return *this;
	}

public:
	HPTR(const HPTR<T>& _Other) : PTR(_Other.PTR)
	{
		if (nullptr == PTR)
		{
			return;
		}
		PTR->ADDREFCOUNT();
	}

	HPTR() : PTR(nullptr)
	{
	}

	HPTR(T* _Ptr) : PTR(_Ptr)
	{
		if (nullptr == _Ptr)
		{
			return;
		}

		_Ptr->ADDREFCOUNT();
	}
	~HPTR()
	{
		if (nullptr == PTR)
		{
			return;
		}

		PTR->DECREFCOUNT();
	}
};

template<typename T>
bool operator!=(void* _Ptr, const HPTR<T> _TypeName) 
{
	return _TypeName.operator!=(_Ptr);
}

template<typename T>
bool operator==(void* _Ptr, const HPTR<T> _TypeName)
{
	return _TypeName.operator==(_Ptr);
}


template<typename T>
class HWPTR
{
public:
	T* PTR;

public:
	// ������ ������ �����ε�
	T* operator->()
	{
		return PTR;
	}

	HWPTR& operator=(const HWPTR<T>& _Other)
	{
		PTR = _Other.PTR;
		return *this;
	}

public:
	HWPTR(const HPTR<T>& _Other) : PTR(_Other.PTR)
	{
	}

	HWPTR() : PTR(nullptr)
	{
	}

	HWPTR(T* _Ptr) : PTR(_Ptr)
	{
	}
	virtual ~HWPTR()
	{
	}
};