#pragma once
#include<DxLib.h>
class SceneManager;
class Bullet;

class Unit
{
public:

	static constexpr float SPEED_ANIM = 20.0f;

	static constexpr float SPEED_ROT = 5.0f;

	static constexpr float SPEED_ROT_RAD = SPEED_ROT*(DX_PI_F/180.0f);

	Unit(SceneManager* manager);

	void Init(void);
	void Update(void);
	void Draw(void);


	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAngle(void);

private:

	SceneManager* mSceneManager;
	Bullet* mBullet;

	int mModel;

	VECTOR mPos;

	VECTOR mAngles;

	VECTOR mAnglesLocal;

	//アニメーションID
	int mAnimWalk;

	//アニメーションの総時間
	float mTimeTotalAnimWalk;

	//アニメーションの現在フレーム
	float mStepAnim;
};

