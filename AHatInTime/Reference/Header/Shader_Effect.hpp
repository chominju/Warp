matrix			g_matWorld;		// 상수 테이블 : 고유 이름
matrix			g_matView;
matrix			g_matProj;

texture			g_BaseTexture;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;	
};

texture			g_DepthTexture;

sampler DepthSampler = sampler_state
{
	texture = g_DepthTexture;
};



struct VS_IN
{
	float4		vPosition : POSITION;	
	float2		vTexUV    : TEXCOORD0; 
};

struct VS_OUT
{
	float4		vPosition : POSITION;	
	float2		vTexUV : TEXCOORD0;	
	vector		vProjPos : TEXCOORD1;
};

// 버텍스 쉐이더
VS_OUT		VS_MAIN(VS_IN In)
{
	VS_OUT	 Out = (VS_OUT)0;

	matrix	matWV, matWVP;

	matWV  = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);
	
	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vProjPos = Out.vPosition;
	Out.vTexUV = In.vTexUV;

	return Out;
}

struct PS_IN
{
	float2		vTexUV		: TEXCOORD0;
	vector		vProjPos	: TEXCOORD1;
};

struct PS_OUT
{
	float4		vColor		: COLOR0;
};

// 픽셀 쉐이더
PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT	 Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV); 

	float2		vDepthUV = (float2)0.f;

	// 투영 상태의 좌표를 텍스처 uv 좌표로 변환
	// x : 투영의 -1 -> 텍스쳐 0, 투영의 1 -> 텍스처 1
	vDepthUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	
	// y : 투영의 1 -> 텍스쳐 0, 투영의 -1 -> 텍스처 1
	vDepthUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	// 깊이 버퍼로 부터 텍스처의 해당 부위의 뷰스페이스 상의 깊이 값을 얻어옴
	float fViewZ = tex2D(DepthSampler, vDepthUV).y * 1000.f;	

	Out.vColor.a = Out.vColor.a * saturate(fViewZ - In.vProjPos.w);
		
	return Out;
}

technique	Default_Device
{
	pass Temp
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;

		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
	}
};
