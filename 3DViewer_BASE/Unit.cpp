#include"SceneManager.h"
#include"AsoUtility.h"
#include"Camera.h"
#include"Bullet.h"
#include "Unit.h"

Unit::Unit(SceneManager* manager)
{
	mSceneManager = manager;
}

void Unit::Init(void)
{
	mModel = MV1LoadModel("Model/Human.mv1");
	mPos = { 0.0f,0.0f,0.0f };
	mAngles = { 0.0f,0.0f,0.0f };
	mAnglesLocal = { 0.0f,(float)AsoUtility::Deg2Rad(180.0f),0.0f };

	//モデルの事前設定(座標)
	MV1SetPosition(mModel, mPos);

	VECTOR angle = mAngles;
	angle.x += mAnglesLocal.x;
	angle.y += mAnglesLocal.y;
	angle.z += mAnglesLocal.z;


	MV1SetRotationXYZ(mModel, angle);

	//再生するアニメーションの設定
	mAnimWalk = MV1AttachAnim(mModel, 1);

	//アニメーションの総時間取得
	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModel, mAnimWalk);

	//再生するアニメーションのフレームを指定する
	mStepAnim = 0.0f;
	MV1SetAttachAnimTime(mModel, mAnimWalk, mStepAnim);

}

void Unit::Update(void)
{
	Camera* camera = mSceneManager->GetCamera();

	VECTOR cmAngles = camera->GetAngles();

	float deltaTime = mSceneManager->GetDeltaTime();

	//アニメーションの再生時間をリセット
	mStepAnim += (SPEED_ANIM * deltaTime);
	if (mStepAnim > mTimeTotalAnimWalk)
	{
		mStepAnim = 0.0f;
	}


	//カメラ回転
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//右回転
		//mAngles.y += AsoUtility::Deg2Rad(1.0f);
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		//左回転
		//mAngles.y += AsoUtility::Deg2Rad(-1.0f);
	}

	VECTOR angle = mAngles;
	angle.x += mAnglesLocal.x;
	angle.y += mAnglesLocal.y;
	angle.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModel, angle);

	float movePow = 5.0f;

	float brincPow = 100.0f;

	//操作キー判定
	bool isHitMove = false;

	bool isBrinc = false;

	//回転したい角度
	float rodRad = 0.0f;

	VECTOR brincPos = { mPos.x + sinf(cmAngles.y + rodRad) * brincPow,mPos.y,
			mPos.z + cosf(cmAngles.y + rodRad) * brincPow };

	if (CheckHitKey(KEY_INPUT_P))
	{
		//Zの方向
		//mPos.z += movePow;

		//mAngles = { 0.0f,0.0f,0.0f };

		rodRad = AsoUtility::Deg2Rad(0.0f);
		
		isBrinc = true;
	}

	if (CheckHitKey(KEY_INPUT_W))
	{
		//Zの方向
		//mPos.z += movePow;

		//mAngles = { 0.0f,0.0f,0.0f };

		rodRad = AsoUtility::Deg2Rad(0.0f);
		isHitMove = true;

	}

	if (CheckHitKey(KEY_INPUT_S))
		{
			//Zの方向
			//mPos.z += (-movePow);

		//mAngles = { 0.0f,-180.0f,0.0f };

			rodRad = AsoUtility::Deg2Rad(180.0f);
			isHitMove = true;
		}

		if (CheckHitKey(KEY_INPUT_D))
		{
			//Zの方向
			//mPos.x += movePow;
			//mAngles = { 0.0f,90.0f,0.0f };

			rodRad = AsoUtility::Deg2Rad(90.0f);
			isHitMove = true;
		}

		if (CheckHitKey(KEY_INPUT_A))
		{
			//Zの方向
			//mPos.x += (-movePow);
			//mAngles = { 0.0f,-90.0f,0.0f };

			rodRad = AsoUtility::Deg2Rad(270.0f);
			isHitMove = true;
		}

		if (isHitMove)
		{
			mPos.x += sinf(cmAngles.y + rodRad) * movePow;
			mPos.z += cosf(cmAngles.y + rodRad) * movePow;
			

			//mAngles.y = cmAngles.y + rotRad;

			//徐々に回転する

			//現在の角度
			float radUnitAngleY = mAngles.y;

			//理想の角度(向きたい角度)
			float radMoveAngleY = cmAngles.y + rodRad;
			radMoveAngleY = AsoUtility::RadIn2PI(radMoveAngleY);

			//回転が少ないほうの回転の向きを取得する
			float aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);

			//回転させる
			mAngles.y += (SPEED_ROT_RAD * aroundDir);

			float diff = radMoveAngleY - radUnitAngleY;
			if(diff<= AsoUtility::Deg2Rad(5.0f)&& diff >= AsoUtility::Deg2Rad(-5.0f))
			{
				mAngles.y = radMoveAngleY;
			}

			mAngles.y = AsoUtility::RadIn2PI(mAngles.y);
			
		}

		if (isBrinc)
		{
			mPos = brincPos;
		}

	MV1SetPosition(mModel, mPos);



	MV1SetAttachAnimTime(mModel, mAnimWalk, mStepAnim);

	if (CheckHitKey(KEY_INPUT_Q))
	{
		if (mBullet == nullptr)
		{
			mBullet = new Bullet(mPos, mAngles);
			mBullet->Init();
			
		}
	}
	if (mBullet != nullptr)
	{
		mBullet->Update();
	}
	
}

void Unit::Draw(void)
{
	MV1DrawModel(mModel);

	if (mBullet != nullptr)
	{
		mBullet->Draw();
	}
	
}


void Unit::Release(void)
{
	MV1DeleteModel(mModel);

	if (mBullet != nullptr)
	{
		mBullet->Release();
		delete mBullet;
	}

}

VECTOR Unit::GetPos(void)
{
	return mPos;
}

VECTOR Unit::GetAngle(void)
{
	return mAngles;
}
