matrix			g_matWorld;		// ��� ���̺� : ���� �̸�
matrix			g_matView;
matrix			g_matProj;

texture			g_BaseTexture;

// �ؽ�ó�� ���� ������ �����ϱ� ���� ����ü 
sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;	
};


struct VS_IN
{
	float4		vPosition : POSITION;	// �ø�ƽ : ���� �ɼ�(�����ϱ� ���� ǥ���ϸ� FVF)
	float2		vTexUV    : TEXCOORD0; 
};

struct VS_OUT
{
	float4		vPosition : POSITION;	
	float2		vTexUV : TEXCOORD0;
	
	//float4		vColor : COLOR0;
};

// ���ؽ� ���̴�
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

// �ȼ� ���̴�
PS_OUT		PS_Main(PS_IN In)
{
	PS_OUT	 Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV); // 2���� ������ �ؽ�ó�κ��� uv��ǥ�� �ش��ϴ� ���� �����ϴ� �Լ�(��ȯ Ÿ���� vectorŸ��)

	return Out;
}