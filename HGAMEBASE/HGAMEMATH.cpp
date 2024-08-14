#include "HGAMEMATH.h"

const float HGAMEMATH::PI = 3.14159265358979323846264338f;
const float HGAMEMATH::PI2 = 3.14159265358979323846264338f * 2;
const float HGAMEMATH::PI2D1 = 3.14159265358979323846264338f * 0.5f;
const float HGAMEMATH::DTOR = HGAMEMATH::PI / 180.0f;
const float HGAMEMATH::RTOD = 180.0f / HGAMEMATH::PI;

int HGAMEMATH::RandomInt(int _Min, int _Max) 
{
    static std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(_Min, _Max);

    return dis(gen);
}
float HGAMEMATH::RandomFloat(float _Min, float _Max) 
{
    static std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(_Min, _Max);

    return dis(gen);
}


const HVECTOR HVECTOR::WHITE = { 1.0F, 1.0F, 1.0f, 1.0f };
const HVECTOR HVECTOR::BLUE = { 0.0F, 0.0F, 1.0f, 1.0f };
const HVECTOR HVECTOR::BLACK = { 0.0F, 0.0F, 0.0f, 1.0f };
const HVECTOR HVECTOR::RED = { 1.0F, 0.0F, 0.0f, 1.0f };
const HVECTOR HVECTOR::GREEN = { 0.0F, 1.0F, 0.0f, 1.0f };
const HVECTOR HVECTOR::MAGENTA = { 1.0F, 0.0F, 1.0f, 1.0f };

const HVECTOR HVECTOR::NONE = { 0.0F, 0.0F, 0.0f, 0.0f };
const HVECTOR HVECTOR::ZERO = { 0.0F, 0.0F, 0.0f, 1.0f };
const HVECTOR HVECTOR::ONE = { 1.0F, 1.0F, 1.0f, 1.0f };


const HVECTOR HVECTOR::RIGHT = { 1.0F, 0.0F };
const HVECTOR HVECTOR::LEFT = { -1.0F, 0.0F };
const HVECTOR HVECTOR::UP = { 0.0F, 1.0F };
const HVECTOR HVECTOR::DOWN = { 0.0F, -1.0F };
const HVECTOR HVECTOR::FORWARD = { 0.0F, 0.0F, 1.0f };
const HVECTOR HVECTOR::BACK = { 0.0F, 0.0F, -1.0f };

HVECTOR& HVECTOR::operator*=(const HMATRIX& _Value)
{
	HVECTOR NewResult;

	DXVEC = DirectX::XMVector4Transform(DXVEC, _Value);
	return *this;
}


HVECTOR HVECTOR::operator*(const HMATRIX& _Value)
{
	HVECTOR NewResult;

	for (size_t x = 0; x < 4; x++)
	{
		NewResult.Arr2D[0][x] = 0.0f;
		for (size_t CalCount = 0; CalCount < 4; CalCount++)
		{
			NewResult.Arr2D[0][x] += Arr2D[0][CalCount] * _Value.Arr2D[CalCount][x];
		}
	}

	return NewResult;
}



HVECTOR HVECTOR::MatrixToQuaternion(const HMATRIX& M) 
{
    HVECTOR Return;

    if (M.ArrV[0].IsNearlyZero() || M.ArrV[1].IsNearlyZero() || M.ArrV[2].IsNearlyZero())
    {
        Return.x = 0.0f;
        Return.y = 0.0f;
        Return.z = 0.0f;
        Return.w = 1.0f;
        return Return;
    }

    float	s;

    // Check diagonal (trace)
    const float tr = M.Arr2D[0][0] + M.Arr2D[1][1] + M.Arr2D[2][2];

    if (tr > 0.0f)
    {
        float InvS = InvSqrt(tr + 1.f);
        Return.w = 0.5f * (1.f / InvS);
        s = 0.5f * InvS;

        Return.x = (M.Arr2D[1][2] - M.Arr2D[2][1]) * s;
        Return.y = (M.Arr2D[2][0] - M.Arr2D[0][2]) * s;
        Return.z = (M.Arr2D[0][1] - M.Arr2D[1][0]) * s;
    }
    else
    {
        // diagonal is negative
        int i = 0;

        if (M.Arr2D[1][1] > M.Arr2D[0][0])
            i = 1;

        if (M.Arr2D[2][2] > M.Arr2D[i][i])
            i = 2;

        static const int nxt[3] = { 1, 2, 0 };
        const int j = nxt[i];
        const int k = nxt[j];

        s = M.Arr2D[i][i] - M.Arr2D[j][j] - M.Arr2D[k][k] + 1.0f;

        float InvS = InvSqrt(s);

        float qt[4];
        qt[i] = 0.5f * (1.f / InvS);

        s = 0.5f * InvS;

        qt[3] = (M.Arr2D[j][k] - M.Arr2D[k][j]) * s;
        qt[j] = (M.Arr2D[i][j] + M.Arr2D[j][i]) * s;
        qt[k] = (M.Arr2D[i][k] + M.Arr2D[k][i]) * s;

        Return.x = qt[0];
        Return.y = qt[1];
        Return.z = qt[2];
        Return.w = qt[3];
    }

    return Return;
}