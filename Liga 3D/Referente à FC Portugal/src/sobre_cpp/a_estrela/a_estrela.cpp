/*
Matheus Deyvisson, 2025

Deixo registrado mais uma vez o n�vel de profissionalismo do c�digo original
escrito por Miguel Abreu.
*/

#include <iostream>  // Apenas para realizarmos testes.

#include "a_estrela.h"
#include "obtendo_possibilidades.h"
#include <cmath>
#include <algorithm>
#include <chrono>

/*
Apenas para melhorarmos legibilidade.
*/
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

using std::min;
using std::max;

/*
Explica��o do que significa 'inline'
	Usada para sugerir ao compilador que uma fun��o deve ser expandida
	diretamente no local da chamada, em vez de realizar uma chamada de
	fun��o tradicional. De semelhante � fun��es lambda do Python.
	
	Mais precisamente, � parecido com o #define s� que para fun��o.
*/
inline int x_para_linha(
	float x
){
	/*
	Descri��o:
		Transformar de coordenada matem�tica x para coordenada de linha do campo.
	*/
	return int(
		// Linhas e Colunas s�o inteiras.
		fmaxf(
			/*
			Garantimos que a sa�da ser� 0 ou algo maior.
			*/
			0.f,
			fminf(
				/*
				Garantimos que estar� sob as 320 linhas totais.
				*/
				10 * x + 160,
				320.f
			)
		) + 0.5f
	);
}

inline int y_para_col(
	float y
){
	return int(
		// Linhas e Colunas s�o inteiras.
		fmaxf(
			/*
			Garantimos que a sa�da ser� 0 ou algo maior.
			*/
			0.f,
			fminf(
				/*
				Garantimos que estar� sob as 220 colunas totais.
				*/
				10 * y + 110,
				220.f
			)
		) + 0.5f
	);
}

inline float distancia_diagonal(
	bool ir_ao_gol,
	int linha,
	int coluna,
	int linha_final,
	int coluna_final
){
	/*
	Descri��o:
		Oq est� prestes � algo muito foda.
		Sugiro que verifique o seguinte site explicat�rio: http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
		
		Basicamente, estamos escolhendo velocidade � precis�o! Buscando
		um caminho que seja bom o suficiente, mas o mais r�pido poss�vel.	
	*/
	
	int delta_linha = 0;
	int delta_coluna = 0;
	
	if(
		ir_ao_gol
	){
		delta_linha = abs(
			LINHA_DO_GOL - linha
		);
		
		// OK, me rendi � forma que foi escrito no original.
		if(coluna > 119)       { delta_coluna = coluna - 119; }
		else if(coluna < 101)  { delta_coluna = 101 - coluna; }
		else                   { delta_coluna = 0;			  }
	}
	else{
		delta_linha  = abs( linha  - linha_final  );
		delta_coluna = abs( coluna - coluna_final );
	}
	
	/*
	Aqui est� o cerne da brincadeira. Sugiro que de verdade que verifique
	o site apresentado na descri��o. Alto N�vel demais.
	Esse n�mero � um valor espec�fico para o campo. Tome cuidado alterando-o.
	*/
	
	return (delta_linha + delta_coluna) - 0.585786437626905f * min(delta_linha, delta_coluna);
}

// Assim como definimos um Terra em circuitos, definiremos um n� n�o expandido
// que representar� o menor custo total previsto.
Node* min_node = nullptr;  

namespace noding{
	/*
	Descri��o:
		Define um espa�o de nomes (namespace), que serve para organizar e 
		agrupar funcionalidades (como classes, fun��es, vari�veis) em um escopo
		nomeado, evitando conflitos de nomes com outras partes do programa ou 
		bibliotecas externas.
		
		Acredito que foi feito assim pois Node n�o � exatamente um objeto,
		mas uma estrutura de dados e, portanto, struct. E, por legibilidade,
		n�o associamos classes<->structs, cada um no seu quadrado.
		
		Coloquei 'noding' porque queria relacionar com Node.
			
	Forma de Uso:
		open::imprimir();
		std::cout << open::valor;
	*/
	
