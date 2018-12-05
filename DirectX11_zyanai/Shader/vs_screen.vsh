cbuffer GLOBAL_MATLIXS {

	float4x4 GM_VP_INVERT;

};

struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
};


VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;

	output.pos = mul(input.pos, GM_VP_INVERT);
	output.col = input.col;
	return output;
}