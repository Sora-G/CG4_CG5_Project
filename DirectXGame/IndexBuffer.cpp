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
}
