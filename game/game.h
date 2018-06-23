#pragma once

#ifdef _GAMEDLL
#define GAMEDLL_API __declspec(dllexport)
#else
#define GAMEDLL_API __declspec(dllimport)
#endif

class GAMEDLL_API Game
{
public:
	virtual bool Initalize(void);
	virtual bool Run(void);
	virtual void Finalize(void);
};