#pragma once
#include "HSPRITERENDERER.h"
#include <map>

class HGAMEACTOR;
class HFRAMEANI : public HACTORCOM
{
public:
	HPTR<HSPRITERENDERER> m_SpriteRender;

public:
	void Init(HPTR<HSPRITERENDERER> _SpriteRender = nullptr);
	void Update() override;

private:
	class HFRAMEANIMATION : public HGAMEREF
	{
	public:
		HGAMEACTOR* Actor;
	 	HGAMESTRING m_AniName;
		HGAMESTRING m_SpriteName;
		unsigned int m_Start;
		unsigned int m_End;
		float m_FrameTime;
		bool m_Loop;

		unsigned int m_CurFrame;
		float m_CurFrameTime;

		std::map<unsigned int, std::list<std::function<void(HGAMEACTOR* _Actor)>>> m_StartFunc;
		std::map<unsigned int, std::list<std::function<void(HGAMEACTOR* _Actor)>>> m_EndFunc;

	public:
		void CheckStartFunc(unsigned int _Frame) 
		{
			if (m_StartFunc.end() == m_StartFunc.find(_Frame))
			{
				return;
			}

			for (auto& _Var : m_StartFunc[_Frame])
			{
				_Var(Actor);
			}
		}

		void CheckEndFunc(unsigned int _Frame)
		{
			if (m_EndFunc.end() == m_EndFunc.find(_Frame))
			{
				return;
			}

			for (auto& _Var : m_EndFunc[_Frame])
			{
				_Var(Actor);
			}
		}


	public:
		void Reset() {
			m_CurFrame = m_Start;
			m_CurFrameTime = m_FrameTime;
		}
	};

private:
	std::map<HGAMESTRING, HPTR<HFRAMEANIMATION>> m_Ani;
	HPTR<HFRAMEANIMATION> m_CurAni;

public:
	bool CurAniEnd() {
		return m_CurAni->m_CurFrame == m_CurAni->m_End;
	}

	unsigned int CurAniFrame() 
	{
		return m_CurAni->m_CurFrame;
	}


public:
	// 어떤 애니메이션 "IDLE"
	// 어떤 프레임     5
	template<typename T>
	void PushStartFunc(const HGAMESTRING& _AniName, unsigned int _Frame, T* _Obj, void(T::* _Ptr)(HGAMEACTOR*))
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		HPTR<HFRAMEANIMATION> pAni = FindAni(_AniName);

		if (nullptr == pAni)
		{
			AMSG(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}

		std::map<unsigned int, std::list<std::function<void(HGAMEACTOR* _Actor)>>>::iterator FindIter 
			= pAni->m_StartFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_StartFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_StartFunc[_Frame] = std::list<std::function<void(HGAMEACTOR* _Actor)>>();
			FindIter = pAni->m_StartFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1));
	}

	void PushStartFunc(const HGAMESTRING& _AniName, unsigned int _Frame, void(*_Ptr)(HGAMEACTOR*))
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		HPTR<HFRAMEANIMATION> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			AMSG(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}
		std::map<unsigned int, std::list<std::function<void(HGAMEACTOR* _Actor)>>>::iterator FindIter
			= pAni->m_StartFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_StartFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_StartFunc[_Frame] = std::list<std::function<void(HGAMEACTOR* _Actor)>>();
			FindIter = pAni->m_StartFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, std::placeholders::_1));
	}

	template<typename T>
	void PushEndFunc(const HGAMESTRING& _AniName, unsigned int _Frame, T* _Obj, void(T::* _Ptr)(HGAMEACTOR*))
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		HPTR<HFRAMEANIMATION> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			AMSG(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}
		std::map<unsigned int, std::list<std::function<void(HGAMEACTOR* _Actor)>>>::iterator FindIter
			= pAni->m_EndFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_EndFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_EndFunc[_Frame] = std::list<std::function<void(HGAMEACTOR* _Actor)>>();
			FindIter = pAni->m_EndFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, _Obj, std::placeholders::_1));
	}

	void PushEndFunc(const HGAMESTRING& _AniName, unsigned int _Frame, void(*_Ptr)(HGAMEACTOR*))
	{
		if (nullptr == _Ptr)
		{
			AMSG(L"nullptr인 함수를 넣어줬습니다. 실행할수 없습니다.");
		}

		HPTR<HFRAMEANIMATION> pAni = FindAni(_AniName);
		if (nullptr == pAni)
		{
			AMSG(L"존재하지 않는 애니메이션에 콜백을 넣을수 없습니다.");
		}
		std::map<unsigned int, std::list<std::function<void(HGAMEACTOR* _Actor)>>>::iterator FindIter
			= pAni->m_EndFunc.find(_Frame);

		// 먼저 저 프레임에 자료구조가 있는지 봐야한다.
		if (pAni->m_EndFunc.end() == FindIter)
		{
			// 없으면 그 프레임은 일단 만든다.
			// 무조건 만들어지게 된다.
			pAni->m_EndFunc[_Frame] = std::list<std::function<void(HGAMEACTOR* _Actor)>>();
			FindIter = pAni->m_EndFunc.find(_Frame);
		}

		FindIter->second.push_back(std::bind(_Ptr, std::placeholders::_1));
	}




private:
	HPTR<HFRAMEANIMATION> FindAni(const HGAMESTRING& _AniName);

public:
	void CreateAni(
		const HGAMESTRING& _AniName, 
		const HGAMESTRING& _SpriteName, 
		unsigned int _Start, 
		unsigned int _End, 
		float _FrameTime,
		bool _Loop);


	void ChangeAni(const HGAMESTRING& _AniName);

};

