#pragma once
#include "HDEVICEBUFFER.h"
#include "HSHADER.h"

class HStructuredBuffer : public HMGR<HStructuredBuffer>, public HDEVICEBUFFER
{
private:
	ID3D11ShaderResourceView* m_SRV;
	ID3D11UnorderedAccessView* m_UAV;
	unsigned int m_iElementSize;
	unsigned int m_iElementCount;

public:
	void Create(UINT _iElementSize, UINT _iElementCount, void* _pSysMem, D3D11_USAGE _eUsage = D3D11_USAGE_DEFAULT);
	void UpdateDataRW(UINT _iRegisterNum);
	void SetData(void* _pData, UINT _iSizeOfByte);

	void Setting(SHADERTYPE _Type, unsigned int _Reg);
public:
	static void Reset(UINT _iRegisterNum);
	static void ClearRW(UINT _iRegisterNum);

public:
	HStructuredBuffer();
	virtual ~HStructuredBuffer();
};

