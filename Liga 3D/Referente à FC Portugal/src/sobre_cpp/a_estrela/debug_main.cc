/*
Matheus Deyvisson, 2025

Os arquivos com extens�o .cc (ou .cpp, .cxx, etc.) s�o
arquivos de c�digo-fonte em C++. Eles cont�m a implementa��o
de fun��es, classes e l�gica do programa, que depois s�o
compilados para gerar execut�veis ou bibliotecas (como .so
no Linux ou .dll/.pyd no Windows).

Oq eu entendi: Apenas C�digo C++ para linux.
*/

#include "a_estrela.h"
#include <chrono>
#include <iostream>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

std::chrono::_V2::system_clock::time_point inicio, fim;

float parametros[] = {
    /*
    N�o me atrevo a escrever outra coisa.
    */
    15.78,-0.07, //start
    1,1, //out of bounds? go to goal?
    0,0, //target (if not go to goal)
    500000, // timeout
    -10,0,1,5,5,
    -10,1,1,7,10,
    -10,-7,0,5,1
};

int quantidade_de_parametros = sizeof( parametros ) / sizeof(float);

int main(){

    inicio = high_resolution_clock::now();

    a_estrela(parametros, quantidade_de_parametros);

    fim = high_resolution_clock::now();

    std::cout << duration_cast<microseconds>(fim - inicio).count() << "us (inclui valores de inicializa��o.\n";

    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    inicio = high_resolution_clock::now();

    a_estrela(parametros, quantidade_de_parametros);

    fim = high_resolution_clock::now();

    std::cout << duration_cast<microseconds>(fim - inicio).count() << "us.\n";

}

















