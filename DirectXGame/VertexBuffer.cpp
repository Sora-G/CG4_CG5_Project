#include "VertexBuffer.h"
#include "KamataEngine.h"

#include <d3dx12.h>
#include <cassert>

using namespace KamataEngine;

void VertexBuffer::Create(const UINT size, const UINT stride) {
	// クラス内で取得するために追加
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// VertexResource生成
	// 頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; // CPUから書き込むヒープ
	// 頂点リソースの設定
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; // バッファ
	vertexResourceDesc.Width = sizeof(Vector4) * 3;                 // リソースのサイズ Vertex4を３頂点分
	// バッファの場合はこれらを１にする
	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;
	// バッファの場合はこれにする
	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 実際に頂点リソースを生成する
	ID3D12Resource* vertexResource = nullptr;
	HRESULT hr =
	    dxCommon->GetDevice()->CreateCommittedResource(
			&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &vertexResourceDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexResource));
	assert(SUCCEEDED(hr)); // 上手く行かなかった時は起動できない

	vertexBuffer_ = vertexResource;
}
