#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
};

uniform Light light;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 objectColor;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;  // 环境光照
  	
    // diffuse 
    vec3 norm = normalize(Normal);  // 法向量
    vec3 lightDir = normalize(lightPos - FragPos);  // 入射方向
    float diff = max(dot(norm, lightDir), 0.0);  // 点乘
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);  // 视线方向
    vec3 reflectDir = reflect(-lightDir, norm);  // 反射方向
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // 计算视线方向和反射方向点乘
    vec3 specular = light.specular * (spec * material.specular);
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 