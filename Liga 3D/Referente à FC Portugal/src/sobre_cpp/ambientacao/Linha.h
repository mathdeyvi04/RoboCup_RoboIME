#ifndef LINHA_H
#define LINHA_H

#include "Geometria.h"
#include <stdio.h>

class Linha{
	/*
	Descri��o:
		Classe respons�vel por represetar um segmento de linha a partir de 
		2 vetores tridimensionais.
		
	Cr�ditos: Miguel Abreu (m.abreu@fe.up.pt)
	*/
	
public:
	
	// Para coordenadas esf�ricas.
	/*
	Para coordenadas esf�ricas. Basta ver em Geometria.h e no original
	Vector3f.cpp que ele se refere a vetores com raio, phi e theta. Mas em
	polares � para 2D, para 3D nos referimos a esfericas.
	*/
	const Vetor3D inicio_e;
	const Vetor3D final_e;
	
	// Para coordenadas cartesianas.
	const Vetor3D inicio_c;
	const Vetor3D final_c;

	const float comprimento;
	
	//////////////////////////////////////////////////////////////////////
	/// Construturos e Destrutores
	//////////////////////////////////////////////////////////////////////
	
	Linha(
		const Vetor3D& inicio_esf,
		const Vetor3D& final_esf
	) : inicio_e(inicio_esf ),
		 final_e(final_esf  ),
		inicio_c(inicio_esf.para_cartesiano()),
		 final_c(final_esf.para_cartesiano ()),
     comprimento(inicio_c.obter_distancia(final_c))
	{}
	
	Linha(
		const Vetor3D& inicio_cart,
		const Vetor3D& final_cart,
		float comprimento
	) : inicio_e(inicio_cart.para_esferica()),
		 final_e(final_cart.para_esferica()),
		inicio_c(inicio_cart),
		 final_c(final_cart),
	 comprimento(comprimento)
	{}
	
	Linha(
		const Linha& a_ser_copiado
	) : inicio_e(a_ser_copiado.inicio_e),
		 final_e(a_ser_copiado.final_e),
		inicio_c(a_ser_copiado.inicio_c),
		 final_c(a_ser_copiado.final_c),
	 comprimento(a_ser_copiado.comprimento)
	{}
	
	//////////////////////////////////////////////////////////////////////
	/// M�todos de C�lculo Espec�fico
	//////////////////////////////////////////////////////////////////////
	
	/*
	Aten��o, existem fun��es que recebem par�metros em esf�ricas e 
	retornam pontos em cartesianas.
	*/
	
