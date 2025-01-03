#include "B_FuncoesFront.h"

Display
inicializar_display(
	void
){
	/*
	Descri��o:
		Fun��o respons�vel por verificar e inicializar a janela e o renderizador.
		Como s�o estruturas que precisamos juntas, � mais interessante que usemos 
		uma struct da uni�o delas.
	
	Retorno:
		Display em condi��es de ser usada, sendo este composto pela janela e renderizador;
		Display com renderizador NULL, caso apenas este tenha dado erro.
		Display NULO.
	*/
	
	Display resultado = {
		NULL,
		NULL
	};
	
	if(
		SDL_Init(
			SDL_INIT_EVERYTHING
		) != 0
	){
		apresentar_erro(
			"Houve erro ao inicializar ferramentas.\n"
		);
		
		return resultado;
	}
	
	SDL_Window *janela = SDL_CreateWindow(
		"Minha Janela",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		COMPRIMENTO_TELA,
		ALTURA_TELA,
		SDL_WINDOW_SHOWN
	);
	
	if(
		!janela
	){
		apresentar_erro(
			"Houve erro ao tentar criar janela.\n"
		);
		
		return resultado;
	}
	
	resultado.janela = janela;
	
	SDL_Renderer *renderizador = SDL_CreateRenderer(
		janela,  // � qual janela vamos anex�-lo.
		-1,  // Qual o c�digo do display que vamos usar, -1 default.
		0  // N�o desejamos caracter�sticas especiais.
	);
	
	if(
		!renderizador
	){
		apresentar_erro(
			"Houve erro ao tentar criar renderizador."
		);
		
		return resultado;
	}
	
	resultado.renderizador = renderizador;
	
	return resultado;
}


int
destruir_display(
	Display display
){
	/*
	Descri��o:
		Fun��o respons�vel por fechar corretamente o display.
	
	Par�metros:
		Autoexplicativo.
	
	Retorno:
		Encerramento do display.
	*/
	
	
	if (
		display.renderizador != NULL
	){
		SDL_DestroyRenderer(
			display.renderizador
		);
	}
	
	if (
		display.janela != NULL
	){
		SDL_DestroyWindow(
			display.janela
		);
	}
	
	SDL_Quit();
	
	printf("\nEncerrado com sucesso!");
	
	return 0;
}


void 
entrada_de_usuario(){
	/*
	Descri��o:
		Fun��o respons�vel por gerenciar o input do
		usu�rio.
	
	Par�metros:
		
	Retorno:
		Chamada das respectivas fun��es de entrada.
	*/
}


void
atualizacoes_de_estado(){
	/*
	Descri��o:
		Fun��o respons�vel por gerenciar as respectivas
		atualiza��es de cada um dos membros da simula��o.
	
	Par�metros:
		
	Retorno:
		Membros da simula��o atualizados de forma multiprocessada.
	*/	
}


void
render(){
	/*
	Descri��o:
		Fun��o respons�vel por gerenciar as atualiza��es na tela.
	
	Par�metros:
		
	Retorno:
		Tela atualizada conforme as necessidades de renderiza��o.
	*/
}


