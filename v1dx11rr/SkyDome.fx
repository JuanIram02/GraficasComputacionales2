//Skydome.fx

Texture2D textures : register(t0);
Texture2D noche : register(t2);
Texture2D Atardecer : register(t1);
SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projMatrix;
    float4 valores;
};


cbuffer Skycontrol : register(b1)
{
    float porciento;
    float hora;
    float extra;
    float extra2;
};

struct VS_Input
{
    float4 pos : POSITION;
    float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD0;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input) 0;
    vsOut.pos = mul(vertex.pos, worldMatrix);
    vsOut.pos = mul(vsOut.pos, viewMatrix);
    vsOut.pos = mul(vsOut.pos, projMatrix);

    vsOut.tex0 = vertex.tex0;

    return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{

    float4 finalColor;
    float4 TextNoche = noche.Sample(colorSampler, pix.tex0);
    float4 Texttextures = textures.Sample(colorSampler, pix.tex0);
    float4 TextAtardecer = Atardecer.Sample(colorSampler, pix.tex0);

    if (hora > 1 && hora < 2)
    {
        finalColor = lerp(TextNoche, TextAtardecer, porciento);
    }

    if (hora > 2 && hora < 11)
    {
        finalColor = lerp(TextAtardecer, Texttextures, extra);

    }

    if (hora > 11 && hora < 15)
    {
        finalColor = lerp(TextNoche, TextAtardecer, porciento);
    }


    return finalColor;
}