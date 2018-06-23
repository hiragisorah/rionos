#pragma once

class GRAPHICSDLL_API Sprite2D
{
public:
	enum class CENTER_POSITION
	{
		K_LEFT_UP,
		K_LEFT_DOWN,
		K_RIGHT_UP,
		K_RIGHT_DOWN,
		K_CENTER
	};
	enum class TEXTURE_SIZE
	{
		K_RELATIVE,
		K_ABSOLUTE
	};
};