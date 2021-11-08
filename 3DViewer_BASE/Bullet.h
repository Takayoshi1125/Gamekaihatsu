#pragma once
#include<DxLib.h>
class Bullet
{
public:
	static constexpr int RANGE = 300;

	Bullet(VECTOR pos,VECTOR angle);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	int bCnt;

	VECTOR mPos;

	VECTOR mAngles;

	VECTOR mAnglesLocal;
};

