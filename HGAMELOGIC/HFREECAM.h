#pragma once
#include <HGAMECOM.h>
#include <set>

#pragma comment(lib, "HGAMEBASE.lib")
#pragma comment(lib, "HGAMEENGINE.lib")

class HCAM;
class HFREECAM : public HACTORCOM
{

public:
	HPTR<HCAM> m_Cam;
	float m_Speed;
	float m_RotSpeed;

public:
	//HFREECAM() 
	//{
	//  m_Cam->addref
	//}
	//~HFREECAM();
	HFREECAM();
	~HFREECAM();

public:
	// ķ�� ȸ��
	void Init(float _Speed);
	void Update() override;


};

