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

	//�A�j���[�V����ID
	int mAnimWalk;

	//�A�j���[�V�����̑�����
	float mTimeTotalAnimWalk;

	//�A�j���[�V�����̌��݃t���[��
	float mStepAnim;


	//�v���C���[�𔭌�
	bool mIsNotice;
};

