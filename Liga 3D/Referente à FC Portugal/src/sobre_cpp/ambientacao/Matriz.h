#ifndef MATRIZ_H
#define MATRIZ_H

#include "Geometria.h"

// Valores para um espa�o tridimensional.
#define M_LINHAS  4
#define M_COLUNAS 4
#define M_TAMANHO M_COLUNAS * M_LINHAS

class Matriz {
	/*
	Descri��o:
		Classe respons�vel por representar matrizes em geral, em especial
		matrizes 4x4 e providenciar ferramentas necess�rias para
		transforma��es de transla��o, rota��o e escalamento.
		
		Apesar de ser uma matriz, usaremos um vetor para represent�-la.
				
		Este c�digo tratar� de uma matem�tica mais profunda. Para isso:
		
		- Sugiro que verifique o seguinte link para melhor embasamento: 
	    
		Site explicando sobre essas transforma��es em matrizes 4x4:
			https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html
		
		- V�deo no Youtube explicando sobre porque utilizamos 4x4:
			https://youtu.be/Do_vEjd6gF0
		
			Resposta: 
				Matriz 3x3 conseguem representar perfeitamente transforma��es 
				lineares como rota��o e escalamento. Entretanto, n�o conseguem
				representar transforma��es n�o lineares, como TRANSLA��O.
				Portanto, usamos 4x4 que conseguem ambos.
		
	Testes:
		Foi criado um arquivo .cpp que executou cada uma das aplica��es
		implementas aqui. Caso novas atualiza��es sejam providenciadas, sugiro o mesmo.
		
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
	
	// Matriz de Transla��o
	Matriz(
		const Vetor3D& vetor_3d
	) {
		/*
		ATEN��O: Matriz de Transla��o!
		
		Criar� uma matriz, neste caso de 4 dimens�es, a partir de um
		vetor (tx, ty, tz).
		
		O que essa matriz ser� capaz de fazer:
		
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
	
	
	// Outra forma de matriz de transla��o
	static Matriz obter_matriz_de_translacao(
		float tx,
		float ty,
		float tz
	) {

		const float temp[M_TAMANHO] = {
								        1, 0, 0, tx,
								        0, 1, 0, ty,
								        0, 0, 1, tz,
								        0, 0, 0,  1
								   	  };
								   	  
		return Matriz(temp);
	}
	
    ~Matriz() {}
	
	///////////////////////////////////////////////////////////////////////
	/// Manipuladores
	///////////////////////////////////////////////////////////////////////
	
	void setar(
		unsigned int index_a_ser_setado,
		float valor_a_ser_setado
	) {
		/*
		Caso esteja sendo manipulado como um vetor.
		*/
		conteudo[index_a_ser_setado] = valor_a_ser_setado;
	}
	void setar(
		unsigned int linha_a_ser_setada,
		unsigned int coluna_a_ser_setada,
		float valor_a_ser_setado
	) {
		/*
		Caso esteja sendo manipulado como matriz.
		*/
		
		conteudo[
			M_COLUNAS * linha_a_ser_setada + coluna_a_ser_setada
		] = valor_a_ser_setado;
	}
	
	
	float obter(
		unsigned int index_a_ser_obtido
	) {
		/*
		Caso esteja sendo manipulado como um vetor.
		*/
		return conteudo[index_a_ser_obtido];
	}
	float obter(
		unsigned int linha_a_ser_obtido,
		unsigned int coluna_a_ser_obtido
	) {
		/*
		Caso esteja sendo manipulado como matriz.
		*/
		
		return conteudo[
			M_COLUNAS * linha_a_ser_obtido + coluna_a_ser_obtido
		];
	}
	
	
	///////////////////////////////////////////////////////////////////////
	/// M�todos de Aritm�tica
	///////////////////////////////////////////////////////////////////////
	
	
	Matriz operator+(
		const Matriz& outra_matriz
	) const {
		/*
		Descri��o:
			Gerar� nova matriz soma.
		*/
		
		float temp[M_TAMANHO];
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			temp[i] = (*this).conteudo[i] + outra_matriz.conteudo[i];
		}
		
		return Matriz(temp);
	}
	
	
	Matriz operator-(
		const Matriz& outra_matriz
	) {
		/*
		Gerar� matriz diferen�a.
		*/
		
		float temp[M_TAMANHO];
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			temp[i] = (*this).conteudo[i] - outra_matriz.conteudo[i];
		}
		
		return Matriz(temp);
	}
	
	
	/*
	Multiplica��o de Matrizes
	*/
	Matriz operator*(
		const Matriz& outra_matriz
	){

		float temp[M_TAMANHO];
		
		for(
			int linha = 0;
			linha < M_LINHAS;
			linha++
		){
			for(
				int coluna = 0;
				coluna < M_COLUNAS;
				coluna++
			){
				// Setamos como se fosse matriz nula.
				temp[M_COLUNAS * linha + coluna] = 0;
				
				// Construimos a soma para cada entrada.
				for(
					int lin_col_ja_somada = 0;
					lin_col_ja_somada < M_COLUNAS;
					lin_col_ja_somada++
				){
					
					temp[
						M_COLUNAS * linha + coluna
					] += (*this).conteudo[
						M_COLUNAS * linha  + lin_col_ja_somada
					] * outra_matriz.conteudo[
						M_COLUNAS * coluna + lin_col_ja_somada
					];
				}
				
			}
		}
		
		return Matriz(temp);
	}
	
	
	/*
	Multiplica��o de Matriz por escalar
	*/
	Matriz operator*(
		const float escalar
	){
		
		float temp[M_TAMANHO];
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			temp[i] = conteudo[i] * escalar;
		}
		
		return Matriz(temp);
	}
	
	
	/*
	Multiplica��o de Matriz de Transla��o por Vetor Quadridimensional
	*/
	Vetor3D operator*(
		const Vetor3D& vetor
	){
		/*
		Aplica��o do algoritmo da matriz de transla��o.
		Verifique:
		https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html
		
		Foi um aprimoramento gigante no algoritmo, experimente ver como 
		est� no original.
		
		N�o � exatamente garantido que a submatriz do lado esquerdo
		seja a identidade 3x3.
		
		*/
		
		float temp[3] = {0, 0, 0};
		
		int index = 0;
		for(
			// Iterar sobre elementos da matriz
			int i = 0;
			i < 12;  // garantia de que � 4x4
			i++
		){
			if(
				i > 4 * (index + 1)
			){
				index++;
			}
			
			temp[index] += conteudo[ i ] * ( (i + 1) % 4 != 0 ? vetor[index] : 1);
		}
		
		return Vetor3D(
						temp[0], 
						temp[1], 
						temp[2]
					  );
	}

	
	///////////////////////////////////////////////////////////////////////
	/// M�todos de Atribui��o
	///////////////////////////////////////////////////////////////////////
	
	
	void operator=(
		const Matriz& outra_matriz
	){
		/*
		Assimilar� outra matriz � esta.
		*/
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			(*this).conteudo[i] = outra_matriz.conteudo[i];
		}
	}

	
	bool operator==(
		const Matriz& outra_matriz
	){
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			if(
				(*this).conteudo[ i ] != outra_matriz.conteudo[ i ]
			){
				return false;
			}
		}
		
		return true;		
	}


	void operator+=(
		const Matriz& outra_matriz
	){
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			(*this).conteudo[ i ] += outra_matriz.conteudo[ i ];
		}
	}
	
	
	void operator-=(
		const Matriz& outra_matriz
	){
		
		for(
			int i = 0;
			i < M_TAMANHO;
			i++
		){
			
			(*this).conteudo[ i ] -= outra_matriz.conteudo[ i ];
		}
	}

	
	float& operator[](
		const unsigned int index
	){
		/*
		Retornamos uma refer�ncia para permitir posterior altera��o do valor.
		Al�m disso, � mais eficiente, dado que n�o cria uma c�pia.
		*/
		return conteudo[index];
	}
	
	
	///////////////////////////////////////////////////////////////////////
	/// M�todos de Opera��es Espec�ficas
	///////////////////////////////////////////////////////////////////////
	
	
	Vetor3D obter_vetor_de_translacao() const {
		
		return Vetor3D(
						/*
						Garantia que � 4D.
						*/
						conteudo[ 3 ],
						conteudo[ 7 ],
						conteudo[ 11 ]
					  );
	}

	
	Matriz transposta() {
		// Devemos gerar uma nova matriz transposta.
		
		Matriz transp;
		
		for(
			int linha = 0;
			linha < M_LINHAS;
			linha++
		){
			
			for(
				int coluna = 0;
				coluna < M_COLUNAS;
				coluna++
			){
				
				transp.setar(
							coluna, 
							linha,
							(*this).obter(
										 linha,
										 coluna
									  )
							);
			}
		}
		
		return transp;
	}

	
	Matriz obter_matriz_de_transformacao_inversa() const {
		/*
		Suponha que eu tenha uma matriz que representa uma Transforma��o
		Linear, basta verificar novamente o estilo que estamos manipulando:
		https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html
		
		Eu desejo obter a matriz que representa a Transforma��o Inversa da mesma.
		Para quem olhou no site, desejamos a matriz inversa da apresentada
		com as entradas em a_ij.
		*/
		
		Matriz inv;  // Temos garantia que this � 4x4.
		
		// Transposta da SubMatriz 3x3
		int sub_index = 0;
		int index     = 0;
		while(
			index < 11
		){
			if(
				(index + 1) % 4 == 0
			){
				index++;
				sub_index++;
			}
			
			inv[
				4 * ( index % 4 ) + sub_index
			] = conteudo[
				index
			];
			
			index++;
		}
		
		// Transla��o de Valores
		index     = 0;
		while(
			index < 3
		){
			
			inv[
				4 * (index + 1) - 1
			] = (
				- conteudo[     index ] * conteudo[ 3  ]
			) + (
				- conteudo[ 4 + index ] * conteudo[ 7  ]
			) + (
				- conteudo[ 8 + index ] * conteudo[ 11 ]
			);
			
			index++;
		}
		
		return inv;
	}

	bool obter_inversa(
		Matriz& matriz_que_sera_inversa 
	) const {
		/*
		Obter� os coeficientes da inversa de uma matriz 4x4 qualquer.
		Al�m disso, verifica se o determinante desta matriz � 0:
		
		Retorna false caso o det seja 0, isto �, n�o existe inversa.
		Retorna true caso o det n�o seja 0 e teremos a matriz.
		
		N�o vou me atrever a alterar esse c�digo e buscar um algoritmo.
		(m.abreu@2020)
		*/
		
		float inv[16], det;
		// Apenas para garantirmos que n�o modificaremos o conte�do
	    const float* m = conteudo; 
	    
	    inv[ 0  ] =   m[5] * m[ 10 ] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	    inv[ 4  ] = - m[4] * m[ 10 ] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	    inv[ 8  ] =   m[4] * m[ 9  ] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9 ];
	    inv[ 12 ] = - m[4] * m[ 9  ] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9 ];
	    inv[ 1  ] = - m[1] * m[ 10 ] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	    inv[ 5  ] =   m[0] * m[ 10 ] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	    inv[ 9  ] = - m[0] * m[ 9  ] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9 ];
	    inv[ 13 ] =   m[0] * m[ 9  ] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9 ];
	    inv[ 2  ] =   m[1] * m[ 6  ] * m[15] - m[1] * m[7 ] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7 ] - m[13] * m[3] * m[6 ];
	    inv[ 6  ] = - m[0] * m[ 6  ] * m[15] + m[0] * m[7 ] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7 ] + m[12] * m[3] * m[6 ];
	    inv[ 10 ] =   m[0] * m[ 5  ] * m[15] - m[0] * m[7 ] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7 ] - m[12] * m[3] * m[5 ];
	    inv[ 14 ] = - m[0] * m[ 5  ] * m[14] + m[0] * m[6 ] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6 ] + m[12] * m[2] * m[5 ];
	    inv[ 3  ] = - m[1] * m[ 6  ] * m[11] + m[1] * m[7 ] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9 ] * m[2] * m[7 ] + m[9 ] * m[3] * m[6 ];
	    inv[ 7  ] =   m[0] * m[ 6  ] * m[11] - m[0] * m[7 ] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8 ] * m[2] * m[7 ] - m[8 ] * m[3] * m[6 ];
	    inv[ 11 ] = - m[0] * m[ 5  ] * m[11] + m[0] * m[7 ] * m[9 ] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9 ] - m[8 ] * m[1] * m[7 ] + m[8 ] * m[3] * m[5 ];
	    inv[ 15 ] =   m[0] * m[ 5  ] * m[10] - m[0] * m[6 ] * m[9 ] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9 ] + m[8 ] * m[1] * m[6 ] - m[8 ] * m[2] * m[5 ];
	
	    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	    
		if (det == 0){
	    	
	    	return false;
		}
	
	    det = 1.0 / det;
	
	    for( 
			int i = 0;
			i < 16;
			i++
		){
			
			matriz_que_sera_inversa.setar(i, inv[i] * det);
		}
	
	    return true;
	}
	
	
	/*
	Por que escrevemos tr�s matrizes e n�o apenas uma?
		A multiplica��o dessas matrizes 
		N�O S�O COMUTATIVAS!
		
		Por exemplo, fazer uma rota��o de X e em seguida em Y, n�o resultar�
		na mesma coisa que fazer primeiro em Y e dps em X.
	*/
	static Matriz matriz_de_rotacao_x(
		float angle
	){
		/*
		Providencia a matriz que representa a rota��o do eixo x
		neste �ngulo em degraus.
		*/
		const float temp[M_TAMANHO] = {
			1,              0,                0,      0,
        	0, cos_deg(angle), - sin_deg(angle),      0,
        	0, sin_deg(angle),   cos_deg(angle),      0,
        	0,              0,                0,      1
		};
		
		return Matriz(temp);
	}
	
	
	static Matriz matriz_de_rotacao_y(
		float angle
	){
		const float temp[M_TAMANHO] = {
        cos_deg(angle),     0,   sin_deg(angle),      0,
        			 0,     1,                0,      0,
      - sin_deg(angle),     0,   cos_deg(angle),      0,
                     0,     0,  	          0,      1
    	};
		
		return Matriz(temp);
	}


	static Matriz matriz_de_rotacao_z(
		float angle
	){
		const float temp[M_TAMANHO] = {
        cos_deg(angle), - sin_deg(angle),     0,      0,
        sin_deg(angle),   cos_deg(angle),     0,      0,
                     0,                0,     1,      0,
                     0,                0,     0,      1
    	};
		
		return Matriz(temp);
	}
	
	
	static Matriz matriz_de_rotacao_em_torno_de_eixo(
		Vetor3D eixo_representado_como_vetor_unitario,
		float angle
	){
		/*
		Obter matriz de rota��o em torno de um eixo espec�fico.
		Este vetor TEM QUE SER UNIT�RIO.
		*/
		
		float x = eixo_representado_como_vetor_unitario.x;
		float y = eixo_representado_como_vetor_unitario.y;
		float z = eixo_representado_como_vetor_unitario.z;
		
		const float temp[M_TAMANHO] = {
	(x * x * (1 - cos_deg(angle)) +     cos_deg(angle)), (x * y * (1 - cos_deg(angle)) - z * sin_deg(angle)), (x * z * (1 - cos_deg(angle)) + y * sin_deg(angle)), 0,
	(x * y * (1 - cos_deg(angle)) + z * sin_deg(angle)), (y * y * (1 - cos_deg(angle)) +     cos_deg(angle)), (y * z * (1 - cos_deg(angle)) - x * sin_deg(angle)), 0,
	(x * z * (1 - cos_deg(angle)) - y * sin_deg(angle)), (y * z * (1 - cos_deg(angle)) + x * sin_deg(angle)), (z * z * (1 - cos_deg(angle)) +     cos_deg(angle)), 0,
													  0,                                                   0,                                                   0, 1
	    };
	    
	    return Matriz(temp);
	}

}
#endif // Matriz_h
