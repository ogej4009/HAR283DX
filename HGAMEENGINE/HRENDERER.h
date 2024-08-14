#pragma once
#include "HTRANS.h"
#include "HMATERIAL.h"
#include "HMESH.h"
#include "HCBUFFER.h"
#include "HTEXTURE.h"
#include "HSAMPLER.h"
#include "HStructuredBuffer.h"
#include <set>


// 상수버퍼를 세팅해주는 기능
class HLight;
class CBUFFERSETTER
{
public:
	friend class HRENDERPLAYER;
	friend class HRENDERER;
public:
	CBUFFERMODE m_Mode;
	const SHADERDATA* m_Data;
	HPTR<HCBUFFER> m_RES;
	void* m_Value;

public:
	~CBUFFERSETTER() 
	{
		if (nullptr != m_Value && m_Mode == CBUFFERMODE::CB_NEW)
		{
			delete[] m_Value;
		}
	}
};

class TEXTURESETTER
{
public:
	friend class HRENDERPLAYER;
	friend class HRENDER;
public:
	const SHADERDATA* m_Data;
	HPTR<HTEXTURE> m_RES;
	bool IsOption;
};

class SAMPLERSETTER
{
public:
	friend class HRENDERPLAYER;
	friend class HRENDER;
public:
	const SHADERDATA* m_Data;
	HPTR<HSAMPLER> m_RES;
};

class STRUCTUREDSETTER
{
public:
	friend class HRENDERPLAYER;
	friend class HRENDER;
public:
	const SHADERDATA* m_Data;
	HPTR<HStructuredBuffer> m_RES;
};

#define BOOLTOINT(NAME)  \
public: \
	bool NAME; \
private: \
	bool NAME##Temp##[3]; \

// 자동세팅이라 이렇게 바꾸면
class RenderPlayerOption 
{
public:
	BOOLTOINT(IsDifTexture);
	BOOLTOINT(IsNormalTexture);
	BOOLTOINT(IsShadow);
	BOOLTOINT(IsAni);
	BOOLTOINT(IsDummy0);
	BOOLTOINT(IsDummy1);
	BOOLTOINT(IsDummy2);
	BOOLTOINT(IsDummy3);

public:
	float4 BasicColor;

public:
	RenderPlayerOption() 
	{
		IsDifTexture = false;
		IsNormalTexture = false;
		IsShadow = false;
		IsAni = false;
		BasicColor = HVECTOR::WHITE;
	}
};

class HMESH;
class HMATERIAL;
class HRENDERER;
class HRENDERPLAYER : public HGAMEREF, public HOnOffBase
{
	friend HRENDERER;

public:
	HRENDERER* m_Parent;

	RenderPlayerOption RenderOption;

	HPTR<HMESH> m_Mesh;
	HPTR<HMATERIAL> m_Mat;

private:
	// 아 상수버퍼가 있구나 내가 그걸 세팅하는 클래스를 만들께.
	// 6칸
	//   어떤쉐이더에       이런이름의  이 타입의 리소스를 세팅해주는
	std::map<HGAMESTRING, std::vector<CBUFFERSETTER>> m_CBUFFER;
	std::map<HGAMESTRING, std::vector<TEXTURESETTER>> m_TEXTURE;
	std::map<HGAMESTRING, std::vector<SAMPLERSETTER>> m_SAMPLER;
	std::map<HGAMESTRING, std::vector<STRUCTUREDSETTER>> m_STRUCTURED;

public:
	std::list<TEXTURESETTER*> AllTextureSetter(const HGAMESTRING& _SetterName);


public:
	HPTR<HMESH> MESH();
	HPTR<HMATERIAL> MATERIAL();

	void MESH(const HPTR<HMESH>& _Mesh);
	void MESH(const HGAMESTRING& _Name);
	void MATERIAL(const HGAMESTRING& _Name, bool _Push = true);

