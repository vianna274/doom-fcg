#version 330 core

#define SPHERE 0
#define BUNNY  1
#define PLANE  2
#define WALL   3
#define PISTOL 4
#define SHOT   5
// Atributos de v�rtice recebidos como entrada ("in") pelo Vertex Shader.
// Veja a fun��o BuildTrianglesAndAddToVirtualScene() em "main.cpp".
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;

// Matrizes computadas no c�digo C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int object_id;

// Atributos de v�rtice que ser�o gerados como sa�da ("out") pelo Vertex Shader.
// ** Estes ser�o interpolados pelo rasterizador! ** gerando, assim, valores
// para cada fragmento, os quais ser�o recebidos como entrada pelo Fragment
// Shader. Veja o arquivo "shader_fragment.glsl".
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;
out vec3 vertex_color;
void main()
{
    gl_Position = projection * view * model * model_coefficients;

    position_world = model * model_coefficients;

    position_model = model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;
    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(camera_position - position_world);
    vec4 lightPos = vec4(10,0.3,10,1);
    vec4 l2 = normalize(lightPos - p);
    vec4 v = normalize(camera_position - p);
    vec4 r =  -l + 2 * n * (dot(n, l));
    vec4 r2 =  -l2 + 2 * n * (dot(n, l2));
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q;

    if (object_id == BUNNY) {
      Kd = vec3(0.08,0.4,0.8);
      Ks = vec3(0.8,0.8,0.8);
      Ka = vec3(0.00,0.00,0.00);
      q = 32.0;
    }
    vec3 I = vec3(0.3,0.3,0.3);
    vec3 I2 = vec3(0.1,0.1,0.1);
    vec3 Ia = vec3(0.1,0.1,0.1); // PREENCHA AQUI o espectro da luz ambiente
    vec3 ambient_term = Ka * Ia;
    vec3 phong_specular_term  = Ks * I * pow(max(0, dot(r, v)), q);
    vec3 phong_specular_term2  = Ks * I2 * pow(max(0, dot(r2, v)), q);
    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n, l));
    vec3 lambert_diffuse_term2 = Kd * I2 * max(0, dot(n, l2));
    vec3 color1 = phong_specular_term + lambert_diffuse_term;
    vec3 color2 = phong_specular_term2 + lambert_diffuse_term2;

    color1 = color1/(2*(sqrt(pow(camera_position.x - position_world.x,2) +
                pow(camera_position.y - position_world.y,2) +
                pow(camera_position.z - position_world.z,2))));
    color2 = 2*color2/((sqrt(pow(lightPos.x - position_world.x,2) +
                pow(lightPos.y - position_world.y,2) +
                pow(lightPos.z - position_world.z,2))));

    vertex_color = ambient_term + color1 + color2;
    vertex_color = pow(vertex_color, vec3(1.0,1.0,1.0)/2.2);
    // Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
    texcoords = texture_coefficients;
}
