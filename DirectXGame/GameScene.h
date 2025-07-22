#pragma once
#include "KamataEngine.h"
#include "Stage.h"
#include "Player.h"
#include "Graph.h"
#include "DrawScore.h"
class GameScene {
public:
	~GameScene();//解放処理
	void Init();//初期化処理
	void Update();//更新処理
	void DrawBackGroundSprite();//スプライトの描画処理
	void DrawUISprite();
	void DrawModel();//モデルの描画処理

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;
	Stage* stage_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	Player* player_ = nullptr;
	Graph* graph_ = nullptr;
	DrawScore* score_ = nullptr;
};
