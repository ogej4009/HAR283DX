#pragma once
#include "HSHADER.h"
#include <HMGR.h>
#include <HPTR.h>

#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

class HTEXTURE : public HFILEMGR<HTEXTURE>
{
public:
	static HPTR<HTEXTURE> Load(const HGAMEFILE& _File)
	{
		HPTR<HTEXTURE> Res = CreateToInsertToFile(_File.FullPath());
		Res->Load();
		return Res;
	}

	static HPTR<HTEXTURE> Load(const HGAMESTRING& _Path)
	{
		HPTR<HTEXTURE> Res = CreateToInsertToFile(_Path);
		Res->Load();
		return Res;
	}

private:
	// ���̺귯������ �������ִ� ����ü
	DirectX::ScratchImage m_Img;
	D3D11_TEXTURE2D_DESC Desc; // �ؽ�ó ����
	ID3D11Resource* m_pTex; // �ؽ�ó �޸� ����

	ID3D11RenderTargetView* m_RTV; // �ؽ�ó ����Ÿ�� ����
	ID3D11DepthStencilView* m_DSV; // �ؽ�ó ����Ÿ�� ����

	// �� ������ �̿��ؼ� �־���� �Ѵ�.
	ID3D11ShaderResourceView* m_SRV; // �ؽ�ó ���̴� ���� ����

public:
	const D3D11_TEXTURE2D_DESC& TextDesc() 
	{
		return Desc;
	}

public:
	ID3D11DepthStencilView* DSV() {
		return m_DSV;
	}

	ID3D11RenderTargetView* RTV() {
		return m_RTV;
	}

public:
	HVECTOR Size();

public:
	HTEXTURE();
	~HTEXTURE();

public:
	// Ŀ������ �ؽ�ó�� ����� �־�� �Ѵ�.
	void Create(HVECTOR _Size, DXGI_FORMAT _Fmt, UINT _BindFlag, D3D11_USAGE _eUsage);
	void Create(D3D11_TEXTURE2D_DESC _Desc);
	void Create(ID3D11Texture2D* _BackBufferTex);

public:
	void Load();
	void Setting(SHADERTYPE _Type, unsigned int _Reg);
	void Reset(SHADERTYPE _Type, unsigned int _Reg);
	void SetPixel(void* _PixelData, int Size);
	float4 GetPixel(int2 _Pos);

	void SettingData();
};

