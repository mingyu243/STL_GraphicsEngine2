// �ȼ� ���̴� �Է�.
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

// ����Ʈ ����.
cbuffer light : register(b0)
{
    float3 lightPosition;
    float pad1;
}

// �ؽ��� ������.
Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);

SamplerState samplerState : register(s0);


// �ȼ� ���̴�.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    // ��ָ� �� ����.
    float3 tangentNormal = normalMap.Sample(samplerState, input.texCoord).rgb;
    
    // ���� �� ����.
    tangentNormal = tangentNormal * 2 - 1;
    
    // ź��Ʈ ���� -> ���� ���� ��ȯ ��� (TBN)
    // �� ���� ��ķ� �������. ����
    float3x3 TBN = float3x3(
        normalize(input.tangent), // �����⸦ ��ġ�鼭 ���� �� �־ normalize �� ��.
        normalize(input.binormal),
        normalize(input.normal)
    );
    float3 worldNormal = mul(tangentNormal, TBN); // �� ���� ��� ��.
    //float3 worldNormal = mul(TBN, tangentNormal); // �� ���� ��� ��.
    
    //// ����Ʈ ��ġ.
    //float3 lightPosition = float3(500.0f, 500.0f, -500.0f);
    
    // ����Ʈ ����.
    float3 lightDir = normalize(input.worldPosition - lightPosition);
    
    // �̹����� ���� �����ϱ�.
    float4 diffuseColor = diffuseMap.Sample(samplerState, input.texCoord);
    
    // ��ǻ�� ���� ����(���) power.
    float NdotL = saturate(dot(worldNormal, -lightDir));
    //NdotL = max(0, NdotL);
    //NdotL = saturate(NdotL);
    
    NdotL = pow((NdotL * 0.5f) + 0.5f, 2); // ���� ����Ʈ.
    
    
    float3 cameraDirection = normalize(input.cameraDirection);
    
    // ��-��(Blinn-Phong)
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