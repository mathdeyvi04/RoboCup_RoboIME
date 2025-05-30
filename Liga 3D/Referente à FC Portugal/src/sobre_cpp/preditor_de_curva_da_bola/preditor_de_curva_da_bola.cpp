#include <cmath>
#include "preditor_de_curva_da_bola.h"

/*
Cada vetor deste, ter� 600 elementos dispon�veis pois valor colocar:

v[ i     ] = componente_x
v[ i + 1 ] = componente_y
*/
float predicao_da_posicao   [ 600 ]; // Como Posi��o 
float predicao_da_velocidade[ 600 ]; // Como Vetor
float predicao_da_speed     [ 300 ]; // Denominamos Speed = M�dulo
int   quantidade_de_pontos_de_posicao;


void obter_previsao_de_intersecao_com_bola(
	/*
	Componentes da Posi��o do rob�.
	*/
	float x, 
	float y,
	/*
	M�ximo m�dulo de deslocamento do rob� por passo tempo
	*/
	float max_speed_do_robo_por_passo,
	/*
	Vetor de futuras posi��es da bola e seu respectiva quantidade
	de pontos.
	*/
	float posicao_da_bola[],
	float quantidade_de_pontos_de_posicao,
	/*
	Valores que ser�o retornados!
	*/
	float &ret_x,
	float &ret_y,
	float &ret_d
){
	/*
	Descri��o:
		Verifica a poss�vel interse��o do rob� com a bola. Note que a vari�vel max_speed...
		� para considerarmos que o rob� est� correndo com m�xima velocidade na dire��o da bola,
		a fim de termos uma estimativa.

		Caso haja interse��o, retorna a posi��o (x, y) e a respectiva dist�ncia relativas � interse��o.
		Caso n�o, retornar� a �ltima posi��o (x, y) e a respectiva dist�ncia relativas calculadas.

		Uma forma de saber se h� a possibilidade de contato � observar 
		a dist�ncia relativa dada.		
	Retorno:
		ret_x -> ponteiro para posi��o x do ponto de inters��o
		ret_y -> ponteiro para posi��o y do ponto de interse��o
		ret_d -> ponteiro para dist�ncia entre rob� e ponto de interse��o
	*/
	
	float max_distancia_de_contato = 0.2;
	
	int index = 0;
	while(1){
		/*
		Vamos pegar a dist�ncia relativa entre a posi��o futura do rob� e 
		verificar se h� interse��o
		*/
		float vec_x = posicao_da_bola[index++] - x;
		float vec_y = posicao_da_bola[index++] - y;
		
		// Dist�ncia percorrida pela bola nesse intervalo de tempo.
		// Vulgo intervalo de tempo para termos dois slots de posi��o registrados.
		float dist_sq = vec_x * vec_x + vec_y * vec_y;  

		if(
			(
				dist_sq < max_distancia_de_contato * max_distancia_de_contato
			) || (
				index >= quantidade_de_pontos_de_posicao
			)
		){

			ret_d = sqrtf(dist_sq);

			ret_x = (fabs(posicao_da_bola[index - 2]) > 1e-6) ? posicao_da_bola[index - 2] : 0;
			ret_y = (fabs(posicao_da_bola[index - 1]) > 1e-6) ? posicao_da_bola[index - 1] : 0;
			
			break;
		}
		
		max_distancia_de_contato += max_speed_do_robo_por_passo;
	}
}


void obter_previsao_cinematica(
	double pos_ball_x,
	double pos_ball_y,
	double vel_ball_x, 
	double vel_ball_y
){
	/*
	Descri��o:
		Tentaremos prever como a bola se comportar� cinematicamente.
		
		Os n�meros citados aqui n�o foram alterados do material base.
		Acredito que sejam experimentais.
	*/
	
	/*
	Por miguel abreu:
		acceleration = Rolling Drag Force * mass (constant = 0.026 kg)
    	acceleration = k1 * velocity^2 + k2 * velocity
    */
	const double coef_arrasto_quadratico = - 0.01;
	const double coef_arrasto_linear     = -    1;
	
	const double coef_arrasto_quadratico_x = (vel_ball_x < 0) ? - coef_arrasto_quadratico : coef_arrasto_quadratico;
	const double coef_arrasto_quadratico_y = (vel_ball_y < 0) ? - coef_arrasto_quadratico : coef_arrasto_quadratico;
	
	// Inicializamos os vetores.
	predicao_da_posicao   [0] = pos_ball_x;
	predicao_da_posicao   [1] = pos_ball_y;
	predicao_da_velocidade[0] = vel_ball_x;
	predicao_da_velocidade[1] = vel_ball_y;
	predicao_da_speed     [0] = sqrt(vel_ball_x * vel_ball_x + vel_ball_y * vel_ball_y);
	
	int index = 2;
	
	double delta_t = 0.02;
	double delta_t_sq = delta_t * delta_t;
	
	while(
		// Enquanto n�o preenchermos o vetor
		index < QUANT_DE_ELEMENTOS * 2
	){
		
		double acel_x = vel_ball_x * vel_ball_x * coef_arrasto_quadratico_x + vel_ball_x * coef_arrasto_linear;
		double acel_y = vel_ball_y * vel_ball_y * coef_arrasto_quadratico_y + vel_ball_y * coef_arrasto_linear;
		
		double dx = vel_ball_x * delta_t + 0.5 * acel_x * delta_t_sq;
		double dy = vel_ball_y * delta_t + 0.5 * acel_y * delta_t_sq;
		
		pos_ball_x += dx;
		pos_ball_y += dy;
		
		if(
			(
				// Uma m�trica para medirmos rapidamente dist�ncia
				(fabs(dx) + fabs(dy)) <  0.005
			) or (
				// Caso tenha passado do limite em x
				fabs(pos_ball_x) > 15
			) or (
				// Caso tenho passado do limite em y
				fabs(pos_ball_y) > 10
			)
		){
			break;
		}
		
		vel_ball_x += acel_x * delta_t;
		vel_ball_y += acel_y * delta_t;
		
		// Apesar de calcularmos em double, guardaremos em float.
		predicao_da_speed     [ index  / 2 ] = sqrt(vel_ball_x * vel_ball_x + vel_ball_y * vel_ball_y);
		
		predicao_da_velocidade[ index      ] = vel_ball_x;
		predicao_da_posicao   [ index++    ] = pos_ball_x;

		predicao_da_velocidade[ index      ] = vel_ball_y;
		predicao_da_posicao   [ index++    ] = pos_ball_y;


		// printf("\nIndex =  %d", index);
		// printf("\npos   = (%.3lf, %.3lf)", pos_ball_x, pos_ball_y);
		// printf("\nvel   = (%.3lf, %.3lf)", vel_ball_x, vel_ball_y);
		// printf("\n|vel| =  %.3lf\n", sqrt(vel_ball_x * vel_ball_x + vel_ball_y * vel_ball_y));
	}
	
	quantidade_de_pontos_de_posicao = index;
}
