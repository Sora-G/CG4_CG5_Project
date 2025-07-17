#pragma once
#include "KamataEngine.h"
#include "Stage.h"
class GameScene {
public:
	~GameScene();//デストラクタ
	void Init();//初期化処理
	void Update();//更新処理
	void DrawBackGroundSprite();//スプライトの描画処理
	void DrawModel();//モデルの描画処理

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	Stage* stage_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
};
