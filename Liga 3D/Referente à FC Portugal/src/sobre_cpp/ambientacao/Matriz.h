#ifndef MATRIZ_H
#define MATRIZ_H

#include "Geometria.h"
#include <stdio.h>

// Valores para um espa�o tridimensional.
#define M_LINHAS  4
#define M_COLUNAS 4
#define M_TAMANHO M_COLUNAS * M_LINHAS

class Matriz {
	/*
	Descri��o:
		N�o ironicamente apenas uma classe para representarmos 
		opera��es matriciais, entretanto, de forma inteligente.
		
		Pois usaremos uma matriz de 4 dimens�es como um vetor!
		Apesar dos autores terem constru�do de tal forma que seja para
		4x4, vamos construir de forma mais gen�rica.
		
		Trata-se de uma matem�tica mais profunda. Sugiro que verifique
		o seguinte link para melhor embasamento: 
	https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html
		
		
	Cr�ditos:
	- @author Nuno Almeida (nuno.alm@ua.pt)
   	- Adapted - Miguel Abreu
	*/
public:
	
	float conteudo[M_TAMANHO]; 
	
	///////////////////////////////////////////////////////////////////////
	/// Construtores e Destrutores
	///////////////////////////////////////////////////////////////////////
	
	Matriz() {
		/*
		Vamos retornar uma esp�cie de matriz identidade. Digo esp�cie
		porque n�o necessariamente ser� quadrada, depender� se 
		M_LINHAS = M_COLUNAS.
		
		Suponha M_LINHAS e M_COLUNAS, n�o necessariamente iguais.
		
		Imagine um loop percorrendo pelo index:
		
		  0,           1,             2, ..., M_C - 1
		M_C,     M_C + 1,       M_C + 2, ..., 2 * M_C - 1
	2 * M_C, 2 * M_C + 1, 2 * (M_C + 1), ...
		
		Observe que o termo que recebe 1 necessariamente � um m�ltiplo
		da quantidade M_COLUNAS + 1.
		
		Sendo assim, temos nosso algoritmo.
		*/
		
		for(
			int index = 0;
			index < M_TAMANHO;
			index++
		){
			
			conteudo[ index ] = index % (M_COLUNAS + 1) == 0;
		}
	}
	
	
	Matriz(
		const float entradas[]
	) {
		/*
		Contruir matriz baseado no valores presentes neste vetor de entrada.
		
		A matriz receber� apenas at� que a quantidade dispon�vel se estabele�a.
		*/
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			conteudo[i] = entradas[i];
		}
	}
	
	
	Matriz(
		const Matriz& outra_matriz
	) {
		/*
		Construir matriz baseado em outra.
		*/
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			conteudo[i] = outra_matriz.conteudo[i];
		}
	}
	
	
	Matriz(
		const Vetor3D& vetor_3d
	) {
		/*
		ATEN��O: Matriz de Transla��o!
		
		Criar� uma matriz, neste caso de 4 dimens�es, a partir de um
		vetor (tx, ty, tz).
		
		O que se proceder�:
		
		(Matriz)(vx, vy, vz, 1)^T = (vx + tx, vy + ty, vz + tz, 1)^T
		*/
		
		float vetor_4d[] = {
			vetor_3d.x,
			vetor_3d.y,
			vetor_3d.z,
			1
		};
		int indicador_de_componente = 0;  // Temos garantio que ser� 0, 1, ou 2.
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			conteudo[i] = ( 
			
				// Condi��o: Se n�o estiver na �ltima coluna.
				i != (M_COLUNAS * (indicador_de_componente + 1) - 1)
				
			) ? (
			
				// Se verdadeiro, preenchemos como se fosse identidade.
				i % (M_COLUNAS + 1) == 0
				
			) : (
			
				// Se false, preenchemos com a componente.
				vetor_4d[indicador_de_componente++]
				
			);
		}
	}
	
	
    ~Matriz() {}
	
	///////////////////////////////////////////////////////////////////////
	/// Manipuladores
	///////////////////////////////////////////////////////////////////////
	
	
	
	
	
	
	
};










#endif // Matriz_h
