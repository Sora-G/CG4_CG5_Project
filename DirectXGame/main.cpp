#include "KamataEngine.h"
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

	GameScene* gameScene= new GameScene();
	gameScene->Init();

	Stage* stage = new Stage();
	stage->Init();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		stage->Update();


		dxCommon->PreDraw();

		Sprite::PreDraw(dxCommon->GetCommandList());
		stage->Draw();
		Sprite::PostDraw();

		dxCommon->PostDraw();
	}

	// エンジンの終了処理
	KamataEngine::Finalize();

	delete stage;
	delete gameScene;

	return 0;
}
