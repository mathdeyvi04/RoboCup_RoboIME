##  Hierarquia

Do arquivo / pasta mais profundo, implementado mais cedo, at� o mais superficial, �ltimo implementado.

* [UserInterface](src/sobre_scripts/comuns/UserInterface.py)
  * Disponibilizar ferramentas de estiliza��o de apresenta��o no terminal.
  
* [Script](src/sobre_scripts/comuns/Script.py)
  * Argumentos intr�nsecos ao time est�o dispon�veis em [config.json](src/config.json).
  * Existe uma fun��o respons�vel pela compila��o de c�digo cpp.
  * Em geral, respons�vel por providenciar ferramentas de execu��o em terminal.

* [a_estrela](src/sobre_cpp/a_estrela)
  * M�dulo C++ focado no algoritmo A*, o qual foi criado em C++ para ser usado em Python.
    
    * [a_estrela.h](src/sobre_cpp/a_estrela/a_estrela.h)
      * Inicializa��o de vari�veis e structs b�sicas, como a �rvore representante de caminhos.
      * Cria��o de representa��o do campo como uma matriz de obst�culos.
      
    * [obtendo_possibilidades.py](src/sobre_cpp/a_estrela/obtendo_possibilidades.py)
      * Obtemos uma �rea circular centrada no agente que representar�
      a �rea preferencial de c�lculos para previs�o de caminhos.
      * Disponibiliza para _obtendo_possibilidades.h_ a �rea anteriormente citada, literalmente
      para que o c�digo n�o precise calcular todas as dist�ncias necess�rias! EXCELENTE IDEIA.
      * Alterar par�metros presentes no arquivo afetar� a otimiza��o.
      
    * [a_estrela.cpp](src/sobre_cpp/a_estrela/a_estrela.cpp)
      * Super c�digo de implementa��o do A* em C++. Tente l�-lo.
      * Cria��o de fun��es manipuladoras da �rvore.
      * Utiliza��o de um algoritmo insano para calcular dist�ncias, criado e desenvolvido pela equipe de Portugal exclusivamente para aprimorar a velocidade da busca pelo melhor caminho poss�vel.
      * Excelente demonstra��o de como codar como um Deus, agrade�o ao Miguel Abreu por disponibilzar essa obra de arte.
      * Acredito que, para posteriores avan�os, pode-se implementar m�todos de testes autom�ticos a fim de apresentar e verificar o algoritmo e respectivos avan�os.
    
    * [debug_main.cc](src/sobre_cpp/a_estrela/debug_main.cc)
      * C�digo para teste de fun��o desenvolvida dentro da pasta, vulgo a_estrela().
  
    * [ponte_de_ligacao_entre_python_e.cpp](src/sobre_cpp/a_estrela/ponte_de_ligacao_entre_python_e.cpp)
      * C�digo respons�vel por prover ferramentos de conex�o do ambiente Python com fun��es C++.
    
    * [Makefile](src/sobre_cpp/a_estrela/Makefile)
      * Respons�vel por providenciar o build do m�dulo. N�o ironicamente � o segundo
      arquivo mais importante.
      
* [preditor_de_curva_da_bola](src/sobre_cpp/preditor_de_curva_da_bola)
  * M�dulo C++ focado em previsibilidade de oportunidades com a bola.
  
    * [preditor_da_curva_da_bola.h](src/sobre_cpp/preditor_de_curva_da_bola/preditor_de_curva_da_bola.h)
      * Declara��o base de ponteiros e vetores que ser�o amplamente utilizados.
      
    * [preditor_da_curva_da_bola.cpp](src/sobre_cpp/preditor_de_curva_da_bola/preditor_de_curva_da_bola.cpp)
      * Implementa��o de fun��es de previs�o de interse��o e de atributos cinem�ticos.
      
    * [debug_main.cc](src/sobre_cpp/preditor_de_curva_da_bola/debug_main.cc)
      * C�digo para teste de fun��es implementadas.
  
    * [ponte_de_ligacao_entre_python_e.cpp](src/sobre_cpp/a_estrela/ponte_de_ligacao_entre_python_e.cpp)
      * C�digo respons�vel por prover ferramentos de conex�o do ambiente Python com fun��es C++.

* [ambientacao](src/sobre_cpp/ambientacao)
  * M�dulo C++ respons�vel por ferramentas de localiza��o e de visualiza��o de mundo.
  * Houve condensa��o de arquivos quando comparado com o original.
    
    * [Singular.h](src/sobre_cpp/ambientacao/Singular.h)
      * Cria��o e Implementa��o de Classe Abstrata que permitir� inst�ncias �nicas de qualquer classe.
      * Um show de genialidade.
  
    * [Geometria.h](src/sobre_cpp/ambientacao/Geometria.h)
      * Cria��o e Implementa��o de Classes Vetoriais de 2 Dimens�es e de 3 Dimens�es.
 
    * [Matriz.h](src/sobre_cpp/ambientacao/Matriz.h)
      * Cria��o e Implementa��o de Classe Matricial 4x4 que representar� diversas transforma��es.
      * Matem�tica mais profunda e divertida.
    
    * [Linha.h](src/sobre_cpp/ambientacao/Linha.h)
      * Cria��o e Implementa��o de Classe de Linha, representando retas e segmentos de reta.
      * Um show de �lgebra Linear, bem complexo matematicamente.
    
    * [RobovizDraw.h](src/sobre_cpp/ambientacao/RobovizDraw.h)
      * Cria��o e Implementa��o de fun��es esteticamente constru�das em C que fornecem 
      buffers de informa��es de desenho para o software RoboViz.
      * Par�metros alterados aqui influenciam como as coisas ser�o apresentadas 
      nos desenhos do RoboViz.
  
    * [RobovizLogger.h](src/sobre_cpp/ambientacao/RobovizLogger.h)
      * Header C++ extremamente mais complexo e focado em comunica��o via protocolos.
      * Disponibiliza ferramentas de apresenta��o de desenhos no RoboVIz.
      * Discuss�o interessante sobre destrutores comuns e virtuais.

    * [World.h](src/sobre_cpp/ambientacao/World.h)
      * Cria��o de vari�veis e structs que ser�o utilizadas na visualiza��o do mundo
      externo.
      * Par�metros alterados aqui influenciam diretamente em como o rob� visualiza
      o mundo externo.

    * [Ruido_de_Campo.h](src/sobre_cpp/ambientacao/World.h)
      * Cria��o e Implementa��o de classe respons�vel por prover previsibilidade de erros
      nos sensores.
      * Possui car�ter matem�tico forte e bem complexo.
      * Par�metros alterados aqui influenciam em medidas consideradas pelos agentes e,
      consequentemente, em a��es e c�lculos gerais. 
      * Houve altera��o de interpreta��o de l�gicas a partir do original.