	HPTR<HTEXTURE> GetTEXTURE(const HGAMESTRING& _Name);
	void TEXTURE(const HGAMESTRING& _Name, const HPTR<HTEXTURE>& _Tex);
	void TEXTURE(const HGAMESTRING& _Name, const HGAMESTRING& _TexName);
	void SAMPLER(const HGAMESTRING& _Name, const HGAMESTRING& _SmpName);
	void CBUFFER(const HGAMESTRING& _Name, void* _Data, CBUFFERMODE _Mode);
	void STRUCTURED(const HGAMESTRING& _Name, const HPTR<HStructuredBuffer>& _Buffer);

	bool IsTEXTURE(const HGAMESTRING& _Name);
	bool IsSAMPLER(const HGAMESTRING& _Name);
	bool IsCBUFFER(const HGAMESTRING& _Name);
	bool IsSTRUCTURED(const HGAMESTRING& _Name);

public:
	void Render();
	void Reset();
};


// 뭐든지 랜더할수 있는 기반을 다져줘야 한다.
// 애만으로 모든 랜더가 가능해야 한다.
// 여러분들이 불편하면 상속을 내리는 거다.
class HCAM;
class HMESH;
class HMATERIAL;
class HRENDERER : public HTRANS
{
private:
public:
	std::vector<HPTR<HRENDERPLAYER>> m_PlayerList;

	std::vector<HPTR<HRENDERPLAYER>> m_DefferdList;
	std::vector<HPTR<HRENDERPLAYER>> m_ForwardList;
	std::vector<HPTR<HRENDERPLAYER>> m_ShadowList;

public:
	// GetRenderPlayer();

public:
	void Init(int _Order = 0);
	void Init(const HGAMESTRING& _Mesh, const HGAMESTRING& _Mat, int _Order = 0);
	void Init(const HPTR<HMESH>& _Mesh, const HGAMESTRING& _Mat, int _Order = 0);

	virtual void Render(HPTR<HCAM> _Cam);
	virtual void DefferdRender(HPTR<HCAM> _Cam);
	virtual void ForwardRender(HPTR<HCAM> _Cam);
	virtual void ShadowRender(const LightData& _Data);


	HPTR<HRENDERPLAYER> CreateRenderPlayer(const HPTR<HMESH>& _Mesh, const HGAMESTRING& _Mat);
	HPTR<HRENDERPLAYER> CreateRenderPlayer(const HGAMESTRING& _Mesh, const HGAMESTRING& _Mat);
	HPTR<HRENDERPLAYER> CreateRenderPlayer(const HPTR<HMESH>& _Mesh);

	HPTR<HRENDERPLAYER> GetRenderPlayer(int _Index);

	void TEXTURE(const HGAMESTRING& _Name, const HPTR<HTEXTURE>& _Res);
	void TEXTURE(const HGAMESTRING& _Name, const HGAMESTRING& _ResName);
	void CBUFFER(const HGAMESTRING& _Name, void* _Data, CBUFFERMODE _Mode = CBUFFERMODE::CB_LINK);
	void SAMPLER(const HGAMESTRING& _Name, const HGAMESTRING& _ResName);


	std::vector<HPTR<HRENDERPLAYER>> CreateRenderPlayerToFbxEx(const HGAMESTRING& _FbxExName, const HGAMESTRING& _MatName, int DrawSet = 0);
	HPTR<HRENDERPLAYER> CreateRenderPlayerToFbxPartEx(const HGAMESTRING& _FbxExName, const HGAMESTRING& _MatName, int DrawSet, int _SubIndex, int _MainIndex);

	std::vector<HPTR<HRENDERPLAYER>> CreateRenderPlayerToFbx(const HGAMESTRING& _FbxName, const HGAMESTRING& _MatName, const HGAMESTRING& _SmpName);

	// 메테리얼만 세팅되지 않은
	// 여러분들이 메테리얼을 세팅해줘야 합니다.
	std::vector<HPTR<HRENDERPLAYER>> CreateRenderPlayerToFbxNoneMat(const HGAMESTRING& _FbxName);

	void ShadowOn();

public:
	HRENDERER();
	~HRENDERER();
};
