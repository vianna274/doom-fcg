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
    vec4 l = normalize(vec4(1.0,1.0,0.5,0.0));
    l = normalize(camera_position - position_world);
    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);
    vec4 r =  -l + 2 * n * (dot(n, l));

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q;
    if ( object_id == SPHERE )
    {
        // PREENCHA AQUI as coordenadas de textura da esfera, computadas com
        // projeção esférica EM COORDENADAS DO MODELO. Utilize como referência
        // o slide 139 do documento "Aula_20_e_21_Mapeamento_de_Texturas.pdf".
        // A esfera que define a projeção deve estar centrada na posição
        // "bbox_center" definida abaixo.

        // Você deve utilizar:
        //   função 'length( )' : comprimento Euclidiano de um vetor
        //   função 'atan( , )' : arcotangente. Veja https://en.wikipedia.org/wiki/Atan2.
        //   função 'asin( )'   : seno inverso.
        //   constante M_PI
        //   variável position_model
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        float raio = length(bbox_center - bbox_max);
        vec4 p_ = bbox_center + raio* normalize(position_model - bbox_center);
        vec4 pvector = p_ - bbox_center;

        float px = pvector.x;
        float py = pvector.y;
        float pz = pvector.z;
        float ro = sqrt(pow(px,2) + pow(py,2) + pow(pz,2));
        float omega = atan(px,pz);
        float delta = asin(py/ro);
        U = (omega + M_PI)/(2*M_PI);
        V = (delta + (M_PI_2))/(M_PI);
    }
    else if ( object_id == PLANE )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        Kd = vec3(0.8,0.2,0.2);
        Ks = vec3(0.2,0.2,0.2);
        Ka = vec3(0.0,0.0,0.0);
        q = 1.0;
    }
    else if ( object_id == WALL )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        Kd = vec3(0.8,0.2,0.2);
        Ks = vec3(0.2,0.2,0.2);
        Ka = vec3(0.0,0.0,0.0);
        q = 50.0;
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
    vec3 I = vec3(0.2,0.2,0.2);
    // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
    vec3 Ia = vec3(0.05,0.05,0.05); // PREENCHA AQUI o espectro da luz ambiente

    vec3 Kd0 = texture(TextureImage2, vec2(U,V)).rgb;
    vec3 ambient_term = Ka * Ia;
    vec3 phong_specular_term  = Ks * I * pow(max(0, dot(r, v)), q);

    if (object_id == PLANE) {
      Kd0 = texture(TextureImage0, vec2(U,V)).rgb;
    } else if (object_id == WALL) {
      Kd0 = texture(TextureImage1, vec2(U,V)).rgb;
      ambient_term = vec3(0,0,0);
      phong_specular_term = vec3(0,0,0);
    } else if (object_id == PISTOL) {
     Kd0 = texture(TextureImage2, vec2(U,V)).rgb;
   } else if (object_id == SHOT) {
      Kd0 = Kd;
    }
    vec3 lambert_diffuse_term = Kd0 * I * max(0, dot(n, l));

    // Termo ambiente

    // Termo especular utilizando o modelo de iluminação de Phong

    // Cor final do fragmento calculada com uma combinação dos termos difuso,
    // especular, e ambiente. Veja slide 134 do documento "Aula_17_e_18_Modelos_de_Iluminacao.pdf".
    color = lambert_diffuse_term + ambient_term + phong_specular_term;

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}
