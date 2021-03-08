// 행렬 데이터.
// Constant Buffer. (상수 버퍼.)
cbuffer transform : register(b0)
{
	// 4x4 행렬. 
	matrix world; // 월드 행렬.
};

// 카메라 행렬 데이터.
cbuffer camera : register(b1)
{
    matrix viewProjection;
    float3 cameraPosition;
    float pad1;
}

// 정점 입력.
struct vs_input
{
	float4 position : POSITION; // 입력 레이아웃 순서랑 같아야 함.
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

// 정점 출력.
struct vs_output
{
	float4 position : SV_POSITION; // 시스템이 쓰니까, SV 붙힘.
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
};

// float4 main(float4 position : POSITION) : SV_POSITION
// float4 main(vs_input input) : SV_POSITION
vs_output main(vs_input input)
{
	vs_output output;
	output.position = mul(input.position, world);
    output.position = output.position + float4((1 - input.texCoord.y) * -10, 0, 0, 0);
	
    output.position = mul(output.position, viewProjection);
	
	output.texCoord = input.texCoord;
	
	// normal도 월드변환.
    output.normal = mul(input.normal, (float3x3)world);
	
		
	return output;
}