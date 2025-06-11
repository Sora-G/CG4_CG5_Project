#include "IndexBuffer.h"
#include "KamataEngine.h"

#include <d3d12.h>//ID3D~ D3D~
#include <cassert>//assert

using namespace KamataEngine;

void IndexBuffer::Create(const UINT size, const UINT stride) {
	//strideの値によって、１つのインデックスのフォーマットを決める
	assert(stride == 2 || stride == 4);//2byte,4byteのみ受け付ける
	DXGI_FORMAT format = (stride == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	
	//クラス内でdxCommonを使用するために追加
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//インデックスリソースの生成==========
	//インデックスリソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;//CPUから書き込むヒープ
	//インデックスリソースの設定
	D3D12_RESOURCE_DESC indexResourceDesc{};
	indexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;//バッファ
	indexResourceDesc.Width = size;//リソースのサイズ
	//バッファの場合はこれらを１にする決まり
	indexResourceDesc.Height = 1;
	indexResourceDesc.DepthOrArraySize = 1;
	indexResourceDesc.MipLevels = 1;
	indexResourceDesc.SampleDesc.Count = 1;
	//バッファの場合はこれにする決まり
	indexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
}
