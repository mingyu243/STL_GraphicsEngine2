// 픽셀 쉐이더 입력.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;
    
    float3 cameraDirection : TEXCOORD2;
    
    float3 binormal : TEXCOORD3;
    float3 tangent : TEXCOORD4;
};

// 라이트 버퍼.
cbuffer light : register(b0)
{
    float3 lightPosition;
    float pad1;
}

// 텍스쳐 데이터.
Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);

SamplerState samplerState : register(s0);


// 픽셀 쉐이더.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    // 노멀맵 값 추출.
    float3 tangentNormal = normalMap.Sample(samplerState, input.texCoord).rgb;
    
    // 원래 값 복원.
    tangentNormal = tangentNormal * 2 - 1;
    
    // 탄젠트 공간 -> 월드 공간 변환 행렬 (TBN)
    // 열 기준 행렬로 만들어짐. ↓↓↓
    float3x3 TBN = float3x3(
        normalize(input.tangent), // 보간기를 거치면서 꼬일 수 있어서 normalize 해 줌.
        normalize(input.binormal),
        normalize(input.normal)
    );
    float3 worldNormal = mul(tangentNormal, TBN); // 열 기준 행렬 곱.
    //float3 worldNormal = mul(TBN, tangentNormal); // 행 기준 행렬 곱.
    
    //// 라이트 위치.
    //float3 lightPosition = float3(500.0f, 500.0f, -500.0f);
    
    // 라이트 방향.
    float3 lightDir = normalize(input.worldPosition - lightPosition);
    
    // 이미지의 색상 추출하기.
    float4 diffuseColor = diffuseMap.Sample(samplerState, input.texCoord);
    
    // 디퓨즈 빛의 세기(밝기) power.
    float NdotL = saturate(dot(worldNormal, -lightDir));
    //NdotL = max(0, NdotL);
    //NdotL = saturate(NdotL);
    
    NdotL = pow((NdotL * 0.5f) + 0.5f, 2); // 하프 램버트.
    
    
    float3 cameraDirection = normalize(input.cameraDirection);
    
    // 블린-퐁(Blinn-Phong)
    float3 halfVector = normalize((-cameraDirection) + (-lightDir));
    float specular = 0;
    if (NdotL > 0)
    {
        float HdotN = saturate(dot(halfVector, worldNormal));
        specular = pow(HdotN, 100.0f);
    }

    float4 final = (NdotL * diffuseColor) + (specular * diffuseColor);
    final = NdotL + specular;
    
    return final;
}