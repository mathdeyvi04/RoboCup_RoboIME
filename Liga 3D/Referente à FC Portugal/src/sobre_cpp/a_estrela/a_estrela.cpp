/*
Matheus Deyvisson, 2025
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

// Assim como definimos um Terra em circuitos, definiremos um n� n�o expandido
// que representar� o menor custo total previsto.
Node* min_node = nullptr;  

namespace noding{
	/*
	Descri��o:
		Define um espa�o de nomes (namespace) chamado open, que serve para 
		organizar e agrupar funcionalidades (como classes, fun��es, vari�veis)
		em um escopo nomeado, evitando conflitos de nomes com outras partes do
		programa ou bibliotecas externas.
		
		Acredito que foi feito assim pois Node n�o � exatamente um objeto,
		mas uma estrutura de dados e, portanto, struct. E, por legibilidade,
		n�o associamos classes<->structs, cada um no seu quadrado.
		
		Coloquei 'noding' porque queria relacionar com Node.
		
		A seguir, um exemplo de cria��o BST que voc� pode usar para testas
		as fun��es criadas aqui.
		
			Node *node = new Node(1);
			
			Node *node_l = new Node(2);
			(*node_l).up = node;
			(*node).left = node_l;
			
			Node *node_r = new Node(3);
			(*node_r).up = node;
			(*node).right = node_r;
			
			Node *node_s = new Node(99);
			(*node_s).up = node_r;
			(*node_r).right = node_s;
			
			noding::apresentar(
				node
			);
			
			delete node_s;
			delete node_l;
			delete node_r;
			delete node;
				
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
		int se_eh_esquerdo
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
			Obviamente pega um n� e o insere dentro de outra estrutura.
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
		sucedida.
		
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
		O pai do novo n� torna-se o m�nimo.
		O novo n� torna-se o m�nimo.
		
		* Estrutura na Sa�da:
		
		   		[5]
		       /   \
		     [2]   [10]
		    /   \
		  [1]    [4]
		  /
		[0] <- MIN
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
	pop_min(
		Node* raiz
	){
		/*
		Descri��o:
			Desejamos remover o menor elemento, que apesar de deveria ser
			o �ltimo elemento, n�o necessariamente ser�.
			
			Note que o m�nimo pode ter um filho, mas este necessariamente
			ser� direito.
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

}

int main()
{
	
//	Node *node = new Node(5);
//			
//	Node *node_l = new Node(2);
//	(*node_l).up = node;
//	(*node).left = node_l;
//	
//	Node *node_r = new Node(8);
//	(*node_r).up = node;
//	(*node).right = node_r;
//	
//	Node *node_s = new Node(7);
//	(*node_s).up = node_r;
//	(*node_r).left = node_s;
//	
//	min_node = node_s;
//	
//	noding::apresentar(
//		node
//	);
//	
//	noding::liberar(
//		node
//	);
	
    return 0;
}
