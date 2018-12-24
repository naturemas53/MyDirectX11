cbuffer GLOBAL_MATLIXS {

	float4x4 GM_VP_INVERT;

};

struct VS_IN
{
	float4 pos : POSITION0;
	float2  uv : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2  uv : TEXCOORD0;

};


VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;

	output.pos = mul(input.pos, GM_VP_INVERT);
	output.uv = input.uv;

	return output;
}