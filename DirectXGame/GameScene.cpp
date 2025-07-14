#include "GameScene.h"
#include "Stage.h"

using namespace KamataEngine;

GameScene::~GameScene() {
	//解放処理
	delete titleSprite_;
	delete gameStartSprite_;
}

void GameScene::Init() {
	//初期化処理
	titleTexture_ = TextureManager::Load("game_title.png");
	titleSprite_ = Sprite::Create(titleTexture_, {340, 260});
	gameStartTexture_ = TextureManager::Load("press_any_button.png");
	gameStartSprite_ = Sprite::Create(gameStartTexture_, {340, 540});
}

void GameScene::Update() {
	//更新処理
	count_++;
	if (count_ > 60) {
		count_ = 0;
	}
}

void GameScene::Draw() {
	//描画処理
	titleSprite_->Draw();
	if (count_ % 60 >= 30) {
		gameStartSprite_->Draw();
	}
}

