#include "DrawScore.h"

using namespace KamataEngine;

DrawScore::~DrawScore() {
	//解放処理
	for (int i = 0; i < 5; i++) {
		delete scoreSprite_[i];
	}
}

void DrawScore::Init() {
	//初期化処理
	scoreTexture_ = TextureManager::Load("number.png");
	for (int i = 0; i < 5; i++) {
		scoreSprite_[i] = Sprite::Create(scoreTexture_, {1000.0f + size.x * i, 30.0f});
		scoreSprite_[i]->SetSize(size);
		scoreSprite_[i]->SetTextureRect({0, 0}, size);
	}
}

void DrawScore::Update() {
	//更新処理
	number_++;
	if (number_ > 99999) {
		number_ = 0;
	}

	int digit = 10000;
	for (int i = 0; i < 5; i++) {
		int nowNumber = (number_ / digit) % 10;
		scoreSprite_[i]->SetTextureRect({size.x * nowNumber, 0}, size);
		digit /= 10;
	}
}

void DrawScore::Draw() {
	//描画処理
	for (int i = 0; i < 5; i++) {
		scoreSprite_[i]->Draw();
	}
}
