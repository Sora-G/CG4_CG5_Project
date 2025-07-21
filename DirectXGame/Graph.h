#pragma once
#include "KamataEngine.h"
class Graph {
public:
	~Graph();//解放処理
	void Init();
	void Update();
	void Draw();

private:
	uint32_t graphTexture_ = 0;
	const KamataEngine::Vector2 kGraphSize = {200.0f, 30.0f};
	KamataEngine::Vector2 graphSize_;
	KamataEngine::Sprite* graphSprite1_ = nullptr;
	KamataEngine::Sprite* graphSprite2_ = nullptr;
};
