#pragma once
#include "HCAM.h"


class HRenderTarget;
class HBloomFilter : public HFilter
{
public:
	HPTR<HRENDERPLAYER> BloomCheckPlayer;
	HPTR<HRenderTarget> SmallTarget;
	HPTR<HRenderTarget> SmallTarget2;


	float4 SmallUvSize;
	HPTR<HRENDERPLAYER> BloomPlayer;
	

public:
	void Init(int _Len);

private:
	void DefferdMergePrevEffect() override;
	void CamMergeNextEffect() override;
};

