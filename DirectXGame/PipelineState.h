#pragma once

#include <d3dx12.h>

class PipelineState {
public:
	//生成
	void Create();
	//ゲッター
	ID3D12PipelineState* Get();

	//コンストラクタ
	PipelineState();
	//デストラクタ
	~PipelineState();

private:
	//パイプラインステート
	ID3D12PipelineState* pipelineState_ = nullptr;
};
