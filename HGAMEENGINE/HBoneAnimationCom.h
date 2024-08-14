#pragma once
#include "HGAMECOM.h"
#include "HFBX.h"

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
class HBoneAnimationCom : public HACTORCOM
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
		HBoneAnimationCom* m_MeshAni;
		HFBX* m_Fbx;
		HFBXANIDATA* m_AniData;
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
		std::vector<BONEFRAMEDATA> FrameBoneData;

		// ������ �Ŵ°��� �����Ѵ�.
		// 134
		// �ظ��� ��쿡�� 134
		// �����ִ� �� �ؽ�ó�� �������� ��.
		HPTR<HTEXTURE> m_BoneTex; // = new CreateTEXTURE; �̷��� ���Ѵ�.

		// ���� ���
		std::vector<HMATRIX> FrameMatData;
		std::vector<HPTR<HRENDERPLAYER>> m_RenderPlayerList;

	public:
		bool IsEnd();

	public:
		// ���ӳ����� �̰� ������ 
		// �������� ����� ����̴�
		void SetStartFrame(int _Frame);
		void SetEndFrame(int _Frame);

	public:
		// �ִϸ��̼��� ���� �÷��̾ ��� ���� ���
		void RDOFF();
		void RDON();

	public:
		// �ִϸ��̼��� ���� �ʱ� ���·� ������ �Լ�.
		void Reset();
		void Update();  // �����Ӱ�� 502 ����ϰ�
		void UpdateNext(); // ����� 502�������� ������ ���⼭ ����Ѵ�.
	};
	friend MESHANI;

private:
	HPTR<HRENDERER> m_Render;
	HPTR<MESHANI> m_CurAni;
	bool m_IsPlay;

	// ���� �����ٰ��̴�.
	//       FBX 134
	std::map<HGAMESTRING, HPTR<HTEXTURE>> m_AniBoneTex;
	//       ATTECT
	//       DEF
	std::map<HGAMESTRING, std::vector<HPTR<HRENDERPLAYER> >> m_AllRenderPlayer;

	//       ATTECT
	//       DEF
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

	std::list<HPTR<HRENDERPLAYER>> CreateAni(
		const HGAMESTRING& _Fbx, 		 // const HGAMESTRING& _Fbx				Monster03.fbx ����
		const HGAMESTRING& _TakeName,	 // const HGAMESTRING& _TakeName 		Take 001�� 1434
		const HGAMESTRING& _AniName,	 // const HGAMESTRING& _AniName 		Attack�� ������.
		int _Start,						 // 500
		int _End,						 // 580
		const HGAMESTRING& _MatName = L"3DANIFORWARD",	 // �� � ���׸���� ������ �ض�.
		float Speed = 1.0f,					// �ӷ�����
		bool Loop = false					// �ӷ�����
	);

public:
	void Init() override;
	void Update() override;
	void UpdateNext() override;

};

