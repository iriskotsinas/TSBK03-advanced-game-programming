#version 150
// bump mapping should be calculated
// 1) in view coordinates
// 2) in texture coordinates

in vec2 outTexCoord;
in vec3 out_Normal;
in vec3 Ps;
in vec3 Pt;
in vec3 pixPos;  // Needed for specular reflections
uniform sampler2D texUnit;
out vec4 out_Color;

void main(void)
{
    vec3 light = vec3(0.0, 0.7, 0.7); // Light source in view coordinates

	// Calculate gradients here
	float offset = 1.0 / 256.0; // texture size, same in both directions

    //    bs = b[s+1, t] - b[s, t]
    //    bt = b[s, t+1] - b[s, t]
    float bs = 10*(texture(texUnit, outTexCoord + vec2(offset, 0.0)) - texture(texUnit, outTexCoord)).x;
    float bt = 10*(texture(texUnit, outTexCoord + vec2(0.0, offset)) - texture(texUnit, outTexCoord)).y;

    //    vec3 normal = normalize(out_Normal);

    // view coordinates
    //    vec3 normal = out_Normal + bs*Ps + bt*Pt;

    // texture coordinates
    mat3 mvt = transpose(mat3(Ps, Pt, out_Normal));
    vec3 normal = vec3(bs, bt, 1);

    normal = normalize(normal);

	// Simplified lighting calculation.
	// A full solution would include material, ambient, specular, light sources, multiply by texture.
    //    out_Color = vec4( dot(normal, light)) * texture(texUnit, outTexCoord);
    vec3 lightT = mvt * light;
    out_Color = vec4(dot(normal, lightT));
}
