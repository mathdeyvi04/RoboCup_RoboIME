/*
Matheus Deyvisson, 2025
*/

#include "a_estrela.h"

/*
Simplesmente loucura, nunca ouvi falar disso.

Apesar de termos instalado com pip install, esta biblioteca
pybind11 � somente de cabe�alho � exp�e tipos C++ em Python e
vice-versa, principalmente para criar vincula��es Python de
c�digo C++ existente.

Apesar de seu prop�sito ser integra��o com Python, ela foi
escrita em C++ e usada dentro de c�digo C++.

O compilador C++ gera um m�dulo nativo (ex: a_star.so)
No Python:
'''
import a_estrela
a_estrela.find_optimal_path()
'''
*/
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

/*
Usar 'using namespace pybind11' traria todas as fun��es e
vari�veis de pybind11; fazendo dessa forma, criamos apenas um
atalho, mantendo o c�digo mais seguro.

Ao ver 'py::' saiba que vem imediatamente de pybind11.
*/
namespace py = pybind11;
using namespace std;

py::array_t<float>
find_optimal_path(
    py::array_t<float> parametros_de_campo_e_de_situacao
){
    /*
    Descri��o:
        Em poucas palavras, implementa o algoritmo para que
        possa ser usado em python, permitindo que c�lculos
        intensivos do A* sejam realizados em C++ enquanto
        mant�m uma interface limpa com Python.

    Par�metros:
        Somente vendo a fun��o a_estrela(), dispon�vel
        no arquivo correspondente a_estrela.cpp, j� sanar� suas
        necessidades.
        
        Entretanto, um resumo r�pido � que:
            Vetor de valores espec�ficos que informam sobre 
            posi��o no campo, objetivo e seu local no campo,
            obst�culos e respectivas posi��es.  

    Retorno:
        Caminho a ser executado pelo agente.
    */

    /*
    Com isso passamos um array numpy do Python direto
    para C++ via pybind11. Essa biblioteca � t�o bizarra de
    impressionante.

    .request()
        Permite acessar os dados de forma eficiente, sem c�pia,
        manipulando diretamente a mem�ria compartilhada entre
        Python e C++.

    py::buffer_info
        � uma struct que exp�e o ponteiro para a mem�ria do array,
        tipo dos dados, shape da matriz dos dados e strides, que s�o
        o tamanho de cada item, em teoria.
    */
    py::buffer_info buffer_de_entrada = parametros_de_campo_e_de_situacao.request();
    int quantidade_de_parametros = buffer_de_entrada.shape[
        0  // Colocamos 0 pois assumimos que ser� um vetor unidimensional.
    ];

    /////////////////////////////////////////////////////////////////////
    /// Calculamos o caminho
    /////////////////////////////////////////////////////////////////////

    a_estrela(
        (float*) buffer_de_entrada.ptr,
        quantidade_de_parametros
    );

    /////////////////////////////////////////////////////////////////////
    /// Retornaremos o caminho obtido.
    /////////////////////////////////////////////////////////////////////

    // Alocamos mem�ria
    py::array_t<float> a_ser_retornado = py::array_t<float>(tamanho_do_caminho_final);

    // Obtemos informa��es de ponteiros.
    py::buffer_info buffer_de_saida = a_ser_retornado.request();

    float *ptr = (float*) buffer_de_saida.ptr;  // Pegamos o primeiro ponteiro do array.

    for(
        int index = 0;
        index < tamanho_do_caminho_final;
        index++
    ){
        /*
        Preenchemos o buffer_de_saida a partir do ponteiro.

        N�o podemos retornar o ponteiro de caminho_final pois
        ele ser� reutilizado e alterado.
        */
        ptr[index] = caminho_final[index];
    }

    return a_ser_retornado;
}

/*
Usamos esse m�dulo para possibilitar a adi��o de argumentos nomeados.

Define o operador _a, que � usado para associar um nome a um argumento
na defini��o da fun��o. Por exemplo, "parametros"_a � equivalente a
pybind11::arg("parametros").
*/
using namespace pybind11::literals;

/*
Definiremos um m�dulo a_estrela e criamos um objeto m
para configurar a liga��o entre C++ e Python.
*/
PYBIND11_MODULE(
    a_estrela,
    m
){
    m.doc() = "Module responsible for providing optimized design tools to obtain a valid path to an objective";

    m.def(
        "find_optimal_path",    // Nome da fun��o que ser� executada em Python.
        &find_optimal_path,     // Ponteiro para a fun��o C++
        R"pbdoc(
        Description:
            Computes the optimal path from a starting point while avoiding obstacles
            and considering motion constraints. The path is selected to be both 
            unblocked (collision-free) and fast enough within the given timeout.

            The algorithm can optionally handle:
            - Goals to be reached
            - Obstacles with varying influence (soft and hard radii)
            - Permission to go out of bounds

        Parameters:
            - start_x, start_y: Starting position.
            - allow_out_of_bounds: Whether the agent can leave the predefined area.
            - go_to_goal: Whether the agent should attempt to reach a given goal.
            - target_x, target_y: Optional goal coordinates.
            - timeout: Maximum computation time allowed.
            - [x, y, hard_radius, soft_radius, force] * n: List of obstacles, each defined
              by its position, collision radius, influence zone, and repulsion force.

        Return:
            A trajectory or path that avoids obstacles and is optimal with respect to
            time and space constraints.
        )pbdoc"
        "parametros"_a  // Nomeamos o argumento da fun��o.
    );
}
