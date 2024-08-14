#include "HCBUFFER.h"
//
void HCBUFFER::Setting(SHADERTYPE _Type, unsigned int _Reg) 
{
	switch (_Type)
	{
	case SHADERTYPE::SHADER_VS:
		HGAMEDEVICE::MAINOBJ()->Context()->VSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_HS:
		HGAMEDEVICE::MAINOBJ()->Context()->HSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_DS:
		HGAMEDEVICE::MAINOBJ()->Context()->DSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_GS:
		HGAMEDEVICE::MAINOBJ()->Context()->GSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_PS:
		HGAMEDEVICE::MAINOBJ()->Context()->PSSetConstantBuffers(_Reg, 1, &m_pBuffer);
		break;
	case SHADERTYPE::SHADER_END:
		break;
	default:
		break;
	}
}

void HCBUFFER::Create(unsigned int _Size)
{
	m_BufferDesc.ByteWidth = _Size;
	m_BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC; // ��� ������ �޶�. ���� =�׷���ī�忡 ����
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (S_OK != HGAMEDEVICE::MAINOBJ()->Device()->CreateBuffer(&m_BufferDesc, nullptr, &m_pBuffer))
	{
		AMSG(L"������� ���ÿ� �����߽��ϴ�");
	}
}

void HCBUFFER::DataChange(void* _Data, unsigned int _Size)
{
	if (m_BufferDesc.ByteWidth != _Size)
	{
		AMSG(NAME() + L" ��������� ũ�Ⱑ �ٸ��ϴ�.");
	}
	// �������� �����̴ϱ� �װ� �ɱ��?
	// �׷���ī��� ���� m_pBuffer������ ������ �����Ұž�.
	// �׷���ī��� �������� ���ؼ�
	// ��Ƽ ������ ȯ���� ��츦 ����ؼ�
	// �̳༮�� ������ ������� ���ϰ� ���´�.
	// ���������
	HGAMEDEVICE::MAINOBJ()->Context()->Map(m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_SubData);
	memcpy_s(m_SubData.pData, m_BufferDesc.ByteWidth, _Data, m_BufferDesc.ByteWidth);
	// ������ ��ȯ���ش�.
	HGAMEDEVICE::MAINOBJ()->Context()->Unmap(m_pBuffer, 0);

}