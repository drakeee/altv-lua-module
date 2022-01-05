#pragma once

#include <Main.h>

struct LRGBA : public alt::RGBA
{
	LRGBA() = default;
	LRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :
		alt::RGBA(_r, _g, _b, _a)
	{

	}

	int GetColor(void)
	{
		return ((this->a << 24) | (this->r << 16) | (this->g << 8) | this->b);
	}
};