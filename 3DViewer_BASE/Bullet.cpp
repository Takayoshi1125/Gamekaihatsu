#include"SceneManager.h"
#include"AsoUtility.h"
#include"Unit.h"
#include "Bullet.h"

Bullet::Bullet(VECTOR pos, VECTOR angle)
{
	mPos = pos;
	mAngles = angle;
}

void Bullet::Init(void)
{
	bCnt = 0;
	mPos.y = 100.0f;

	mAnglesLocal = { 0.0f,(float)AsoUtility::Deg2Rad(180.0f),0.0f };

	VECTOR angle = mAngles;
	angle.x += mAnglesLocal.x;
	angle.y += mAnglesLocal.y;
	angle.z += mAnglesLocal.z;
}

void Bullet::Update(void)
{
	

	VECTOR angle = mAngles;
	angle.x += mAnglesLocal.x;
	angle.y += mAnglesLocal.y;
	angle.z += mAnglesLocal.z;

	

	float movePow = 5.0f;

	float rodRad = 0.0f;

	

	mPos.x += sinf(mAngles.y) * movePow;
	mPos.z += cosf(mAngles.y) * movePow;

	/*if (bCnt > RANGE)
	{
		
	}*/


	bCnt++;

}

void Bullet::Draw(void)
{
	DrawSphere3D(mPos, 20.0f, 10, 0xffffff, 0xffffff, true);
}

void Bullet::Release(void)
{
	
}
