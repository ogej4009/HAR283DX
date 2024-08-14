#pragma once
#include "HGAMESTRING.h"

class HGAMENAME
{
private:
	HGAMESTRING m_Name;

public:
	HGAMESTRING NAME() 
	{
		return m_Name;
	}

	void NAME(const HGAMESTRING& _Name) 
	{
		m_Name = _Name;
	}

public:
	HGAMENAME() {}
	virtual ~HGAMENAME() {}
};