	int
	apresentar_recursivamente(
		Node* raiz,
		/*
		const std::string&
			
			� uma refer�ncia constante a um objeto do tipo std::string. Us�-la
			garante efici�ncia para o caso de darmos strings grandes demais,
			pois o endere�o de mem�ria original ser� usado.
			
			O const serve apenas para indicar que n�o ser� modificado dentro
			da fun��o.
		*/
		const std::string& prefixo,
		bool se_eh_esquerdo
	){
		/*
			Apresentar� propriamente a BST.
		*/
		if(
			raiz == nullptr
		){
			return 0;
		}
		
		std::cout << prefixo;
		
		std::cout << (se_eh_esquerdo ? "|---" : "L---");  // Sim, eu sei, operador terci�rio, me perdoe.
		
		std::cout << (*raiz).valor << std::endl;
		
		apresentar_recursivamente(
			(*raiz).right,
			prefixo + (se_eh_esquerdo ? "|   " : "    "),
			true
		);
		apresentar_recursivamente(
			(*raiz).left,
			prefixo + (se_eh_esquerdo ? "|   " : "    "),
			false
		);
	}
	
	
	int apresentar(
		Node* raiz
	){
		/*
		Descri��o:
			Apenas preenche os par�metros corretamente, exigir isso do usu�rio
			� demais.
		*/
		return apresentar_recursivamente(
			raiz,
			"",
			false
		);
	}
	
		
	int liberar(
		Node* node
	){
		/*
		Descri��o:
			Libera a mem�ria usada pela estrutura.
		*/
		if(
			node == nullptr
		){
			return 0;
		}
		
		liberar(
			(*node).left
		);
		
		liberar(
			(*node).right
		);
		
		std::cout << "\nLiberando noh de valor: " << (*node).valor;
		
		delete node;
	}	
	
	
	Node*
	inserir(
		Node* novo_node,
		Node* raiz
	){
		/*
		Descri��o:
			Insere um n� de maneira correta dentro da estrutura
			
		Retorno:
			Raiz da estrutura.
		*/
		
		(*novo_node).left = nullptr;
		(*novo_node).right = nullptr;
		
		// Caso estrutura vazia
		if(
			raiz == nullptr
		){
			(*novo_node).up = nullptr;
			
			min_node = novo_node;  // Salvamos o n� minimo.
			
			return novo_node;
		}
		
		///////////////////////////////////////////////////////////////////
		
		// Caso o novo n� seja o menor que o m�nimo.
		if(
			(*novo_node).valor < (*min_node).valor 
		){
			/*
			O n� minimo passa a ter este novo n� como seu filho esquerdo.
			*/
			(*min_node).left = novo_node;
			
			/*
			O novo n� passa a ter o n� m�nimo como pai.
			*/
			(*novo_node).up = min_node;
			
			/*
			Atualiza o n� m�nimo para ser o novo n�.
			Retornando a raiz da �rvore pois a inser��o foi conclu�da.
			*/
			min_node = novo_node;  
			
			return raiz;
		}
		/*
		Mostremos um exemplo para caso a verifica��o anterior seja bem
		sucedida, isto �, o novo node tem um valor menor que o n� m�nimo.
		
		* Estrutura no In�cio:
		
			  [5]
		     /   \
	    	[2]   [10]
	   	   /   \
		[1]    [4]
       	^
		|(min_node)
		
		* Ordem de A��es:
		
		Filho esquerdo do m�nimo torna-se o novo n�.
		O pai do novo n� torna-se o m�nimo atual, [1].
		O novo n� torna-se o m�nimo.
		
		* Estrutura na Sa�da:
		
		   		[5]
		       /   \
		     [2]   [10]
		    /   \
		  [1]    [4]
		  /
		[0] <- Novo MIN
		*/
		
		///////////////////////////////////////////////////////////////////
		
		/*
		Definimos um ponto de partida para iterarmos sobre a estrutura.
		Desse jeito, estamos peganodo o mesmo endere�o de mem�ria.
		*/
		Node* node = raiz; 
		
		// Partimos do fato que � uma BST.
		while(
			1
		){
			if(
				// Se for menor, devemos coloc�-lo na esqueda.
				(*novo_node).valor < (*node).valor
			){
				
				if(
					/*
					Caso n�o exista filho esquerdo, devemos tornar o novo n�
					este filho esquerdo. Enfim, teremos acabado.
					*/
					(*node).left == nullptr
				){
					
					(*node).left = novo_node;
					
					break;
				}
				else{
					/*
					Caso exista um filho esquerdo, vamos iterar sobre ele
					para novas verifica��es.
					*/
					
					node = (*node).left;
				}
				
			}
			else{
				// Caso seja maior ou igual, devemos coloc�-lo na direita.
				
				// Basta ler o primeiro caso para maiores explica��es.
				if(
					(*node).right == nullptr
				){
					
					(*node).right = novo_node;
					
					break;
				}
				else{
					
					node = (*node).right;
				}
			}
		}
		
		// Por fim, atualizamos o Pai do novo n�.
		(*novo_node).up = node;
		
		return raiz;
	}
	
	
	Node*
	remover_min(
		Node* raiz
	){
		/*
		Descri��o:
			Desejamos remover o menor elemento, que apesar de que deveria ser
			o �ltimo elemento, n�o necessariamente ser�.
			
			Note que o m�nimo pode ter um filho, mas este necessariamente
			ser� direito.
			
		Retorno:
			Raiz da estrutura.
		*/
		
		if(
			// Caso n�o tenha filho.
			(*min_node).right == nullptr
		){
			
			if(
				// Caso n�o tenha pai.
				min_node == raiz
			){
				// Ent�o, ap�s remov�-lo n�o haver� nada dentro.
				delete min_node;
				
				return nullptr;
			}
			
			/*
			Caso ele tenha um pai.
			
			Tornar o elemento esquerdo do pai nulo.
			
			E atualizar o novo m�nimo.
			*/
			
			(*((*min_node).up)).left = nullptr;
			
			Node* temp_para_eliminacao = min_node;
			
			min_node = (*temp_para_eliminacao).up;
			
			delete temp_para_eliminacao;
		}
		else{
			// H� filho direito
			
			if(
				// Caso seja a raiz.
				min_node == raiz
			){
				/*
				Essa situa��o � bem mais rara, pois teremos:
				
				  [5](min_node)
			        \
		   			[10]
				
				Note que ele possui filho direito e � a raiz.
				*/
				
				Node* temp_para_eliminacao = min_node;
				
				min_node = (*min_node).right;
				
				delete temp_para_eliminacao;
				
				raiz = min_node;
				
				(*raiz).up = nullptr;
				/*
				No exemplo que eu dei anteriormente, movemos o n� m�nimo 
				para que seja o 10 e a raiz tamb�m, eliminamos o up.
				*/
				
				while(
					/*
					J� estamos com um determinado n�.
					Enquanto houver um filho esquerdo, haver� necessariamente
					um n� menor, portanto, devemos torn�-lo m�nimo.
					*/
					(*min_node).left != nullptr
				){

					min_node = (*min_node).left;
				}
				
				return raiz;				
			}
			
			/*
			Considere este exemplo para este caso.
			
			     [7]
			  	/
			  [5](min_node)
	            \
   			   [10]
   			   
			*/
			
			/*
			Evidenciamos que o pai do filho direito deve ser o pai do m�nimo.
			*/
			(*((*min_node).right)).up = (*min_node).up;
			
			/*
			O filho esquerdo do pai do m�nimo dever� ser o filho direito do m�nimo.
			*/
			(*((*min_node).up)).left = (*min_node).right;
			
			// Atualizamos o novo m�nimo
			
			Node* temp_para_eliminacao = min_node;
			
			min_node = (*min_node).right;
			
			delete min_node;
			
			while(
				/*
				Enquanto houver um elemento � esquerda, haver� um m�nimo.
				*/
				(*min_node).left != nullptr
			){
				
				min_node = (*min_node).left;
			}
			
			return raiz;
		}	
		
		return raiz;
	}
	
	
	Node*
	remover_node(
		Node* node_a_ser_removido,
		Node* raiz
	){
		/*
		Descri��o:
			Separa em casos de exist�ncia de filhos e remove n�s desejados.
			
		Retorno:
			Raiz da estrutura.
		*/
		
		if(
			node_a_ser_removido == min_node
		){
			return remover_min(
				raiz
			); // remover� o m�nimo da estrutura.
		}
		
		if(
			// Caso o n� a ser removido n�o tenha filhos, logo tamb�m n�o � raiz.
			(*node_a_ser_removido).left == nullptr && (*node_a_ser_removido).right == nullptr
		){
			/*
			A partir do n� a ser removido, devemos retirar a conex�o de descida do pai
			para ele.
			*/
			if(
				(*((*node_a_ser_removido).up)).left == node_a_ser_removido
			){
				(*((*node_a_ser_removido).up)).left = nullptr;
			}
			else{
				(*((*node_a_ser_removido).up)).right = nullptr;
			}
			
			delete node_a_ser_removido;
			
			return raiz;
		}
		
		if(
			// Caso tenha somente filho direito.
			(*node_a_ser_removido).left == nullptr
		){
			// Redirecionamos conex�es de subida do filho direito do n� a ser 
			// removido para o pai do n� a ser removido.
			(*((*node_a_ser_removido).right)).up = (*node_a_ser_removido).up;
			
			if(
				(*((*node_a_ser_removido).up)).left == node_a_ser_removido		
			){
				/*
				J� que estamos removendo um n� que tem filho direito, fazemos com que 
				este seja o novo filho do pai do n� a ser removido, conservando o lado
				deste.
				*/
				(*((*node_a_ser_removido).up)).left = (*node_a_ser_removido).right;
			}
			else{
				(*((*node_a_ser_removido).up)).right = (*node_a_ser_removido).right;
			}
			
			delete node_a_ser_removido;
			
			return raiz;
			
		}
		
		if(
			// Caso somente tenha filho esquerdo
			(*node_a_ser_removido).right == nullptr
		){
			
			if(
				/*
				Al�m de ter somente filho esquerdo, ele � a raiz. Logo,
				devemos desfazer a conex�o de subida do filho esquerdo e 
				torn�-lo a nova raiz.
				*/
				node_a_ser_removido == raiz
			){
				
				(*((*node_a_ser_removido).left)).up = nullptr;
				
				Node* nova_raiz = (*node_a_ser_removido).left;
				
				delete node_a_ser_removido;
				
				return nova_raiz; 
			}
			
			// Como n�o � a raiz.
			(*((*node_a_ser_removido).left)).up = (*node_a_ser_removido).up;
			
			if(
				(*((*node_a_ser_removido).up)).left == node_a_ser_removido
			){
				(*((*node_a_ser_removido).up)).left = (*node_a_ser_removido).left;
			}
			else{
				(*((*node_a_ser_removido).up)).right = (*node_a_ser_removido).left;
			}
			
			delete node_a_ser_removido;
			
			return raiz;
		}
		
		/*
		Logo, tem filhos e n�o � o m�nimo.
		Vejamos o exemplo:
		
			   [5]
		      /   \
 (Remov�-lo)[2]   [10]
	   	   /   \
		[1]    [4]
		...		...
		
		*/
		
		/*
		Como � BST, temos a garantia que o filho direito � maior que o 
		filho esquerdo. 
		
		Caso o filho esquerdo do n� a ser removido substitua-o, este
		ser� pai do filho direito do n� a ser removido, o que contradiz a BST.
		
		Portanto, o filho direito do n� a ser removido, [4], torna-se o
		sucessor.
		*/
		Node* sucessor = (*node_a_ser_removido).right;
		
		if(
			// Sucessor n�o tem filho esquerdo.
			(*sucessor).left == nullptr
		){
			// Caso o sucessor n�o tenha filho esquerdo.
			
			/*
			Filho esquerdo do n� a ser removido torna-se o filho esquerdo
			do sucessor.
			*/
			(*sucessor).left = (*node_a_ser_removido).left; 
			
			/*
			Pai do sucessor torna-se o pai do n� a ser removido.
			*/
			(*sucessor).up = (*node_a_ser_removido).up;
			
			/*
			Pai do filho esquerdo torna-se o sucessor.
			*/
			(*((*node_a_ser_removido).left)).up = sucessor;
			
			if(
				// Se for a raiz
				node_a_ser_removido == raiz
			){
				delete node_a_ser_removido;
				
				return sucessor; // Este tornou-se a nova raiz
			}
			
			// Se n�o for a raiz, alteramos o filho do pai do n� a ser removido.
			if(
				(*((*node_a_ser_removido).up)).left == node_a_ser_removido
			){
				
				(*((*node_a_ser_removido).up)).left = sucessor;
			}
			else{
				
				(*((*node_a_ser_removido).up)).right = sucessor;
			}
		}
		else{
			// Sucessor tem filho esquerdo.
			
			while(
				/*
				Enquanto o sucessor tiver filho esquerdo, vamos
				tornar este o novo sucessor.
				*/
				(*sucessor).left != nullptr
			){
				sucessor = (*sucessor).left;
			}
			
			if(
				/*
				Pelo loop anterior, n�o h� filho esquerdo.
				Verificamos se n�o h� filho direito.
				*/
				(*sucessor).right == nullptr
			){
				// N�o h� filhos direito e esquerdo no sucessor.
				
				/*
				O pai desse sucessor n�o ter� mais filho esquerdo. Por isso, nullptr.
				Eliminamos a conex�o de descida.
				*/
				(*((*sucessor).up)).left = nullptr;
			}
			else{
				/*
				O filho esquerdo do pai do sucessor, deve se tornar o �nico filho do sucessor.
				*/
				(*((*sucessor).up)).left = (*sucessor).right;
				
				/*
				Apenas a conex�o de subida referente � conex�o de descida definida anteriormente.
				*/
				(*((*sucessor).right)).up = (*sucessor).up;
			}
			
			/*
			Alteramos todas as conex�es do sucessor para substituir exatamente
			o n� que desejamos remover.
			*/
			(*sucessor).left = (*node_a_ser_removido).left;
			(*sucessor).right = (*node_a_ser_removido).right;
			(*sucessor).up = (*node_a_ser_removido).up;
			
			/*
			Atualizamos as conex�es de subida dos filhos esquerdo e direito para
			o substituto do n� a ser removido, vulgo sucessor.
			*/
			(*((*node_a_ser_removido).left)).up = sucessor;
			(*((*node_a_ser_removido).right)).up = sucessor;
			
			if(
				node_a_ser_removido == raiz
			){
				
				delete node_a_ser_removido;
				return sucessor;
			}
			
			if(
				/*
				Apenas atualizamos a conex�o de descida do pai do node a ser removido.
				*/
				(*((*node_a_ser_removido).up)).left == node_a_ser_removido
			){
				
				(*((*node_a_ser_removido).up)).left = sucessor;
			}
			else{
				
				(*((*node_a_ser_removido).up)).right = sucessor;
			}
			
			return raiz;
		}
		/*
		Um exemplo completo do algoritmo referente ao �ltimo 
		
		Quest�o:
		
			L---5
			    |---10
			    L---2
			        |---4
			        |   |---5
			        |   L---3
			        L---1
			
			Desejamos remover o n� de valor 2.
			
		Solu��o:
			
			Sucessor torna-se n� 4.
			
			Este possui filho esquerdo, logo enquanto houver um filho esquerdo,
			teremos garantia que este ser� menor que seu pai( Defini��o BST).
			Iteramos atualizando o sucessor para cada filho esquerdo.
			Note que mesmo que haja filhos direitos, temos a garantia de que
			estes ser�o maiores que os respectivos filhos esquerdos(Defini��o BST).
			N� 3 torna-se o sucessor.
			
			
			Neste caso, n�o h� filho direito no sucessor. Como o sucessor vai sair, 
			o pai dele ficar� sem filhos.
			Caso tivesse filho direito no sucessor, ele se tornaria o novo filho do 
			pai do ent�o sucessor.
			
			Atualizamos as conex�es que partem do sucessor para que ele substitua
			o n� que ser� removido.
			Em seguida, atualizamos as atualiza��es dos filhos do n� que ser� removido
			para apontarem para o substituto, vulgo sucessor.
			Finalmente, atualizamos a conex�o de descida do pai do n� que ser� removido
			para apontar para o sucessor.
		*/
		return raiz;
	}
	
