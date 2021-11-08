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

	//���f���̎��O�ݒ�(���W)
	MV1SetPosition(mModel, mPos);

	VECTOR angle = mAngles;
	angle.x += mAnglesLocal.x;
	angle.y += mAnglesLocal.y;
	angle.z += mAnglesLocal.z;


	MV1SetRotationXYZ(mModel, angle);

	//�Đ�����A�j���[�V�����̐ݒ�
	mAnimWalk = MV1AttachAnim(mModel, 1);

	//�A�j���[�V�����̑����Ԏ擾
	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModel, mAnimWalk);

	//�Đ�����A�j���[�V�����̃t���[�����w�肷��
	mStepAnim = 0.0f;
	MV1SetAttachAnimTime(mModel, mAnimWalk, mStepAnim);

}

void Unit::Update(void)
{
	Camera* camera = mSceneManager->GetCamera();

	VECTOR cmAngles = camera->GetAngles();

	float deltaTime = mSceneManager->GetDeltaTime();

	//�A�j���[�V�����̍Đ����Ԃ����Z�b�g
	mStepAnim += (SPEED_ANIM * deltaTime);
	if (mStepAnim > mTimeTotalAnimWalk)
	{
		mStepAnim = 0.0f;
	}


	//�J������]
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//�E��]
		//mAngles.y += AsoUtility::Deg2Rad(1.0f);
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		//����]
		//mAngles.y += AsoUtility::Deg2Rad(-1.0f);
	}

	VECTOR angle = mAngles;
	angle.x += mAnglesLocal.x;
	angle.y += mAnglesLocal.y;
	angle.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModel, angle);

	float movePow = 5.0f;

	float brincPow = 100.0f;

	//����L�[����
	bool isHitMove = false;

	bool isBrinc = false;

	//��]�������p�x
	float rodRad = 0.0f;

	VECTOR brincPos = { mPos.x + sinf(cmAngles.y + rodRad) * brincPow,mPos.y,
			mPos.z + cosf(cmAngles.y + rodRad) * brincPow };

	if (CheckHitKey(KEY_INPUT_P))
	{
		//Z�̕���
		//mPos.z += movePow;

		//mAngles = { 0.0f,0.0f,0.0f };

		rodRad = AsoUtility::Deg2Rad(0.0f);
		
		isBrinc = true;
	}

	if (CheckHitKey(KEY_INPUT_W))
	{
		//Z�̕���
		//mPos.z += movePow;

		//mAngles = { 0.0f,0.0f,0.0f };

		rodRad = AsoUtility::Deg2Rad(0.0f);
		isHitMove = true;

	}

	if (CheckHitKey(KEY_INPUT_S))
		{
			//Z�̕���
			//mPos.z += (-movePow);

		//mAngles = { 0.0f,-180.0f,0.0f };

			rodRad = AsoUtility::Deg2Rad(180.0f);
			isHitMove = true;
		}

		if (CheckHitKey(KEY_INPUT_D))
		{
			//Z�̕���
			//mPos.x += movePow;
			//mAngles = { 0.0f,90.0f,0.0f };

			rodRad = AsoUtility::Deg2Rad(90.0f);
			isHitMove = true;
		}

		if (CheckHitKey(KEY_INPUT_A))
		{
			//Z�̕���
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

			//���X�ɉ�]����

			//���݂̊p�x
			float radUnitAngleY = mAngles.y;

			//���z�̊p�x(���������p�x)
			float radMoveAngleY = cmAngles.y + rodRad;
			radMoveAngleY = AsoUtility::RadIn2PI(radMoveAngleY);

			//��]�����Ȃ��ق��̉�]�̌������擾����
			float aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);

			//��]������
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
