#pragma once
#include<DxLib.h>

class SceneManager;
class Unit;
class Enemy
{
public:
	static constexpr float VIEW_ANGLE = 30.0f;
	static constexpr float VIEW_RANGE = 300.0f;

	Enemy(SceneManager* manager,Unit* unit);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void Atack(void);

	VECTOR GetPos(void);
	VECTOR GetAngle(void);

	

private:
	SceneManager* mSceneManager;
	Unit* mUnit;

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


	//プレイヤーを発見
	bool mIsNotice;
};

