#include "KamataEngine.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Stage.h"
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3C_12_スズキ_ソラ");

	// DirectXCommonのインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	TitleScene* titleScene = new TitleScene();
	titleScene->Init();

	GameScene* gameScene = new GameScene();
	gameScene->Init();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		gameScene->Update();

		dxCommon->PreDraw();//描画前処理

		//スプライト描画前処理
		Sprite::PreDraw(dxCommon->GetCommandList());
		gameScene->DrawBackGroundSprite();
		//スプライト描画後処理
		Sprite::PostDraw();

		dxCommon->ClearDepthBuffer();

		Model::PreDraw(dxCommon->GetCommandList());
		gameScene->DrawModel();
		Model::PostDraw();

		// スプライト描画前処理
		Sprite::PreDraw(dxCommon->GetCommandList());
		gameScene->DrawUISprite();
		// スプライト描画後処理
		Sprite::PostDraw();

		dxCommon->PostDraw();//描画後処理
	}

	// エンジンの終了処理
	KamataEngine::Finalize();

	delete gameScene;
	delete titleScene;

	return 0;
}
