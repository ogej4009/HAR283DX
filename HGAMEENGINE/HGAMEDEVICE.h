#pragma once
#include <HGAMEMATH.h>
#include <HGAMEDEBUG.h>

#include <HPTR.h>
#include <HMGR.h>
#include <HGAMEWINDOW.h>



#pragma comment(lib, "HGAMEBASE.lib")

// � �����쿡 3Dȭ���� ���ǵ� �װ� ���ؼ�
// �׷���ī�带 ���Ŵϱ� �� ������ ������ ��. 
// �׷��� ī�带 ���� �ִ� ���ٱ����� ������ �ֶ�� ����
class HRenderTarget;
class HGAMEDEVICE : public HFOBJMGR<HGAMEDEVICE>
{
public:
	static bool bDefResInit;

	static HPTR<HGAMEDEVICE> Create(const HGAMESTRING& _Window)
	{
		HPTR<HGAMEDEVICE> DEVICE = CreateToInsert(_Window);
		DEVICE->Init(HGAMEWINDOW::Find(_Window));
		return DEVICE;
	}

private:
	HPTR<HGAMEWINDOW> m_WINDOW;

	// �ɼ��� �� ������ڴ�. = true
	UINT m_MC;
	UINT m_MQ;
	HVECTOR m_Color;					// �ʱ�ȭ ����. 
	ID3D11Device*		  m_pDevice;	// �׷���ī���� �޸𸮸� ����Ѵ�. �׷��� ī���� �޸𸮸� ���� �� �Ҵ� �����ϴ�. �ε�
	ID3D11DeviceContext*  m_pContext;	// �׷���ī���� ������ ����Ѵ�. ������

	// ����ü�� ���̷�Ʈ�� ȭ���� ����ϴ� �ý����� ������
	// ��Ⱑ Ư���� ���� ������. 
	IDXGISwapChain*			m_pSwapChain;	// ȭ���� Ŭ����� ����� ����Ѵ�.(ex) api ���� ���۸�)
	HPTR<HRenderTarget>		m_BackBufferRenderTarget;
	HPTR<HRenderTarget>		m_UserDataTarget;

public:
	HPTR<HRenderTarget> BackBufferRenderTarget();
	HPTR<HRenderTarget> DataRenderTarget();



public:
	ID3D11Device* Device() {
		return m_pDevice;	
	}
	ID3D11DeviceContext* Context() {
		return m_pContext;
	}

public:
	HGAMEDEVICE();
	~HGAMEDEVICE();

public:
	void CreateSwapChain();
	void CreateBackBufferTarget();

public:
	void RenderStart();
	void RenderEnd();

	void MESHINIT();
	void MATERIALINIT();
	void SHADERINIT();
	void RASTERIZERINIT();
	void DEPTHINIT();
	void BLENDINIT();
	void SAMPLERINIT();

	static void Reset();

private:
	void Init(const HPTR<HGAMEWINDOW>& _Window);

};