	Vetor3D ponto_na_reta_mais_perto_cart(
		const Vetor3D& ponto_qualquer_cart
	){
		/*
		A partir de um ponto qualquer, achar� o ponto na RETA INFINITA
		definida pela linha, this.
		
		�lgebra Linear pura:
			
			Q -> Ponto Qualquer
			P = A + t(B - A) -> Linha
			
			Por defini��o, o mais perto � perpendicular:
			
			< Q - P , P - A > = 0
			< Q - A - t(B - A) , t(B - A) > = 0
			t< Q - A, B - A > - t^2 < B - A, B - A > = 0
			
			t = < Q - A, B - A > / < B - A, B - A >
			
			Por fim, basta substituir na linha.
		*/

		float param = (ponto_qualquer_cart - inicio_c).InnerProduct(final_c - inicio_c) / (comprimento * comprimento);	
		
		return inicio_c + (final_c - inicio_c) * param;
	}
	Vetor3D ponto_na_reta_mais_perto_esf(
		Vetor3D& ponto_qualquer_esf
	){
		
		// Note que estamos recebendo em esf e retornaremos em cartesiana!!!
		
		return ponto_na_reta_mais_perto_cart(ponto_qualquer_esf.para_cartesiano());
	}
	
	
	float distancia_ate_ponto_cart(
		const Vetor3D& ponto_qualquer_cart
	){
		/*
		Dist�ncia de um ponto a uma linha. 
		
		Suponha B - A o segmento de linha pertencente � linha e 
		Q o ponto qualquer.
		
		Note que:
		
		2 * Area = |(Q - inicio_c) X (Q - final_c)| = Base Altura
		
		Altura = |(Q - inicio_c) X (Q - final_c)| / |final_c - inicio_c|
		*/
		
		return ((ponto_qualquer_cart - inicio_c).CrossProduct(ponto_qualquer_cart - final_c)).modulo() / comprimento;
	}
	float distancia_ate_ponto_esf(
		const Vetor3D ponto_qualquer_esf
	){
		return distancia_ate_ponto_cart(ponto_qualquer_esf.para_cartesiano());
	}
	
	
	float distancia_ate_linha(
		const Linha& linha
	)  {
		/*
		Suponha duas retas definidas pelas linhas, (*this) e a dada.
		De tal forma que:
		
		P = A + t(B - A)       		Q = N + r(M - N)
		
		S�o pontos quaisquer respectivamente nas mesmas. Se desejamos a
		dist�ncia entre essas linhas, devemos buscar P - Q de tal forma
		que essa linha seja perpendendicar � B - A e � M - N simutalneamente.
		
		< P - Q, B - A > = 0
		< P - Q, M - N > = 0
		
		Em seguida, manipular algebricamente:
		
		t< B - A, B - A > - r< M - N, B - A > = < N - A, B - A >
		t< B - A, M - N > - r< M - N, M - N > = < N - A, M - N >
		
		Observe que temos um sistema linear. H� tr�s op��es.
		
		i) N�o h� solu��o.
			
			Como estamos dimens�es no m�ximo tridimensionais, sempre haver�
			pelo menos uma solu��o.
		
		ii) Infinitas solu��es.
			
			Caso em que as retas est�o paralelas. H� infinitos pontos que
			satisfazem a perpendicularidade.
			
			Basta que o determinante da matriz dos coeficientes seja zero.
			
			Ent�o basta escolher um ponto da linha dada como fixo, N por exemplo,
			e obtermos a dist�ncia � esse ponto. Neste caso, a solu��o � trivial.
		
		iii) Uma �nica solu��o.
		
			Para facilitar, podemos denotar os coeficientes como par�metros e
			assim resolver o sistema 2x2.
		*/

		float prod_esc_entre_vet_diretores = (linha.final_c - linha.inicio_c).InnerProduct((*this).final_c - (*this).inicio_c);
		
		float Det = prod_esc_entre_vet_diretores * prod_esc_entre_vet_diretores - (*this).comprimento * (*this).comprimento * linha.comprimento * linha.comprimento; 
		
		if(
			// Caso sejam paralelas ou pelo menos quase paralelas.
			fabs(Det) < 1e-5
		){

			return (*this).distancia_ate_ponto_cart(linha.inicio_c);
		}
		
		/*
		Produto escalar entre posi��o relativa do segmento, N - A, e
		vetor diretor da nossa linha, B - A.
		*/
		float g_this = (linha.inicio_c - (*this).inicio_c).InnerProduct((*this).final_c - (*this).inicio_c);
		/*
		Produto escalar entre posi��o relativa do segmento, N - A, e
		vetor diretor da linha dada, M - N.
		*/
		float g_other = (linha.inicio_c - (*this).inicio_c).InnerProduct(linha.final_c - linha.inicio_c);
	
		// Respectivos Par�metros:
		float param_t = (
			g_other * prod_esc_entre_vet_diretores - g_this * linha.comprimento * linha.comprimento
		) / Det;
		
		float param_r = (fabs(prod_esc_entre_vet_diretores) < 1e-5) ? - g_other / (linha.comprimento * linha.comprimento) : (
			param_t * (*this).comprimento * (*this).comprimento - g_this
		) / prod_esc_entre_vet_diretores;
		
		// Respectivos pontos de dist�ncia m�nima.
		Vetor3D P = inicio_c + (final_c - inicio_c) * param_t;
		Vetor3D Q = linha.inicio_c + (linha.final_c - linha.inicio_c) * param_r;
		
		return P.obter_distancia(Q);
	}	
	
	
	//////////////////////////////////////////////////////////////////
	
	
	Vetor3D segment_ponto_na_reta_mais_perto_cart(
		const Vetor3D& ponto_qualquer_cart
	){
		/*
		Basicamente, mesma fun��o que a anterior, entretanto, agora limitamos
		os pontos poss�veis para o segmento de reta definido por inicio_c e 
		final_c.
		*/
		
		float param = (ponto_qualquer_cart - inicio_c).InnerProduct(final_c - inicio_c) / (comprimento * comprimento);	
		
		// Ambas condi��es nunca ser�o verdadeiras ao mesmo tempo.
		param += (param < 0) * ( - param ) + (param > 1) * (1 - param); // Simplesmente goat
		
		return inicio_c + (final_c - inicio_c) * param;
	}
	Vetor3D segment_ponto_na_reta_mais_perto_esf(
		const Vetor3D& ponto_qualquer_esf
	){
		
		return segment_ponto_na_reta_mais_perto_cart(ponto_qualquer_esf.para_cartesiano());
	}
	
	
	float segment_distancia_ate_ponto_cart(
		const Vetor3D& ponto_qualquer_cart
	){
		/*
		Mesma fun��o que a nome semelhante, entretanto, n�o pensaremos mais
		na reta infinita, e sim no segmento de reta.
		
		Imagine um ponto qualquer Q e um SEGMENTO DE RETA definido por B - A.
		
				  .B
		Q.       /
		       /
			A.
		
		Caso Q esteja para "tr�s" de A, a dist�ncia |Q - A| representa a dist�ncia
		m�nima de Q ao segmento.
		
		Caso Q esteja para "frente" de B, a dist�ncia |Q - B| representa a dist�ncia
		m�nima de Q ao segmento.
		
		Caso Q esteja na regi�o entre A e B, teremos o tri�ngulo.
		*/
		
		if(	
			(ponto_qualquer_cart - (*this).inicio_c).InnerProduct((*this).final_c - (*this).inicio_c) <= 0
		){
			
			return (*this).inicio_c.obter_distancia(ponto_qualquer_cart);
		}
		
		if(
			(ponto_qualquer_cart - (*this).final_c).InnerProduct((*this).final_c - (*this).inicio_c) >= 0
		){
			
			return (*this).final_c.obter_distancia(ponto_qualquer_cart);
		}
		
		return ((ponto_qualquer_cart - inicio_c).CrossProduct(ponto_qualquer_cart - final_c)).modulo() / comprimento;
	}
	float segment_distancia_ate_ponto_esf(
		const Vetor3D& ponto_qualquer_esf
	){
		return segment_distancia_ate_ponto_cart(ponto_qualquer_esf.para_cartesiano());
	}
		
	
	float segment_distancia_ate_segment(
		const Linha& linha
	){
		/*
		Obter dist�ncia entre dois segmentos de reta definidos respectivamente
		por B - A e M - N.
		
		Analisando o algoritmo da fun��o imediatamente anterior e a ideia do
		que esta fun��o se prop�e, podemos reutilizar o algoritmo das retas 
		infinitas e verificar os valores dos par�metros.
		
		Caso N�o Sejam Parelalos:
		
		Trivialmente reutilizaremos o algoritmo da fun��o semelhante
		e analisaremos se os par�metros s�o menores que 0 ou maiores
		que 1.
		
		Caso sejam paralelos:
		
		M.
		
		
		
		N.
		
				.B
				
				.A
		
		Observe que se dependendo se M - N est� "� frente" ou "� tr�s"
		temos configura��es diferentes de dist�ncias.
		
		Caso B n�o esteja esteja para tr�s de N e A n�o esteja para 
		frente de M, teremos:
		
		M.
			.B
		
			.A
		N.
		
		Neste caso, teremos um trap�zio.
		
		*/
		
		float prod_esc_entre_vet_diretores = (linha.final_c - linha.inicio_c).InnerProduct((*this).final_c - (*this).inicio_c);
		
		float Det = prod_esc_entre_vet_diretores * prod_esc_entre_vet_diretores - (*this).comprimento * (*this).comprimento * linha.comprimento * linha.comprimento; 
		
		if(
			// Caso sejam paralelas ou pelo menos quase paralelas.
			fabs(Det) < 1e-3
		){
			
			if(
				/*
				Se B estiver para tr�s de N, a dist�ncia ser� |B - N|.
				*/
				((*this).final_c - linha.inicio_c).InnerProduct(linha.final_c - linha.inicio_c) <= 0
			){
				
				return (*this).final_c.obter_distancia(linha.inicio_c);
			}
			
			if(
				/*
				Se A estiver para frente de M, a dist�ncia ser� |A - M|.
				*/
				((*this).inicio_c - linha.final_c).InnerProduct(linha.final_c - linha.inicio_c) >= 1
			){
				
				return (*this).inicio_c.obter_distancia(linha.final_c);
			}
			
			/*
			Obter altura a partir da �rea do trap�zio formado pelas linhas.
			*/
			
			float semi_triang_1 = (linha.inicio_c - (*this).inicio_c).CrossProduct((*this).final_c - (*this).inicio_c).modulo();
			float semi_triang_2 = (linha.inicio_c -    linha.final_c).CrossProduct((*this).final_c -   linha.inicio_c).modulo();
			
			return (semi_triang_1 + semi_triang_2) / (linha.comprimento + (*this).comprimento);
		}
		
		/*
		Produto escalar entre posi��o relativa do segmento, N - A, e
		vetor diretor da nossa linha, B - A.
		*/
		float g_this = (linha.inicio_c - (*this).inicio_c).InnerProduct((*this).final_c - (*this).inicio_c);
		/*
		Produto escalar entre posi��o relativa do segmento, N - A, e
		vetor diretor da linha dada, M - N.
		*/
		float g_other = (linha.inicio_c - (*this).inicio_c).InnerProduct(linha.final_c - linha.inicio_c);
	
		// Respectivos Par�metros:
		float param_t = (
			g_other * prod_esc_entre_vet_diretores - g_this * linha.comprimento * linha.comprimento
		) / Det;
		
		float param_r = (fabs(prod_esc_entre_vet_diretores) < 1e-5) ? - g_other / (linha.comprimento * linha.comprimento) : (
			param_t * (*this).comprimento * (*this).comprimento - g_this
		) / prod_esc_entre_vet_diretores;
		
		// Corre��o para Segmentos de Reta.
		param_t += (param_t < 0) * (- param_t) + (param_t > 1) * (1 - param_t);
		
		param_r += (param_r < 0) * (- param_r) + (param_r > 1) * (1 - param_r);
		
		// Respectivos pontos de dist�ncia m�nima.
		Vetor3D P = inicio_c + (final_c - inicio_c) * param_t;
		Vetor3D Q = linha.inicio_c + (linha.final_c - linha.inicio_c) * param_r;
		
		return P.obter_distancia(Q);
	}
	
