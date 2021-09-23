#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef	struct tagVertexColor
	{
		_vec3		vPos;			
		_ulong		dwColor;		

	}VTXCOL;

	const _ulong	FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

	typedef	struct tagVertexTexture
	{
		_vec3		vPos;
		_vec3		vNormal;
		_vec2		vTexUV;	

	}VTXTEX;

	const _ulong	FVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	typedef struct tagVertexCube
	{
		_vec3			vPos;
		_vec3			vTexUV;

	}VTXCUBE;

	const _ulong	FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0); // FLOAT�� 3���� ũ�⸸ŭ�� �ؽ��� UV�� �ǹ��ϴ� FVF


	typedef struct tagIndex16
	{
		_ushort		_0;
		_ushort		_1;
		_ushort		_2;

	}INDEX16;

	typedef struct tagIndex32
	{
		_ulong		_0;
		_ulong		_1;
		_ulong		_2;

	}INDEX32;


	typedef struct D3DXFRAME_DERIVED : public D3DXFRAME
	{
		_matrix			CombinedTransformMatrix;
			
	}D3DXFRAME_DERIVED;

	typedef struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
	{
		LPDIRECT3DTEXTURE9*			ppTexture;
		
		LPD3DXMESH				pOriMesh;			// ���� x������ �ε����� �� ���� ������ �ʴ� ���� ���� ������ �����ϱ� ���� �İ�ü

		_ulong					dwNumBones;			// ���� ����(���� ��ĵ��� �����Ͽ� ���������� ����ϱ� ���� ���� ����� ����� ���� �ʿ�)

		_matrix*				pFrameOffsetMatrix;	// ���� ���� �ִ� �ִϸ��̼� ������ ����ϱ� ���� ���
		_matrix**				ppFrameCombinedTransformMatrix; // CombinedTransformMatrix���� �ּҰ��� ����(��ȸ�ϸ� ���� ��İ� ���ϱ⸦ �ϱ� ����)�ϱ� ���� ��� ������
		
		_matrix*				pRenderingMatrix;		// ���������� ��� ������ ����� �������
														// pRenderingMatrix = pFrameOffsetMatrix * (*ppFrameCombinedTransformMatrix)

	}D3DXMESHCONTAINER_DERIVED;

	typedef struct
	{
		LPDIRECT3DTEXTURE9 texture; // �ؽ��� ������ �����ϱ� ���� �İ�ü
		D3DXIMAGE_INFO imageInfo;
	}Texture_Info;
}



#endif // Engine_Struct_h__