	Node*
	expandir_filho(
		Node* raiz_da_estrutura,  
		float custo_para_chegar_ao_no_desejado,
		float limite_para_qual_custo_eh_impossivel,
		Node* node_atual_a_ser_expandido,
		/*
		Representa��o da grid do campo
		*/
		Node* quadro_de_possibilidades,
		int posicao_do_node_no_quadro,
		/*
		0 - Explorado
		1 - Lista Aberta
		*/
		int estado_atual_do_node, 
		bool ir_ao_gol,
		// Coordenadas do n�
		int linha, int coluna,
		// Coordenadas do n� final
		int linha_final, int coluna_final,
		// Array que armazenar� estados dos n�s
		unsigned int* estado_dos_nodes,
		// Custo Adicional para o movimento
		float extra
	){
		/*
		Descri��o:
			Parte do algoritmo para busca de melhor caminho poss�vel, 
			expandindo e avaliando filhos durante busca.
			
			Fiz o poss�vel para tentar decifrar o que acontece aqui.
		*/
		
		if(
			/*
			Filho pode ser inacess�vel a partir do n� atual, para isso haver� um 
			custo de penalidade para desencorajar caminhos imposs�veis.
			*/
			custo_para_chegar_ao_no_desejado <= limite_para_qual_custo_eh_impossivel
		){
			
			custo_para_chegar_ao_no_desejado = 100.f;
		}
		
		float min_custo = (*node_atual_a_ser_expandido).custo_pontual + extra + std::fmaxf(
			0.f,
			custo_para_chegar_ao_no_desejado
		);  // Max para garantimos que seja positivo.
		
		Node* filho = quadro_de_possibilidades + posicao_do_node_no_quadro;
		
		if(
			// Caso o n� atual j� esteja na lista aberta.
			estado_atual_do_node
		){
			if(
				/*
				E o novo custo calculo n�o for melhor que o do n� atual,
				o descartamos.
				*/
				min_custo >= (*node_atual_a_ser_expandido).custo_pontual
			){
				
				return raiz_da_estrutura;
			}
			else{
				/*
				Houve uma melhora, devemos remover a refer�ncia do n� filho,
				atualiz�-lo e adicion�-lo na estrutura posteriormente.
				*/
				raiz_da_estrutura = noding::remover_node(
					filho,
					raiz_da_estrutura
				);
			}
		}
		else{
			// Colocamos ele na lista.
			estado_dos_nodes[
				posicao_do_node_no_quadro
			] = 1;
		}
		
		/*
		Preenchemos caracter�sticas do n� filho que est� sendo analisado.
		*/
		float predicao_de_custo_para_atravessar_filho = min_custo + distancia_diagonal(
			ir_ao_gol,
			linha,
			coluna,
			linha_final,
			coluna_final
		);
		
		(*filho).custo_pontual = min_custo;
		(*filho).valor = predicao_de_custo_para_atravessar_filho;
		(*filho).parente = node_atual_a_ser_expandido;
		
		// Finalmente, o inserimos.
		return noding::inserir(
			filho,
			raiz_da_estrutura
		);
	}

}

