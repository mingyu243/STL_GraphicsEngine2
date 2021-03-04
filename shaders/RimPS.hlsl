// 픽셀 쉐이더 입력.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;
    
    float3 cameraDirection : TEXCOORD2;
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
    float3 worldNormal = normalize(input.normal); // 보간기를 거치면서 꼬일 수 있어서 normalize 해 줌.
    
    //// 라이트 위치.
    //float3 lightPosition = float3(500.0f, 500.0f, -500.0f);
    
    // 라이트 방향.
    float3 lightDir = normalize(input.worldPosition - lightPosition);
    
    // 디퓨즈 빛의 세기(밝기) power.
    float NdotL = saturate(dot(worldNormal, -lightDir));
    //NdotL = max(0, NdotL);
    //NdotL = saturate(NdotL);
    
    NdotL = pow((NdotL * 0.5f) + 0.5f, 2); // 하프 램버트.
    
    float step = 3;
    //NdotL = ceil(NdotL * step) / step; // 툰 쉐이더 느낌내기.
    
    
    // 스페큘러.
    float3 reflection = reflect(lightDir, worldNormal);
    float3 cameraDirection = normalize(input.cameraDirection);
    
    // 퐁 쉐이더. 너무 동글동글함.
    float specular = 0;
    if (NdotL > 0)
    {
        float RdotV = dot(reflection, -cameraDirection);
        specular = saturate(RdotV);
        specular = pow(specular, 15.0f);
    }


    
    // 림 라이트.
    float rim = 0;
    rim = 1 - saturate(dot(worldNormal, -cameraDirection));
    rim = pow(rim, 3.0f); // 강도 조정.
    
    // 색 입히기.
    float3 rimColor = float3(0.8f, 0.2f, 0.1f);
    rimColor = rim * rimColor;
    
    // 디퓨즈 + 스페큘러.
    float4 final = (NdotL * color) + (specular * color) + float4(rimColor, 1);
    
    return final;
    //return float4(rimColor, 1);
    //return float4(rim, rim, rim, 1);

}