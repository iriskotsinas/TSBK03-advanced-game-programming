#version 150

//in vec3 in_Color;
in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;
uniform mat4 matrix;

out vec4 g_color;
const vec3 lightDir = normalize(vec3(0.3, 0.5, 1.0));

uniform mat4 R1;
uniform mat4 R2;
uniform mat4 T1;
uniform mat4 T2;

// Uppgift 3: Soft-skinning p� GPU
//
// Flytta �ver din implementation av soft skinning fr�n CPU-sidan
// till vertexshadern. Mer info finns p� hemsidan.

void main(void)
{
	// transformera resultatet med ModelView- och Projection-matriserna
    // uppgift 2
    //	gl_Position = matrix * vec4(in_Position, 1.0);
    
    vec3 pos_x = vec3(in_TexCoord.x * (T1 * R1 * inverse(T1)) * vec4(in_Position, 1));
    vec3 pos_y = vec3(in_TexCoord.y * (T2 * R2 * inverse(T2)) * vec4(in_Position, 1));

    gl_Position = matrix * vec4(pos_x + pos_y, 1.0);

	// s�tt r�d+gr�n f�rgkanal till vertex Weights
	vec4 color = vec4(in_TexCoord.x, in_TexCoord.y, 0.0, 1.0);

	// L�gg p� en enkel ljuss�ttning p� vertexarna 	
	float intensity = dot(in_Normal, lightDir);
	color.xyz *= intensity;

	g_color = color;
}

