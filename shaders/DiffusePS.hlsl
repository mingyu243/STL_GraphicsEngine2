// 픽셀 쉐이더 입력.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;
};

// 라이트 버퍼.
cbuffer light : register(b0)
{
    float3 lightPosition;
    float pad1;
}

// 텍스쳐 데이터.
Texture2D image;
SamplerState samplerState;


// 픽셀 쉐이더.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    // 이미지의 색상 추출하기.
    float4 color = image.Sample(samplerState, input.texCoord);
    
    // 디퓨즈 계산.
    float worldNormal = normalize(input.normal);
    
    //// 라이트 위치.
    //float3 lightPosition = float3(500.0f, 500.0f, -500.0f);
    
    // 라이트 방향.
    float3 lightDir = normalize(input.worldPosition - lightPosition);
    
    // 디퓨즈 빛의 세기(밝기) power.
    float NdotL = saturate(dot(worldNormal, -lightDir));
    //NdotL = max(0, NdotL);
    //NdotL = saturate(NdotL);
    
    // NdotL = pow((NdotL * 0.5f) + 0.5f, 2); // 하프 램버트.
    
    float4 final = NdotL * color;
    
    return float4(NdotL, NdotL, NdotL, 1.0f);
    //return final;
}