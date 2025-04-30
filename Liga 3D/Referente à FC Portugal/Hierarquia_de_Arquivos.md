##  Hierarquia

Do arquivo / pasta mais profundo, implementado mais cedo, até o mais superficial, último implementado.

* [UserInterface](src/sobre_scripts/comuns/UserInterface.py)
  * Disponibilizar ferramentas de estilização de apresentação no terminal.
  
* [Script](src/sobre_scripts/comuns/Script.py)
  * Argumentos intrínsecos ao time estão disponíveis em [config.json](src/config.json).
  * Existe uma função responsável pela compilação de código cpp.
  * Em geral, responsável por providenciar ferramentas de execução em terminal.

* [a_estrela](src/sobre_cpp/a_estrela)
  * Módulo C++ focado no algoritmo A*, o qual foi criado em C++ para ser usado em Python.
    
    * [a_estrela.h](src/sobre_cpp/a_estrela/a_estrela.h)
      * Inicialização de variáveis e structs básicas, como a árvore representante de caminhos.
      * Criação de representação do campo como uma matriz de obstáculos.
      
    * [obtendo_possibilidades.py](src/sobre_cpp/a_estrela/obtendo_possibilidades.py)
      * Obtemos uma área circular centrada no agente que representará
      a área preferencial de cálculos para previsão de caminhos.
      * Disponibiliza para _obtendo_possibilidades.h_ a área anteriormente citada, literalmente
      para que o código não precise calcular todas as distâncias necessárias! EXCELENTE IDEIA.
      * Alterar parâmetros presentes no arquivo afetará a otimização.
      
    * [a_estrela.cpp](src/sobre_cpp/a_estrela/a_estrela.cpp)
      * Super código de implementação do A* em C++. Tente lê-lo.
      * Criação de funções manipuladoras da árvore.
      * Utilização de um algoritmo insano para calcular distâncias, criado e desenvolvido pela equipe de Portugal exclusivamente para aprimorar a velocidade da busca pelo melhor caminho possível.
      * Excelente demonstração de como codar como um Deus, agradeço ao Miguel Abreu por disponibilzar essa obra de arte.
      * Acredito que, para posteriores avanços, pode-se implementar métodos de testes automáticos a fim de apresentar e verificar o algoritmo e respectivos avanços.
    
    * [debug_main.cc](src/sobre_cpp/a_estrela/debug_main.cc)
      * Código para teste de função desenvolvida dentro da pasta, vulgo a_estrela().
  
    * [ponte_de_ligacao_entre_python_e.cpp](src/sobre_cpp/a_estrela/ponte_de_ligacao_entre_python_e.cpp)
      * Código responsável por prover ferramentos de conexão do ambiente Python com funções C++.
    
    * [Makefile](src/sobre_cpp/a_estrela/Makefile)
      * Responsável por providenciar o build do módulo. Não ironicamente é o segundo
      arquivo mais importante.
      
* [preditor_de_curva_da_bola](src/sobre_cpp/preditor_de_curva_da_bola)
  * Módulo C++ focado em previsibilidade de oportunidades com a bola.
  
    * [preditor_da_curva_da_bola.h](src/sobre_cpp/preditor_de_curva_da_bola/preditor_de_curva_da_bola.h)
      * Declaração base de ponteiros e vetores que serão amplamente utilizados.
      
    * [preditor_da_curva_da_bola.cpp](src/sobre_cpp/preditor_de_curva_da_bola/preditor_de_curva_da_bola.cpp)
      * Implementação de funções de previsão de interseção e de atributos cinemáticos.
      
    * [debug_main.cc](src/sobre_cpp/preditor_de_curva_da_bola/debug_main.cc)
      * Código para teste de funções implementadas.
  
    * [ponte_de_ligacao_entre_python_e.cpp](src/sobre_cpp/a_estrela/ponte_de_ligacao_entre_python_e.cpp)
      * Código responsável por prover ferramentos de conexão do ambiente Python com funções C++.

* [ambientacao](src/sobre_cpp/ambientacao)
  * Módulo C++ responsável por ferramentas de localização, de visualização de mundo e de conexão
  com RoboViz.
  * Houve condensação de arquivos, quando comparado com o original, e alterações consideráveis em algumas lógicas.
    
    * [Singular.h](src/sobre_cpp/ambientacao/Singular.h)
      * Criação e Implementação de Classe Abstrata que permitirá instâncias únicas de qualquer classe.
      * Um show de genialidade.
  
    * [Geometria.h](src/sobre_cpp/ambientacao/Geometria.h)
      * Criação e Implementação de Classes Vetoriais de 2 Dimensões e de 3 Dimensões.
 
    * [Matriz.h](src/sobre_cpp/ambientacao/Matriz.h)
      * Criação e Implementação de Classe Matricial 4x4 que representará diversas transformações.
      * Matemática mais profunda e divertida.
    
    * [Linha.h](src/sobre_cpp/ambientacao/Linha.h)
      * Criação e Implementação de Classe Linear, representando retas e segmentos de reta.
      * Um show de Álgebra Linear, bem complexo matematicamente.
    
    * [RobovizDraw.h](src/sobre_cpp/ambientacao/RobovizDraw.h)
      * Criação e Implementação de funções esteticamente construídas em C que fornecem 
      buffers de informações de desenho para o software RoboViz.
      * **Parâmetros alterados aqui influenciam como as coisas serão apresentadas 
      nos desenhos do RoboViz.**
  
    * [RobovizLogger.h](src/sobre_cpp/ambientacao/RobovizLogger.h)
      * Header C++ extremamente mais complexo e focado em comunicação via protocolos.
      * Disponibiliza ferramentas de apresentação de desenhos no RoboViz.
      * Discussão interessante sobre destrutores comuns e virtuais.

    * [World.h](src/sobre_cpp/ambientacao/World.h)
      * Criação de variáveis e structs que serão utilizadas na visualização do mundo
      externo.
      * **Parâmetros alterados aqui influenciam na visualização externa.**

    * [Ruido_de_Campo.h](src/sobre_cpp/ambientacao/Ruido_de_Campo.h)
      * Criação e Implementação de classe responsável por prover previsibilidade de erros
      nos sensores.
      * Possui forte caráter matemático.
      * **Parâmetros alterados aqui influenciam no funcionamento global.**
      * Houve alteração de interpretação de lógicas a partir do original.

    * [RobovizField.h](src/sobre_cpp/ambientacao/RobovizField.h)
      * Criação de classe representadora do campo visualizado pelo Roboviz.
      * Diversas definições de constantes e de structs essenciais para representação de elementos do campo são implementadas aqui.
      * Sugiro a leitura calma deste arquivo, pois **parâmetros alterados aqui
      influenciam no funcionamento global e na visualização externa.**.

    * [RobovizField.cpp](src/sobre_cpp/ambientacao/RobovizField.cpp)
      * Implementação de diversos métodos de visualização e de atualização de
      elementos no Roboviz.
      * **Parâmetros alterados aqui influenciam no funcionamento global.**
      * Arquivo que converge todos os outros derivados de Roboviz e World.h.
      * Houve uma alteração significativa nas funções de desenho de elementos, sugiro comparação com Original.
