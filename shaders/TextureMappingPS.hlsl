// 픽셀 쉐이더 입력.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
};

// 텍스쳐 데이터.
Texture2D image;
SamplerState samplerState;

// 픽셀 쉐이더.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    // 이미지의 색상 추출하기.
    float4 color = image.Sample(samplerState, input.texCoord);
    
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
    return color;
}