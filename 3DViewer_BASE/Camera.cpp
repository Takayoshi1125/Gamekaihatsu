#include<DxLib.h>
#include"AsoUtility.h"
#include"Unit.h"
#include "Camera.h"

Camera::Camera()
{
}

void Camera::Init(void)
{
	mPos = { 0.0f,HEIGHT,-DIS_TARGET_TO_CAMERA };
	mAngles = {
		(float)AsoUtility::Deg2Rad(30.0f),
		0.0f,
		0.0f
	};
}

void Camera::Update(void)
{
	float movePow = 5.0f;

	float rad = 0.0f;

	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	//Z�̕���
	//	//mPos.z += movePow;

	//	rad = AsoUtility::Deg2Rad(0.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;

	//}

	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	//Z�̕���
	//	//mPos.z += (-movePow);

	//	rad = AsoUtility::Deg2Rad(180.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;
	//}

	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	//Z�̕���
	//	//mPos.x += movePow;

	//	rad = AsoUtility::Deg2Rad(90.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;
	//}

	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	//Z�̕���
	//	//mPos.x += (-movePow);

	//	rad = AsoUtility::Deg2Rad(-90.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;
	//}

	if (CheckHitKey(KEY_INPUT_N))
	{
		//Z�̕���
		mPos.y += movePow;
	}

	if (CheckHitKey(KEY_INPUT_M))
	{
		//Z�̕���
		mPos.y += (-movePow);
	}

	//�J������]
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//�E��]
		mAngles.y += AsoUtility::Deg2Rad(1.0f);
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		//����]
		mAngles.y += AsoUtility::Deg2Rad(-1.0f);
	}

	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	//���]
	//	mAngles.x += AsoUtility::Deg2Rad(-1.0f);
	//}

	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	//����]
	//	mAngles.x += AsoUtility::Deg2Rad(1.0f);
	//}

}

void Camera::SetBeforeDraw(void)
{
	if (mUnit == nullptr)
	{
		SetCameraPositionAndAngle(
			mPos, mAngles.x, mAngles.y, mAngles.z);
	}
	else
	{
		float dirX;
		float dirZ;
		VECTOR dir;
		VECTOR movePow;

		//�����_����
		//-------------------------------------------
		mTargetPos = mUnit->GetPos();

		//�J�����̌����Ă���������擾
		dirX = sin(mAngles.y);
		dirZ = cos(mAngles.y);
		

		//�O�̂��߁A�����ɗ͂̐���������Ȃ��悤�ɒP�ʃx�N�g�����擾
		dir = VNorm({ dirX,0.0f,dirZ });
		//�P�ʃx�N�g���ɋ������|�����킹�AXZ�ړ��ʂ��Z�o
		movePow = VScale(dir, DIS_TARGET_TO_UNIT);


		//�X��Y�i�J�����̍����j�𑫂����ƂŁA�����_����̃J�����̑��Έʒu���Y�o
		//movePow = VAdd(movePow, { 0.0f,HEIGHT,0.0f });

		mTargetPos = VAdd(mUnit->GetPos(), movePow);
		mTargetPos.y = 0.0f;
		//--------------------------------------


		//�J�����̈ړ�
		float revRad = AsoUtility::Deg2Rad(180.0f);

		////�J�����̌����Ă���������擾
		//dirX = sin(mAngles.y );
		//dirZ = cos(mAngles.y );
		//�J�����̌����Ă��锽�Ε������擾
		dirX = sin(mAngles.y + revRad);
		dirZ =cos(mAngles.y + revRad);

		//�O�̂��߁A�����ɗ͂̐���������Ȃ��悤�ɒP�ʃx�N�g�����擾
		dir = VNorm({ dirX,0.0f,dirZ });
		//�P�ʃx�N�g���ɋ������|�����킹�AXZ�ړ��ʂ��Z�o
		movePow = VScale(dir, DIS_TARGET_TO_CAMERA);
		//�X��Y�i�J�����̍����j�𑫂����ƂŁA�����_����̃J�����̑��Έʒu���Y�o
		movePow = VAdd(movePow, {0.0f,HEIGHT,0.0f});

		mPos = VAdd(mTargetPos, movePow);

		SetCameraPositionAndTargetAndUpVec(
			mPos, mTargetPos, { 0.0f,1.0f,0.0f }
		);
	}
	
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

void Camera::SetUnit(Unit* unit)
{
	mUnit = unit;
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetAngles(void)
{
	return mAngles;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}

VECTOR Camera::Relese(void)
{
	return VECTOR();
}
