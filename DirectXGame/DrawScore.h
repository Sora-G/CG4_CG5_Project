#pragma once
#include "KamataEngine.h"
class DrawScore {
public:
	~DrawScore();  // 解放処理
	void Init();   // 初期化処理
	void Update(); // 更新処理
	void Draw();   // 描画処理

private:
	KamataEngine::Vector2 size = {32.0f, 64.0f};
	uint32_t scoreTexture_ = 0;
	KamataEngine::Sprite* scoreSprite_[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
	int number_ = 0;
};
