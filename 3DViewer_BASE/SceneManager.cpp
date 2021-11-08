#include <chrono>
#include "DxLib.h"
#include "Fader.h"
#include "TitleScene.h"
#include "Camera.h"
#include "MiniCamera.h"
#include"AsoUtility.h"
#include "SceneManager.h"

void SceneManager::Init()
{

	mSceneID = SCENE_ID::TITLE;
	mWaitSceneID = SCENE_ID::NONE;

	mFader = new Fader();
	mFader->Init();

	mCamera = new Camera();
	mCamera->Init();

	mScene = new TitleScene(this);
	mScene->Init();

	mMiniCamera = new MiniCamera(mCamera);
	mMiniCamera->Init();

	mIsSceneChanging = false;

	// �f���^�^�C��
	mTickCount = std::chrono::system_clock::now();

	//3D�֘A�̏�����
	Init3D();
}

void SceneManager::Init3D(void)
{
	//Z�o�b�t�@��L����
	SetUseZBuffer3D(true);

	//Z�o�b�t�@�ւ̏������݂�L����
	SetWriteZBuffer3D(true);

	//�o�b�N�������O��L����
	SetUseBackCulling(true);

	//�J�����̃N���b�v��������ݒ�
	SetCameraNearFar(0.0f, 1500.0f);
	
	//���C�g�̌���
	ChangeLightTypeDir({ 00.3f,-0.7f,0.8f });

	//�w�i�F�̐ݒ�
	SetBackgroundColor(0, 139, 139);
}

void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	// �f���^�^�C��
	auto tickCount = std::chrono::system_clock::now();
	mDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(tickCount - mTickCount).count() / 1000000000.0f;
	mTickCount = tickCount;

	mFader->Update();
	if (mIsSceneChanging)
	{
		Fader::FADE_STATE fState = mFader->GetState();
		switch (fState)
		{
		case Fader::FADE_STATE::FADE_IN:
			if (mFader->IsEnd())
			{
				mFader->SetFade(Fader::FADE_STATE::NONE);
				mIsSceneChanging = false;
			}
			break;
		case Fader::FADE_STATE::FADE_OUT:
			if (mFader->IsEnd())
			{
				DoChangeScene();
				mFader->SetFade(Fader::FADE_STATE::FADE_IN);
			}
			break;
		default:
			break;
		}
	}
	else 
	{
		mScene->Update();
	}

	//�J����
	mCamera->Update();

	// �~�j�J����
	mMiniCamera->Update();
	mMiniCamera->DrawScreen();

	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();


	//�J�����ݒ�
	mCamera->SetBeforeDraw();

	//DrawSphere3D({0.0f,0.0f,0.0f},50.0f,10,0xffffff,0xffffff,true);

	// �`��
	mScene->Draw();

	// �~�j�J����
	mMiniCamera->Draw();

	mFader->Draw();

}

void SceneManager::Release(void)
{

	mScene->Release();
	delete mScene;

	mCamera->Release();
	delete mCamera;

}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isFading)
{
	mWaitSceneID = nextId;

	if (isFading)
	{
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		mIsSceneChanging = true;
	}
	else 
	{
		DoChangeScene();
	}

}

float SceneManager::GetDeltaTime(void)
{
	return mDeltaTime;
}

Camera* SceneManager::GetCamera(void)
{
	return mCamera;
}

void SceneManager::DoChangeScene(void)
{
	mScene->Release();

	mSceneID = mWaitSceneID;

	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		mScene = new TitleScene(this);
		break;
	default:
		break;
	}

	mScene->Init();

	mWaitSceneID = SCENE_ID::NONE;

}


