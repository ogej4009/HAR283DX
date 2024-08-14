#pragma once
#include <HGAMELOGIC.h>

class MeshCreateData
{
public:
	HGAMESTRING m_MeshName;
	HGAMESTRING m_TakeName;
	HVECTOR m_Scale;
	HVECTOR m_Pos;
	HVECTOR m_Rot;
};

class HGAMEACTOR;
class HBoneAnimationCom;
class HHeightMap;
class HTOOLMAPSCENE : public HSCENECOM
{
public:
	static HTOOLMAPSCENE* Inst;
	static HBoneAnimationCom* AniCom;
	HPTR<class HOutLineFilter> m_LineFilter;
	HPTR<class HBloomFilter> m_BloomFilter;

public:
	HPTR<HGAMEACTOR> TestActor;
	HPTR<HGAMEACTOR> LightTest;
	HPTR<HGAMEACTOR> PlayerActor;
	HPTR<HHeightMap> Map;
	HPTR<HLight> LightCom;

public:
	void CreateFBXObject(MeshCreateData _FbxObjectData);
	void PlayerUpdate();

public:
	HTOOLMAPSCENE();
	~HTOOLMAPSCENE();

public:
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void Init() override;
	void Update() override;
};