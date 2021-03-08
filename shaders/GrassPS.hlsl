// «»ºø Ω¶¿Ã¥ı ¿‘∑¬.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float time : TEXCOORD2;
    float3 worldPosition : TEXCOORD3;
};

// «»ºø Ω¶¿Ã¥ı.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    return float4(0, (abs(input.worldPosition.y / 10.0f) + input.time) % 1, 0, 1);
}