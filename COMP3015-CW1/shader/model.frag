

#version 460

in vec3 FragPos;
in vec3 Normal;
in vec2 TextureCoord;
layout (location = 0) out vec4 FragColor;

struct Material {
    vec3 amibent;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform sampler2D texture1;
uniform Material material;
uniform PointLight pointLights[1];
uniform vec3 viewPos;
uniform bool openLight;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 color;
    color = texture(texture1, TextureCoord).rgb;

    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.f);
    // combine results
    vec3 ambient = light.ambient * color;
    vec3 diffuse = light.diffuse * diff * color;
    vec3 specular = light.specular * spec;

    vec3 result;
    if(!openLight) {
        result = ambient;
    }
    else {
        result = ambient + diffuse + specular;
    }
    return result;
}


void main() {
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = vec3(0.f);
    for(int i = 0; i < 1; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    

    FragColor = vec4(result, 1.0);
}
