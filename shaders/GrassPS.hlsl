// «»ºø Ω¶¿Ã¥ı ¿‘∑¬.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

// «»ºø Ω¶¿Ã¥ı.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    
    
    
    return float4(0, input.texCoord.y, 0, 1);
}