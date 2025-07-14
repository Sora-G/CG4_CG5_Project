#include "Stage.h"

using namespace KamataEngine;

Stage::~Stage() {
	//解放処理
	for (int i = 0; i < 2; ++i) {
		delete backGroundSprite_[i];
	}
}

void Stage::Init() {
	//初期化処理
	backGroundTexture_ = TextureManager::Load("backGround.png");
	backGroundSprite_[0] = Sprite::Create(backGroundTexture_, {0,0});
	backGroundSprite_[1] = Sprite::Create(backGroundTexture_, {1280,0});
}

void Stage::Update() {
	//更新処理
	Vector2 position[2] = {};
	for (int i = 0; i < 2; ++i) {
		position[i] = backGroundSprite_[i]->GetPosition();
		position[i].x -= 4;
		if (backGroundSprite_[i]->GetPosition().x <= -1280+(i*1280)) {
			position[i].x = float(i * 1280);
		}
		backGroundSprite_[i]->SetPosition(position[i]);
	}
}

void Stage::Draw() {
	//描画処理
	for (int i = 0; i < 2; ++i) {
		backGroundSprite_[i]->Draw();
	}
}
