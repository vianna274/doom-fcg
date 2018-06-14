# Final work for the Fundamentals of Computer Graphics

We created a Doom-like game using our knowledge of CG by using OpenGL and C++.

## Libraries required:

*Needs to be filled*

- SFML

### Compatible with Windows and Linux.

## Requirements:

- A sua aplicação deve possibilitar interação em tempo real. :heavy_check_mark:

- A sua aplicação deve possuir algum objetivo e lógica de controle não-trivial. :heavy_check_mark:

- A sua aplicação deve utilizar as matrizes que vimos em aula para transformações geométricas (Model matrix), projeções (Projection matrix), e especificação do sistema de coordenadas da câmera (View matrix).
Você não pode utilizar bibliotecas existentes para o cálculo de câmera, transformações, etc. Por exemplo, as funções a seguir, comumente utilizadas em tutoriais disponíveis na Web, não podem ser utilizadas:
gluLookAt(), gluOrtho2D(), gluPerspective(), gluPickMatrix(), gluProject(), gluUnProject(), glm::lookAt(), glm::ortho(), glm::perspective(), glm::pickMatrix(), glm::rotate(), glm::scale(), glm::translate(), dentre outras.

- A sua aplicação deve possibilitar interação com o usuário através do mouse e do teclado. :heavy_check_mark:

- A qualidade da apresentação do trabalho final, além da presença da dupla nos dias de apresentações de outros colegas, irá contar para a nota final do trabalho. :heavy_check_mark:

### A sua aplicação deve incluir implementação dos seguintes conceitos de Computação Gráfica:

- Objetos virtuais representados através de malhas poligonais complexas (malhas de triângulos). :heavy_check_mark:

- No mínimo sua aplicação deve incluir o modelo geométrico "cow.obj".

- Quanto maior a variedade de modelos geométricos, melhor. :heavy_check_mark:

- Transformações geométricas de objetos virtuais. :heavy_check_mark:

- Através da interação com o teclado e/ou mouse, o usuário deve poder controlar transformações geométricas aplicadas aos objetos virtuais (não somente controle da câmera). :heavy_check_mark:

- Controle de câmeras virtuais. :heavy_check_mark:

- No mínimo sua aplicação deve implementar uma câmera look-at e uma câmera livre, conforme praticamos no Laboratório 2.

- No mínimo um objeto virtual deve ser copiado com duas ou mais instâncias, isto é, utilizando duas ou mais Model matrix aplicadas ao mesmo conjunto de vértices. :heavy_check_mark:

- Testes de intersecção entre objetos virtuais. :heavy_check_mark:

- No mínimo sua aplicação deve utilizar três tipos de teste de intersecção (por exemplo, um teste cubo-cubo e um teste cubo-plano).

- Estes testes devem ter algum propósito dentro da lógica de sua aplicação. :heavy_check_mark:

- Modelos de iluminação de objetos geométricos. :heavy_check_mark:

- No mínimo sua aplicação deve incluir objetos com os seguintes modelos de iluminação: difusa (Lambert) e Blinn-Phong.

### No mínimo sua aplicação deve incluir objetos com os seguintes modelos de interpolação para iluminação:

- No mínimo um objeto com modelo de Gourad: o modelo de iluminação é avaliado para cada vértice usando suas normais, gerando uma cor, a qual é interpolada para cada pixel durante a rasterização.

- No mínimo um objeto com modelo de Phong: as normais de cada vértice são interpoladas para cada pixel durante a rasterização, e o modelo de iluminação é avaliado para cada pixel, utilizando estas normais interpoladas.

- Mapeamento de texturas. :heavy_check_mark:

- No mínimo um objeto virtual de sua aplicação deve ter sua cor definida através de uma textura definida através de uma imagem. :heavy_check_mark:
