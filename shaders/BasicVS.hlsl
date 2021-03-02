// 행렬 데이터.
// Constant Buffer. (상수 버퍼.)
cbuffer transform : register(b0)
{
	// 4x4 행렬. 
	matrix world;
};

// 카메라 행렬 데이터.
cbuffer camera : register(b1)
{
    matrix viewProjection;
}

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
    output.position = mul(output.position, viewProjection);

	return output;
}