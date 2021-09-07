#version 150

in  vec3  in_Position;
in  vec3  in_Normal;
in  vec2  in_TexCoord;

uniform mat4 projectionMatrix;
uniform mat4 modelToWorldToView;

out vec3 Frag_pos;
out vec2 Frag_tex_coord;
out vec3 Normal;

void main(void)
{
//	gl_Position=projectionMatrix*modelToWorldToView*vec4(in_Position, 1.0);
    
    gl_Position=projectionMatrix * modelToWorldToView * vec4(in_Position, 1.0);
    Normal = in_Normal;
    Frag_pos = vec3(modelToWorldToView * vec4(in_Position, 1.0));
    Frag_tex_coord = in_TexCoord;
}

