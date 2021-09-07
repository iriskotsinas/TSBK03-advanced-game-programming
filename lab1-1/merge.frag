#version 150

in vec2 texCoord;
uniform sampler2D texUnit;
uniform sampler2D texUnit2;
out vec4 out_Color;

void main(void)
{
    vec4 a = texture(texUnit, texCoord);
    vec4 b = texture(texUnit2, texCoord);
    out_Color = (a * 0.3 + b * 1.0);
}