float caminho_final[2050] = {0};
int tamanho_do_caminho_final = 0;

inline void
construir_caminho_final(
	/*
	Observe essa diferen�a sutil, simplesmente genial Miguel Abreu.
	
	Node* const
		Ponteiro para Node constante.
		Objeto Node n�o pode ser modificado atrav�s do ponteiro.
		Mas o ponteiro pode apontar para outro Node.
	
	Node* const
		Ponteiro constante para Node
		Ponteiro em si � constante, n�o pode apontar para outro Node.
		Mas o objeto Node pode ser modificado.
	*/
	Node* const melhor_node,
	const Node* quadro_de_possibilidades,
	
	float status,
	/*
	Ativa ou desativa a substitui��o das coordenadas finais discretas
	por valores exatos.
	
	False - Coordenadas Discretas do Grid
	True  - Substitui o �ltimo ponto do caminho por valores exatos em end_x e em end_y.
	*/
	const bool override_end=false,
	/*
	Especificam as coordenadas exatas do ponto final quando override est� ativo.
	*/
	const float end_x=0, const float end_y=0
){
	/*
	Descri��o:
		Fun��o respons�vel por construir o melhor a partir da estrutura de 
		n�s fornecida.
	*/
	
	Node* ptr = melhor_node;
	
	int quantidade_de_parentes = 0;
	while(
		ptr != nullptr
	){
		
		ptr = (*ptr).parente;
		quantidade_de_parentes++;
	}
	
	tamanho_do_caminho_final = min(
		/*
		Limitamos o caminho final � quantidade de slots dispon�veis.
		*/
		2 * quantidade_de_parentes,
		2048
	);
	
	/*
	Voltamos ao melhor n�. 
	Note que foi por isso que escrevemos o const, para preservar essa
	propriedade. 
	Completamente insano.
	*/
	ptr = melhor_node; 
	int indice = tamanho_do_caminho_final - 1;
	
	if(
		// Se ativado, atualiza o ponto final para coordenadas corretas
		// ao inv�s de vers�o discreta.
		override_end
	){
		/*
		indice   - acessamos no indice.
		indice-- - acessamos no indice e o decrementamos
		*/
		caminho_final[indice--] = end_y;
		caminho_final[indice--] = end_x;
		
		ptr = (*ptr).parente;
	}
	
	while(
		indice > 0
	){
		// N�o � um delta embaixo parece.
		caminho_final[indice--] = (
			(ptr - quadro_de_possibilidades) % QUANT_COLUNAS
		) / 10.f - 11.f;  // y
		
		caminho_final[indice--] = (
			(ptr - quadro_de_possibilidades) / QUANT_COLUNAS
		) / 10.f - 16.f;  // x
		
		ptr = (*ptr).parente;
	}
	
	/*
	Atualizamos o status do caminho e acrescentamos a unidade do tamanho
	
	0 - sucesso
	1 - tempo excedido
	2 - imposs�vel
	*/
	caminho_final[
		tamanho_do_caminho_final++
	] = status;  
		
	/*
	Informa��es sobre o custo completo do caminho.
	*/
	caminho_final[
		tamanho_do_caminho_final++
	] = (*melhor_node).custo_pontual / 10.f; 
}	


int main()
{
 	// Exemplo de BST para testarmos c�digo de noding.
 	// Fiz usando // para poder usar o atalho.
	{
//		Node *node = new Node(5);			
//		Node *node_l = new Node(2);
//		(*node_l).up = node;
//		(*node).left = node_l;
//		
//		Node *node_r = new Node(10);
//		(*node_r).up = node;
//		(*node).right = node_r;
//		
//		Node *node_ll = new Node(1);
//		(*node_ll).up = node_l;
//		(*node_l).left = node_ll;
//		
//		Node *node_lr = new Node(4);
//		(*node_lr).up = node_l;
//		(*node_l).right = node_lr;
//		
//		Node* node_lrl = new Node(3);
//		(*node_lrl).up = node_lr;
//		(*node_lr).left = node_lrl;
//		
//		Node* node_lrr = new Node(5);
//		(*node_lrr).up = node_lr;
//		(*node_lr).right = node_lrr;
//		
//		
//		noding::apresentar(
//			node
//		);
//		
//		noding::liberar(
//			node
//		);

	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
    return 0;
}
