#include "A_Simulando.h"

int
main(
	/*
	Quantos argumentos foram passados.
	Sendo que o nome do .exe j� conta como 1 argumento.
	*/
	int argc,
	/*
	Cont�m os argumentos passados. 
	Cada elemento do vetor � uma string representando um argumento.
	*/
	char* argv[]
){
	Display display = inicializar_display();
	
	if (
		(display.janela == NULL) || (display.renderizador == NULL)
	){
		apresentar_erro(
			"Houve erro na inicializa��o da janela."
		);
		return 1;
	}
	
	int simulation_is_running = 1;
	
	while(
		simulation_is_running
	){
		//entrada_de_usuario();
		//atualizacao_de_estado();
		//render();
		
		break;
	}
	
	
	destruir_display(
		display
	);
    
    printf("\n\n");
	system("pause");
    return 0;
}

