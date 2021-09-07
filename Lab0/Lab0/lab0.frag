#version 150

in vec3 Normal;
in vec3 Frag_pos;
in vec2 Frag_tex_coord;

uniform sampler2D example_texture;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 object_color;

//out vec4 Frag_color;
out vec4 out_Color;

void main(void)
{
    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(lightPos - Frag_pos);

    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * lightColor;

    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specular_strength = 0.5;
    vec3 view_dir = normalize(vec3(0,0,0) - Frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * object_color;
    out_Color = vec4(result, 1.0) + texture(example_texture, Frag_tex_coord);
}

