#version 150

//in vec2 outTexCoord;
//uniform sampler2D texUnit;
//out vec4 out_Color;

uniform sampler2D texUnit;
//uniform float texSize;
in vec2 texCoord;
out vec4 fragColor;

void main(void)
{
//    float offset = 1.0 / texSize;
    float offset = 1.0 / 256;
    vec4 c = texture(texUnit, texCoord);
    vec4 l = texture(texUnit, texCoord + vec2(offset, 0.0));
    vec4 r = texture(texUnit, texCoord + vec2(-offset, 0.0));
//    fragColor = (c + c + l + r) * 0.25;
    
//    float offset = 1.0f / 256;
//    vec4 c = texture(texUnit, texCoord);
//    vec4 l = texture(texUnit, texCoord + vec2(offset, 0.0));
//    vec4 r = texture(texUnit, texCoord + vec2(-offset, 0.0));
    vec4 d = texture(texUnit, texCoord + vec2(0.0, offset));
    vec4 u = texture(texUnit, texCoord + vec2(0.0, -offset));
    fragColor = ((4 * c) + l + r + d + u) / 8;
}
