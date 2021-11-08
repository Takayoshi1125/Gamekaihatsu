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

	// デルタタイム
	mTickCount = std::chrono::system_clock::now();

	//3D関連の初期化
	Init3D();
}

void SceneManager::Init3D(void)
{
	//Zバッファを有効に
	SetUseZBuffer3D(true);

	//Zバッファへの書き込みを有効に
	SetWriteZBuffer3D(true);

	//バック化リングを有効に
	SetUseBackCulling(true);

	//カメラのクリップ王距離を設定
	SetCameraNearFar(0.0f, 1500.0f);
	
	//ライトの向き
	ChangeLightTypeDir({ 00.3f,-0.7f,0.8f });

	//背景色の設定
	SetBackgroundColor(0, 139, 139);
}

void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	// デルタタイム
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

	//カメラ
	mCamera->Update();

	// ミニカメラ
	mMiniCamera->Update();
	mMiniCamera->DrawScreen();

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();


	//カメラ設定
	mCamera->SetBeforeDraw();

	//DrawSphere3D({0.0f,0.0f,0.0f},50.0f,10,0xffffff,0xffffff,true);

	// 描画
	mScene->Draw();

	// ミニカメラ
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



