/*
Matheus Deyvisson, 2025.

Para mais coment�rios e explica��es acerca do que est� sendo feito aqui,
sugiro que leia o arquivo de mesmo nome dispon�vel na pasta de a_estrela.
*/
#include "preditor_de_curva_da_bola.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
using namespace std;

py::array_t<float> obter_previsao_de_atributos_cinematicos(
	py::array_t<float> parametros
){
	/*
	Descri��o:
		Faz a mesma coisa que aquela fun��o de prever cinem�tica.
		Fornece 
	*/
	
	py::buffer_info buffer_de_entrada = parametros.request();
	float* parametros_ptr = (float*) buffer_de_entrada.ptr  ;
	
	float pos_ball_x = parametros_ptr[ 0 ];
	float pos_ball_y = parametros_ptr[ 1 ];
	float vel_ball_x = parametros_ptr[ 2 ];
	float vel_ball_y = parametros_ptr[ 3 ];
	
	obter_previsao_cinematica(
		pos_ball_x,
		pos_ball_y,
		vel_ball_x,
		vel_ball_y
	);
	
	py::array_t<float> a_ser_retornado = py::array_t<float>(
		quantidade_de_pontos_de_posicao * ( 2.5 )
	);
	py::buffer_info buffer_de_saida = a_ser_retornado.request();
	float *ptr = (float*) buffer_de_saida.ptr;
	
	int index = 0;
	
	while(
		index < quantidade_de_pontos_de_posicao
	){
		ptr[index] = predicao_da_posicao[index];
		
		index++;
	}
	
	/*
	Observe que para cada loop, come�amos com index = 0.
	� primeira vista, n�o faz sentido. Entretanto, o ponteiro 
	iniciado � shiftado de tal que forma que ele indique o primeiro
	elemento do pr�ximo array e isso nos permite a utiliza��o de
	indexs mais concisos.
	*/
	ptr += quantidade_de_pontos_de_posicao;
	index = 0;
	
	while(
		index < quantidade_de_pontos_de_posicao
	){
		ptr[index] = predicao_da_velocidade[index];
		
		index++;
	}
	
	ptr += quantidade_de_pontos_de_posicao;
	index = 0;
	
	while(
		index < quantidade_de_pontos_de_posicao / 2
	){
		ptr[index] = predicao_da_speed[index];
		
		index++;
	}
	
	return a_ser_retornado;
}


py::array_t<float> obter_previsao_de_intersecao(
	py::array_t<float> parametros
){
	/*
	
	*/
	
	py::buffer_info buffer_de_entrada = parametros.request();
	float* param_ptr = (float*) buffer_de_entrada.ptr;
	int quantidade_de_parametros = buffer_de_entrada.shape[0];
	
	float x = param_ptr[0];
	float y = param_ptr[1];
	float max_speed = param_ptr[2];
	float* pos_ball = param_ptr + 3;
	float ret_x, ret_y, ret_d;
	
	obter_previsao_de_intersecao_com_bola(
		x,
		y,
		max_speed,
		pos_ball,
		quantidade_de_parametros - 3,
		/*
		Resultado ser� retornado para os seguintes endere�os de mem�ria.
		*/
		ret_x,
		ret_y,
		ret_d
	)
	
	
	py::array_t<float> a_ser_retornado = py::array_t<float>( 3 );
	py::buffer_info buffer_de_saida = a_ser_retornado.request();
	float* ptr = (float*) buffer_de_saida.ptr;
	
	ptr[ 0 ] = ret_x;
	ptr[ 1 ] = ret_y;
	ptr[ 2 ] = ret_d;
	
	return a_ser_retornado;
}

// Chame de kinematic_predict

using namespace pybind11::literals;

PYBIND11_MODULE(
	preditor_de_curva_de_bola,
	m
) {
	m.doc() = "Preditor de Curva de Bola, obtendo atributos cinem�ticos e trajet�ria aproximada.";
	
	m.def(
		"kinematic_predict",
		&obter_previsao_de_atributos_cinematicos,
		"parametros"_a.
	);
	
	m.def(
		"obter_intersecao",
		&obter_previsao_de_intersecao,
		"parametros"_a
	);
}

