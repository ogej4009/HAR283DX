#include "HStructuredBuffer.h"

HStructuredBuffer::HStructuredBuffer() 
	:	m_SRV(nullptr),
	m_UAV(nullptr),
	m_iElementSize(0),
	m_iElementCount(0)
{

}
HStructuredBuffer::~HStructuredBuffer() 
{
	if (nullptr == m_SRV)
	{
		m_SRV->Release();
	}
	if (nullptr == m_UAV)
	{
		m_UAV->Release();
	}
}

void HStructuredBuffer::Create(UINT _iElementSize, UINT _iElementCount, void* _pSysMem, D3D11_USAGE _eUsage)
{
	// Create 재 호출 시, 기존 버퍼 해제 후 다시 생성
	m_iElementSize = _iElementSize;
	m_iElementCount = _iElementCount;

	m_BufferDesc.ByteWidth = m_iElementSize * m_iElementCount;
	m_BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	m_BufferDesc.StructureByteStride = _iElementSize;

	if (D3D11_USAGE_DYNAMIC == _eUsage)
	{
		m_BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		m_BufferDesc.Usage = _eUsage;
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	}


	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _pSysMem;

	if (nullptr != _pSysMem)
	{
		HGAMEDEVICE::MAINOBJ()->Device()->CreateBuffer(&m_BufferDesc, &tSub, &m_pBuffer);
	}
	else
	{
		HGAMEDEVICE::MAINOBJ()->Device()->CreateBuffer(&m_BufferDesc, nullptr, &m_pBuffer);
	}

	// SRV 만들기
	D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};

	tSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	tSRVDesc.BufferEx.FirstElement = 0;
	tSRVDesc.BufferEx.Flags = 0;
	tSRVDesc.BufferEx.NumElements = m_iElementCount;

	HRESULT Result = HGAMEDEVICE::MAINOBJ()->Device()->CreateShaderResourceView(m_pBuffer, &tSRVDesc, &m_SRV);

	if (S_OK != Result)
	{
		assert(nullptr);
	}

	if (m_BufferDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
	{
		// UAV 만들기
		D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};

		tUAVDesc.Format = DXGI_FORMAT_UNKNOWN;
		tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		tUAVDesc.Buffer.FirstElement = 0;
		tUAVDesc.Buffer.Flags = 0;
		tUAVDesc.Buffer.NumElements = m_iElementCount;

		Result = HGAMEDEVICE::MAINOBJ()->Device()->CreateUnorderedAccessView(m_pBuffer, &tUAVDesc, &m_UAV);

		if (Result != S_OK)
		{
			assert(nullptr);
		}
	}
}

void HStructuredBuffer::Setting(SHADERTYPE _Type, unsigned int _Reg)
{
	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		HGAMEDEVICE::MAINOBJ()->Context()->VSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_HS:
		HGAMEDEVICE::MAINOBJ()->Context()->HSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_DS:
		HGAMEDEVICE::MAINOBJ()->Context()->DSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_GS:
		HGAMEDEVICE::MAINOBJ()->Context()->GSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_PS:
		HGAMEDEVICE::MAINOBJ()->Context()->PSSetShaderResources(_Reg, 1, &m_SRV);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}

void HStructuredBuffer::UpdateDataRW(UINT _iRegisterNum)
{
	UINT i = -1;
	HGAMEDEVICE::MAINOBJ()->Context()->CSSetUnorderedAccessViews(_iRegisterNum, 1, &m_UAV, &i);
}

void HStructuredBuffer::SetData(void* _pData, UINT _iSizeOfByte)
{
	assert(m_BufferDesc.Usage == D3D11_USAGE_DYNAMIC);

	D3D11_MAPPED_SUBRESOURCE tSub = {};
	HGAMEDEVICE::MAINOBJ()->Context()->Map(m_pBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _pData, _iSizeOfByte);
	HGAMEDEVICE::MAINOBJ()->Context()->Unmap(m_pBuffer, 0);
}

void HStructuredBuffer::Reset(unsigned int _Reg)
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	HGAMEDEVICE::MAINOBJ()->Context()->VSSetShaderResources(_Reg, 1, &pSRV);
	HGAMEDEVICE::MAINOBJ()->Context()->HSSetShaderResources(_Reg, 1, &pSRV);
	HGAMEDEVICE::MAINOBJ()->Context()->CSSetShaderResources(_Reg, 1, &pSRV);
	HGAMEDEVICE::MAINOBJ()->Context()->DSSetShaderResources(_Reg, 1, &pSRV);
	HGAMEDEVICE::MAINOBJ()->Context()->GSSetShaderResources(_Reg, 1, &pSRV);
	HGAMEDEVICE::MAINOBJ()->Context()->PSSetShaderResources(_Reg, 1, &pSRV);
}

void HStructuredBuffer::ClearRW(UINT _iRegisterNum)
{
	ID3D11UnorderedAccessView* pUAV = nullptr;
	UINT i = -1;
	HGAMEDEVICE::MAINOBJ()->Context()->CSSetUnorderedAccessViews(_iRegisterNum, 1, &pUAV, &i);
}
