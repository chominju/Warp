matrix			g_matWorld;		// 상수 테이블 : 고유 이름
matrix			g_matView;
matrix			g_matProj;

texture			g_BaseTexture;

// 텍스처의 각종 성질을 지정하기 위한 구조체 
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;	
};


struct VS_IN
{
	float4		vPosition : POSITION;	// 시멘틱 : 고유 옵션(이해하기 쉽게 표현하면 FVF)
	float2		vTexUV    : TEXCOORD0; 
};

struct VS_OUT
{
	float4		vPosition : POSITION;	
	float2		vTexUV : TEXCOORD0;
	
	//float4		vColor : COLOR0;
};

// 버텍스 쉐이더
VS_OUT		VS_Main(VS_IN In)
{
	VS_OUT	 Out = (VS_OUT)0;

	matrix	matWV, matWVP;

	matWV  = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);
	
	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vTexUV = In.vTexUV;

	return Out;
}

struct PS_IN
{
	float2		vTexUV		: TEXCOORD0;
};

struct PS_OUT
{
	float4		vColor		: COLOR0;
};

// 픽셀 쉐이더
PS_OUT		PS_Main(PS_IN In)
{
	PS_OUT	 Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV); // 2차원 상태의 텍스처로부터 uv좌표에 해당하는 색을 추출하는 함수(반환 타입이 vector타입)

	return Out;
}