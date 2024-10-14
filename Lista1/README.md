1. **O que é a GLSL?**  
GLSL é a linguagem de programação usada para escrever shaders no OpenGL. Os dois tipos obrigatórios de shaders são Vertex Shader, que processa cada vértice, aplicando transformações como projeção e modelagem e o Fragment Shader, que define a cor de cada pixel.

2. **O que são primitivas gráficas?**  
Primitivas gráficas são os elementos básicos usados para construir formas no OpenGL, como pontos, linhas e triângulos. O armazenamento dos vértices na OpenGL é feito usando buffers como o VBO.

3. **Explique VBO, VAO e EBO**:  
- VBO: Armazena os dados dos vértices na GPU.  
- VAO: Gerencia e organiza diferentes VBOs para definir como os vértices serão interpretados.  
- EBO: Armazena índices que determinam a ordem dos vértices, evitando duplicação de dados.

8. **Configuração de buffers para o triângulo**:  
   - **VBO**: Armazena as posições dos vértices P1, P2 e P3, juntamente com suas respectivas cores (vermelho, verde, azul).  
   - **VAO**: Vincula o VBO e define como os dados dos vértices e cores serão lidos.  
   - **EBO**: Armazena os índices dos vértices que formam o triângulo.  
   No vertex shader, esses atributos (posição e cor) seriam identificados, a cor seria enviada para o fragment shader.
