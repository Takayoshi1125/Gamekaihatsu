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
	//	//Zの方向
	//	//mPos.z += movePow;

	//	rad = AsoUtility::Deg2Rad(0.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;

	//}

	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	//Zの方向
	//	//mPos.z += (-movePow);

	//	rad = AsoUtility::Deg2Rad(180.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;
	//}

	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	//Zの方向
	//	//mPos.x += movePow;

	//	rad = AsoUtility::Deg2Rad(90.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;
	//}

	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	//Zの方向
	//	//mPos.x += (-movePow);

	//	rad = AsoUtility::Deg2Rad(-90.0f);
	//	mPos.x += sinf(mAngles.y + rad) * movePow;
	//	mPos.z += cosf(mAngles.y + rad) * movePow;
	//}

	if (CheckHitKey(KEY_INPUT_N))
	{
		//Zの方向
		mPos.y += movePow;
	}

	if (CheckHitKey(KEY_INPUT_M))
	{
		//Zの方向
		mPos.y += (-movePow);
	}

	//カメラ回転
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//右回転
		mAngles.y += AsoUtility::Deg2Rad(1.0f);
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		//左回転
		mAngles.y += AsoUtility::Deg2Rad(-1.0f);
	}

	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	//上回転
	//	mAngles.x += AsoUtility::Deg2Rad(-1.0f);
	//}

	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	//下回転
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

		//注視点制御
		//-------------------------------------------
		mTargetPos = mUnit->GetPos();

		//カメラの向いている方向を取得
		dirX = sin(mAngles.y);
		dirZ = cos(mAngles.y);
		

		//念のため、方向に力の成分が入らないように単位ベクトルを取得
		dir = VNorm({ dirX,0.0f,dirZ });
		//単位ベクトルに距離を掛け合わせ、XZ移動量を算出
		movePow = VScale(dir, DIS_TARGET_TO_UNIT);


		//更にY（カメラの高さ）を足すことで、注視点からのカメラの相対位置を産出
		//movePow = VAdd(movePow, { 0.0f,HEIGHT,0.0f });

		mTargetPos = VAdd(mUnit->GetPos(), movePow);
		mTargetPos.y = 0.0f;
		//--------------------------------------


		//カメラの移動
		float revRad = AsoUtility::Deg2Rad(180.0f);

		////カメラの向いている方向を取得
		//dirX = sin(mAngles.y );
		//dirZ = cos(mAngles.y );
		//カメラの向いている反対方向を取得
		dirX = sin(mAngles.y + revRad);
		dirZ =cos(mAngles.y + revRad);

		//念のため、方向に力の成分が入らないように単位ベクトルを取得
		dir = VNorm({ dirX,0.0f,dirZ });
		//単位ベクトルに距離を掛け合わせ、XZ移動量を算出
		movePow = VScale(dir, DIS_TARGET_TO_CAMERA);
		//更にY（カメラの高さ）を足すことで、注視点からのカメラの相対位置を産出
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
