#pragma once

#include <d3dx12.h>

class VertexBuffer {
public:
	//生成
	void Create(const UINT size,const UINT stride);

	//ゲッター
	ID3D12Resource* Get();//頂点バッファー
	D3D12_VERTEX_BUFFER_VIEW* GetView();//頂点バッファービュー
};
