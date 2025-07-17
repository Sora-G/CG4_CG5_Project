#pragma once
#include "KamataEngine.h"
class TitleScene {
public:
	~TitleScene();  //解放処理
	void Init();   // 初期化処理
	void Update(); // 更新処理
	void Draw();   // 描画処理

private:
	uint32_t titleTexture_ = 0;
	KamataEngine::Sprite* titleSprite_ = nullptr;
	uint32_t gameStartTexture_ = 0;
	KamataEngine::Sprite* gameStartSprite_ = nullptr;
	int count_ = 0;
};
