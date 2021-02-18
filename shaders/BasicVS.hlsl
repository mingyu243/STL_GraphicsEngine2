// 정점 쉐이더.
float4 main(float4 position : POSITION) : SV_POSITION
{
	return position;
}

// float4 main(float4 position  // IA에서 포지션을 받아 옴. 나중에 복잡해지면 구조체로 만들어서 받을 수 있음.
// : POSITION)	// 지금은 포지션 하나만 받아왔으니까 이게 Position을 뜻하는 거라고 알려줌. 시멘틱.
// : SV_POSITION  // 시스템에게 이게 Position을 뜻하는 거라고 알려줌. SV : 시스템 벨류.