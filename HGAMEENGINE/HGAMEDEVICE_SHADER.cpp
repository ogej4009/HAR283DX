#include "HGAMEDEVICE.h"
#include <HGAMEIO.h>

#include "HVTXSHADER.h"
#include "HPIXSHADER.h"
#include "DEFVTXHEADER.h"

#include "HGAMEDEVICE.h"

#pragma warning( push )
#pragma warning( disable : 26444 )

void HGAMEDEVICE::SHADERINIT() 
{
	HGAMEDIRECTORY m_Dir;
	m_Dir.MoveParent(L"HAR283DX");
	m_Dir.Move(L"HSHADER");

	std::list<HGAMEFILE> File = m_Dir.DirAllFile(L"hlsl");

	for (auto& _Value : File)
	{
		// ���̴� ���� ���ο�
		// ��� �Լ��� ����ִ��� �˾ƾ� �ϰ�
		// + �װ� �Լ��� Ȯ���ϴٸ�
		// �ȼ����̴����� ���ؽ� ���̴������� �����Ҽ� �־�� �Ѵ�.

		HSHADER::AutoShaderCompile(_Value.FullPath());
	}

	//{
	//	HPTR<HVTXSHADER> VTX = HVTXSHADER::Load(m_Dir.PlusFileName(L"2DIMG.hlsl"), L"VS_2DIMG");
	//	VTX->AddLayout("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->AddLayout("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
	//	VTX->CreateLayout();
	//	HPIXSHADER::Load(m_Dir.PlusFileName(L"2DIMG.hlsl"), L"PS_2DIMG");
	//}
}

#pragma warning( pop )