#pragma once
#include "Effect.h"
#include <KamataEngine.h>

class GameScene {
public: // メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private: // メンバ変数
	KamataEngine::WorldTransform worldTransform_;//ワールド変換データ
	KamataEngine::Camera camera_;//カメラ

	KamataEngine::Model* modelEffect_ = nullptr;
	Effect* effect_ = nullptr;
};
