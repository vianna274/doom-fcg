#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da cor de cada vértice, definidas em "shader_vertex.glsl" e
// "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;
in vec3 vertex_color;
// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERE 0
#define BUNNY  1
#define PLANE  2
#define WALL   3
#define PISTOL 4
#define SHOT   5
#define COW   6
uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;
uniform sampler2D TextureImage3;
uniform sampler2D TextureImage4;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(camera_position - position_world);
    vec4 lightPos = vec4(10,0.3,10,1);
    vec4 l2 = normalize(lightPos - p);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);
    // l = v;
    vec4 r =  -l + 2 * n * (dot(n, l));
    vec4 r2 =  -l2 + 2 * n * (dot(n, l2));

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q;

    if ( object_id == PLANE )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        Kd = vec3(0.8,0.8,0.8);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.01,0.01,0.01);
        q = 0.9;
    }
    else if ( object_id == WALL )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        Kd = vec3(0.8,0.2,0.2);
        Ks = vec3(0.1,0.1,0.1);
        Ka = vec3(0.01,0.01,0.01);
        q = 10;
    }
    else if ( object_id == BUNNY )
    {
        // PREENCHA AQUI
        // Propriedades espectrais do coelho
        Kd = vec3(0.08,0.4,0.8);
        Ks = vec3(0.8,0.8,0.8);
        Ka = vec3(0.04,0.2,0.4);
        q = 32.0;
    }
    else if ( object_id == COW )
    {
        // PREENCHA AQUI
        // Propriedades espectrais da vaca
        Kd = vec3(1.0,0.0,0.0);
        Ks = vec3(1.0,0.0,0.0);
        Ka = vec3(0.04,0.2,0.4);
        q = 32.0;
    }
    else if ( object_id == PISTOL )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        Kd = vec3(0.8,0.2,0.2);
        Ks = vec3(0.2,0.2,0.2);
        Ka = vec3(0.0,0.0,0.0);
        q = 50.0;
    }
    else if ( object_id == SHOT )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        Kd = vec3(1.0,1.0,0.0);
        Ks = vec3(1.0,1.0,0.0);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
    }
    vec3 I = vec3(0.3,0.3,0.3);
    vec3 I2 = vec3(0.1,0.1,0.1);
    vec3 Ia = vec3(0.1,0.1,0.1); // PREENCHA AQUI o espectro da luz ambiente

    vec3 Kd0 = texture(TextureImage2, vec2(U,V)).rgb;
    vec4 h = (v + l)/length(v + l);
    vec4 h2 = (v + l2)/length(v + l2);
    vec3 ambient_term = Ka * Ia;
    vec3 phong_specular_term  = Ks * I * pow(max(0, dot(r, v)), q);
    vec3 phong_specular_term2  = Ks * I2 * pow(max(0, dot(r2, v)), q);
    vec3 blinn_phong_specular_term  = Ks * I * pow(max(0, dot(h, v)), q);
    vec3 blinn_phong_specular_term2  = Ks * I * pow(max(0, dot(h2, v)), q);

    if (object_id == PLANE) {
      Kd0 = texture(TextureImage0, vec2(U,V)).rgb;
    } else if (object_id == WALL) {
      Kd0 = texture(TextureImage1, vec2(U,V)).rgb;
    } else if (object_id == PISTOL) {
     Kd0 = texture(TextureImage2, vec2(U,V)).rgb;
    } else  {
      Kd0 = Kd;
    }
    vec3 lambert_diffuse_term = Kd0 * I * max(0, dot(n, l));
    vec3 lambert_diffuse_term2 = Kd0 * I2 * max(0, dot(n, l2));

    // Cor final do fragmento calculada com uma combinação dos termos difuso,
    // especular, e ambiente. Veja slide 134 do documento "Aula_17_e_18_Modelos_de_Iluminacao.pdf".
    vec3 color1 = phong_specular_term + lambert_diffuse_term;
    vec3 color2 = phong_specular_term2 + lambert_diffuse_term2;
    vec3 color3 = blinn_phong_specular_term + lambert_diffuse_term;
    vec3 color4 = blinn_phong_specular_term2 + lambert_diffuse_term2;

    color1 = color1/(2*(sqrt(pow(camera_position.x - position_world.x,2) +
                pow(camera_position.y - position_world.y,2) +
                pow(camera_position.z - position_world.z,2))));
    color2 = 2*color2/((sqrt(pow(lightPos.x - position_world.x,2) +
                pow(lightPos.y - position_world.y,2) +
                pow(lightPos.z - position_world.z,2))));
    color3 = color3/(2*(sqrt(pow(camera_position.x - position_world.x,2) +
                pow(camera_position.y - position_world.y,2) +
                pow(camera_position.z - position_world.z,2))));
    color4 = 2*color4/((sqrt(pow(lightPos.x - position_world.x,2) +
                pow(lightPos.y - position_world.y,2) +
                pow(lightPos.z - position_world.z,2))));

    color = ambient_term + color1 + color2;
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
    if (object_id == BUNNY)
      color = vertex_color;

    if( object_id == COW ){ //Iluminacao Blinn-Phong
        color = ambient_term + color3 + color4;
    }

}
