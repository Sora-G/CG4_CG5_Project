#pragma once
#include "KamataEngine.h"
class Stage {
public:
	~Stage();//解放処理
	void Init();   // 初期化処理
	void Update(); // 更新処理
	void Draw();   // 描画処理

private:
	uint32_t backGroundTexture_ = 0;
	KamataEngine::Sprite* backGroundSprite_[2] = {nullptr, nullptr};
};
