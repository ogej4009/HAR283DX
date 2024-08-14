#pragma once
#include "HGAMERES.h"
#include "HGAMEDEVICE.h"
#include <vector>
#include "HRENDERER.h"

struct MergeOption
{
	float AlphaOption;
	float Dummy00;
	float Dummy01;
	float Dummy02;
};

class HTEXTRUE;
class HRenderTarget : public HMGR<HRenderTarget>
{
public:
	friend HGAMEDEVICE;

private:
	static void Init();

private:
	static HRENDERPLAYER TargetMergePlayer;
	static HRENDERPLAYER TargetPlusPlayer;


private:
	std::vector<HPTR<HTEXTURE>> m_AllTexture;
	std::vector<HVECTOR> m_ClearColor;
	std::vector<D3D11_VIEWPORT> m_VIEWPORT;
	std::vector<bool> m_Clear;
	// T * 
	// ID3D11RenderTargetView**
	// ID3D11RenderTargetView**
	std::vector<ID3D11RenderTargetView*> m_AllRTV;

	HPTR<HTEXTURE> m_Depth;

	MergeOption Option;

	void CreateViewPort(D3D11_TEXTURE2D_DESC _Desc);

public:
	HPTR<HTEXTURE> Texture(int _index) 
	{
		return m_AllTexture[_index];
	}

	void Clear(bool _IsDepthClear); // ��� ����� �Ǵ°�.
	void Setting(); // ��� ����� �Ǵ°�.


	void Reset(); // ��� ����� �Ǵ°�.


	void CreateDepth(unsigned int _TargetIndex = 0);

	void Setting(int _Index); // ��� ����� �Ǵ°�.

	void Depth(HPTR<HTEXTURE> _Depth);

	HPTR<HTEXTURE> Depth();


public:
	// �����ϰ� ���� ���鶧.
	void CreateTarget(HVECTOR _Size,  HVECTOR _ClearColor, bool _Clear = true, DXGI_FORMAT _Fmt = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, unsigned int _BindFlag = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);

	// ����۰� ���.
	void CreateTarget(ID3D11Texture2D* _BackBufferTex, HVECTOR _ClearColor, bool _Clear);

	// �ٸ� Ÿ���� Ÿ���� �������� ����.
	void CreateTarget(HPTR<HTEXTURE> _Target, HVECTOR _ClearColor, bool _Clear);

	void Merge(HPTR<HRenderTarget> _Target, int _ThisIndex = 0, int _OtherIndex = 0, bool _AlphaOption = false);
	void Plus(HPTR<HRenderTarget> _Target, int _ThisIndex = 0, int _OtherIndex = 0, bool _AlphaOption = false);

public:
	HRenderTarget();
	~HRenderTarget();
};

