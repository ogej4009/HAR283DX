#pragma once
#include <HMGR.h>
#include "HVBBUFFER.h"
#include "HIBBUFFER.h"

// class HVBBUFFER;
// class HIBBUFFER;
class HMESH : public HMGR<HMESH>
{
private:
	unsigned int m_InstancedRenderCount;
	D3D_PRIMITIVE_TOPOLOGY m_DrawType;

public:
	void InstancedRenderCount(unsigned int _InstancedRenderCount)
	{
		m_InstancedRenderCount = _InstancedRenderCount;
	}

	void DrawType(D3D_PRIMITIVE_TOPOLOGY _DrawType)
	{
		m_DrawType = _DrawType;
	}


public:
	static HPTR<HMESH> Create(const HGAMESTRING& _Name)
	{
		HPTR<HMESH> Mesh = CreateToInsert(_Name);
		Mesh->VB(_Name);
		Mesh->IB(_Name);

		return Mesh;
	}

	static HPTR<HMESH> Create(const HGAMESTRING& _Name, const HGAMESTRING& _VB, const HGAMESTRING& _IB)
	{
		HPTR<HMESH> Mesh = CreateToInsert(_Name);
		Mesh->VB(_VB);
		Mesh->IB(_IB);
		return Mesh;
	}


private:
	HPTR<HVBBUFFER> m_VB;
	HPTR<HIBBUFFER> m_IB;

public:
	HPTR<HVBBUFFER> VB() { return m_VB; }
	HPTR<HIBBUFFER> IB() { return m_IB; }

public:
	void VB(HPTR<HVBBUFFER> _VB);
	void IB(HPTR<HIBBUFFER> _IB);

public:
	void VB(const HGAMESTRING& _Name);
	void IB(const HGAMESTRING& _Name);

public:
	void Render();

public:
	HMESH();
	~HMESH();
};

