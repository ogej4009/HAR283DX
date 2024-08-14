#pragma once
#include "HGAMECOM.h"
#include "HFbxEx.h"

// �ؽ�ó�� ����?
// FLOAT���� �̷���� 2���� �迭�̴�.

// 512 512 / 16

// ������ �ƴϴ�.
// �������� ���ο��� �������
// ���� �÷��̾ ������̴�.
// �����÷��̾�� �Ž��� ���׸���
// �ִϸ��̼� �Ҷ� � �ִϸ��̼ǿ��� � ȿ���� �ַ���
// ���׸����� �ٲ��� �Ѵ�.
// �����÷��̾ �ִϸ��̼Ǹ��� �޶��
// �Ѵٴ� �̾߱�ų�
// �� �ִϸ��̼��� �����Ҷ�
// ���׸����� �ٲ�
// ���׸����� ������ �ִ� �÷��̾ ������ ���� �����̴�.
class HTEXTURE;
class HRENDERER;
class HBoneAnimationComEx : public HACTORCOM
{
public:
	// 500 �����ӿ��� 501 ������ �� 0.3������ ���� ������ ��³༮.
	// 550 ~~~~~~�������~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 551
	// 0            0.2                                 1

	// ũ�� 
	// ���

	// ���� �����ӿ����� ���� �� ���¸� ������ �༮.
	class BONEFRAMEDATA
	{
	public:
		HMATRIX AniMat;
		HMATRIX AniWorldMat;
		HVECTOR AniScale;
		HVECTOR AniPos;
		HVECTOR AniEuler;
		HVECTOR AniQ;

		HVECTOR Scale;
		HVECTOR Pos;
		HVECTOR Euler;
		HVECTOR Q;
	};

	// 2D�� �ִϸ��̼��̶� ������ �ٸ��� ����.
	// ���� ��� �ȴ´�.
	// 1434 500 550
public:
	class MESHANI : public HGAMEREF
	{
	public:
		HBoneAnimationComEx* m_MeshAni;
		HFbxEx* m_AniFbx;
		HFbxExAniData* m_AniData;
		int m_Start;
		int m_End;

		HGAMESTRING m_Name;

		float m_CurAniTime;
		float m_StartTime;
		float m_EndTime;

		float m_Speed;
		float m_CurTime;
		bool m_Loop;

		int m_CurFrame;
		int m_NextFrame;

		// ������ �Ŵ°��� �����Ѵ�.
		// 134
		// �ظ��� ��쿡�� 134
		// �����ִ� �� �ؽ�ó�� �������� ��.
		HTEXTURE* m_BoneTex; // = new CreateTEXTURE; �̷��� ���Ѵ�.

		// ���� ���
		std::vector<BONEFRAMEDATA> FrameBoneData;
		std::vector<HMATRIX> FrameMatData;
		// std::vector<HPTR<HRENDERPLAYER>> m_RenderPlayerList;

	public:
		bool IsEnd();

	public:
		// ���ӳ����� �̰� ������ 
		// �������� ����� ����̴�
		void SetStartFrame(int _Frame);
		void SetEndFrame(int _Frame);

	public:
		// �ִϸ��̼��� ���� �ʱ� ���·� ������ �Լ�.
		void Reset();
		void Update();  // �����Ӱ�� 502 ����ϰ�
		void UpdateNext(); // ����� 502�������� ������ ���⼭ ����Ѵ�.
	};
	friend MESHANI;

private:
	std::vector<BONEFRAMEDATA> FrameBoneData;
	std::vector<HMATRIX> FrameMatData;
	std::vector<std::vector<HPTR<HRENDERPLAYER>>> m_RenderPlayerList;
	HPTR<HTEXTURE> m_BoneTex; // ��� �ֵ鿡�� �����ִ� �ؽ�ó

	HPTR<HRENDERER> m_Render;
	HPTR<MESHANI> m_CurAni;
	bool m_IsPlay;
	HFbxEx* m_MainFbx;

	std::map<HGAMESTRING, HPTR<MESHANI>> m_AllAni;

public:
	HPTR<MESHANI> FindAni(const HGAMESTRING& _Ani);

	bool IsPlay() {
		return m_IsPlay;
	}

	void Play()
	{
		m_IsPlay = true;
	}

	void Stop()
	{
		m_IsPlay = false;
	}

	void PlayChange()
	{
		m_IsPlay = !m_IsPlay;
	}

public:
	HPTR<MESHANI> CurAni()
	{
		return m_CurAni;
	}

	void SetCurFrame(int _Frame);

public:
	// �������� �ٲ�
	void ChangeAni(const HGAMESTRING& _AniName);

	std::vector<HPTR<HRENDERPLAYER>> MainFbx(const HGAMESTRING& _Fbx, const HGAMESTRING& _Mat, int _DrawSetIndex);
	HPTR<HRENDERPLAYER> FbxToPartRenderPlayer(const HGAMESTRING& _Fbx, const HGAMESTRING& _Mat, int _DrawSetIndex, int _PushListIndex, int _MainIndex, int _SubIndex);

	void CreateAni
	(
		const HGAMESTRING& _AniFbx, 	// Monster_Run.Fbx
		const HGAMESTRING& _AniName,	// Run
		int _Start = -1,						// ������
		int _End = -1,						// ������
		int _TakeIndex = 0,					// 0
		float _Speed = 1.0f,				// �ӷ�����
		bool _Loop = true					// ����
	);

public:
	void Init() override;
	void Update() override;
	void UpdateNext() override;

};

