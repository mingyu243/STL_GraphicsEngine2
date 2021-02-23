// 행렬 데이터.
// Constant Buffer. (상수 버퍼.)
cbuffer transform : register(b0)
{
	// 4x4 행렬. 
	// float4x4, float3x3, float2x2
	matrix world;
};

// 정점 입력.
struct vs_input
{
	float4 position : POSITION;
};

// 정점 출력.
struct vs_output
{
	float4 position : SV_POSITION;
};

// float4 main(float4 position : POSITION) : SV_POSITION
// float4 main(vs_input input) : SV_POSITION
vs_output main(vs_input input)
{
	vs_output output;
	output.position = mul(input.position, world);

	return output;
}