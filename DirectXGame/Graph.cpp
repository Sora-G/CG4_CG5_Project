#include "Graph.h"

using namespace KamataEngine;

Graph::~Graph() {
	//解放処理
	delete graphSprite1_;
	delete graphSprite2_;
}

void Graph::Init() {
	//初期化処理
	graphTexture_ = TextureManager::Load("white1x1.png");
	graphSprite1_ = Sprite::Create(graphTexture_, {20.0f, 50.0f});
	graphSprite1_->SetSize(Vector2(kGraphSize.x, kGraphSize.y));
	graphSprite1_->SetColor(Vector4(1.0f, 0.2f, 0.2f, 1.0f));

	graphSize_ = kGraphSize;
	graphSprite2_ = Sprite::Create(graphTexture_, {20.0f, 50.0f});
	graphSprite2_->SetSize(Vector2(graphSize_.x, graphSize_.y));
	graphSprite2_->SetColor(Vector4(0.2f, 1.0f, 0.2f, 1.0f));
}

void Graph::Update() {
	//更新処理
	graphSize_.x--;
	if (graphSize_.x <= 0.0f) {
		graphSize_.x = kGraphSize.x;
	}
	graphSprite2_->SetSize(Vector2(graphSize_.x, graphSize_.y));
}

void Graph::Draw() {
	//描画処理
	graphSprite1_->Draw();
	graphSprite2_->Draw();
}