	//////////////////////////////////////////////////////////////////////
	/// Operador de Acesso
	//////////////////////////////////////////////////////////////////////
	
	
	Vetor3D obter_ponto_medio_cart() const {
		return (inicio_c + final_c) / 2;
	}
	Vetor3D obter_ponto_medio_esf() const {
		return (*this).obter_ponto_medio_cart().para_esferica();
	}
	
	const Vetor3D& obter_ponto_cart(const int index) const {
		/*
		O const no inicio e no final garantem que:
		
		O objeto Linha n�o seja modificado e os membros retornados
		n�o sejam modificados.
		*/
		
		if(
			index == 0
		){
			
			return inicio_c;
		}
		
		return final_c;
	}
	
	const Vetor3D& obter_ponto_esf(const int index) const {
		if(
			index == 0
		){
			
			return inicio_e;
		}
		
		return final_e;
	}
	
	Vetor3D obter_diretor_cart() const {
		return final_c - inicio_c;
	}
	
	Vetor3D obter_diretor_esf() const {
		return final_e - inicio_e;
	}
	
	//////////////////////////////////////////////////////////////////////
	/// Operador de Condi��es
	//////////////////////////////////////////////////////////////////////
	
	bool operator==(const Linha& outra_linha) const {
		/*
		O sistema nos fornecer� em esf�ricas. Acredito que seja melhor assim
		para evitarmos erros de conta devido � opera��es, oq poderia tornar 
		valores um pouco diferentes.
		*/
		return (inicio_e == outra_linha.inicio_e) && (final_e == outra_linha.final_e);
	}
	
};

#endif // LINHA_H
