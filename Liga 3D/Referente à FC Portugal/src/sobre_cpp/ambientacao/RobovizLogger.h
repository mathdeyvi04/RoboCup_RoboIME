/*
Manteremos os cr�ditos por respeito.

 * Created on: 2013/06/24
 * Author: Rui Ferreira
 
//////////////////////////////////////////////////////////////////////////
 
Altera��es foram feitas para aprimorar algoritmos e aumentar legibilidade.

POSS�VEL ERRO QUE VOC� OBTER:

Bibliotecas usadas aqui est�o unicamente dispon�veis em sistemas UNIX.
logo, se voc� estiver baixado o GNU GCC Compiler MinGW para windows,
pode ter problema, j� que n�o vai encontrar as respectivas bibliotecas.

Observe minha solu��o para o problema:

https://github.com/mathdeyvi04/RoboCup_RoboIME/issues/12

*/
#ifndef ROBOVIZLOGGER_H
#define ROBOVIZLOGGER_H

/*
As bibliotecas usada no original s�o as padr�es de C.
Achei melhor aprimor�-las para C++.
*/
#include <cstdlib>
#include <cmath>
#include <cerrno>
#include <string>

/*///////////////////////////////////////////////////////////////////////////

Bibliotecas a seguir s�o bem mais espec�ficas e n�o possuem 
suas respectivas vers�es em C++.

*///////////////////////////////////////////////////////////////////////////

/*
Interface com Sistema Operacional LINUX, conseguindo lidar com:

- chamadas diretas do sistema operacional;
- opera��es de entrada e de sa�da;
- controle de processos, sleep por exemplo;
- acesso a diret�rios.
*/
#include <unistd.h>  

/*
Para tiparmos vari�veis e ponteiros da melhor forma poss�vel.
S�o struct amplamente desenvolvidas como:

- pid_t: Para ID de processos da CPU;
- size_t: Para dimensionar precisamente objetos;
- off_t: Para deslocamentos em arquivos.
*/
#include <sys/types.h>

/*//////////////////////////////////////////////////////////////////////////

As bibliotecas a seguir s�o focadas em programa��o de REDES em 
Sistemas UNIX/LINUX.

Juntas elas formam a base para comunica��o TCP/UDP, permitindo desde simples
clientes at� servidores complexos.

*///////////////////////////////////////////////////////////////////////////

/*
Cria��o e gerenciamento de sockets, os quais s�o canais de comunica��o
entre processos locais e/ou remotos.

Focada em suportar protocolos:

- TCP: 
	Transmisson Control Protocol, comunica��o ideal para aplica��es que exigem
	confiabilidade acima de velocidade.

- UDP:
	User Datagram Protocol, comunica��o ideal para aplica��es
	que exigem velocidade acima de confiabilidade e integridade de dados.
*/
#include <sys/socket.h>

/*
Header fundamental para programa��o de redes via protocolo TCP.
Sendo focado em sistemas UNIX, possui defini��es essenciais para 
cria��o de sockets e manipula��o de endere�os de rede.

Cont�m MUITAS defini��es essenciais para manipula��es de endere�os IP
e portas, structs poderosas e constantes essenciais.

Acredito que, por quest�o de curiosidade e de brio, voc� tamb�m 
deva pelo menos passar os olhos neste arquivo de alta complexidade.

Caso esteja em Windows e n�o possa ver:
	https://github.com/leostratus/netinet/blob/master/in.h

*/
#include <netinet/in.h>

/*
Um pouco mais simples que a anterior, focada na convers�o de 
endere�os IP entre formatos leg�veis para humanos, como 192.172.0.1,
e formatos bin�rios utilizados nas fun��es que envolvem sockets.


Caso esteja em Windows e n�o possa ver, experimente:
	https://github.com/openbsd/src/blob/master/include/arpa/inet.h
*/
#include <arpa/inet.h>

/*
API de sockets em C, usada para resolver nomes de Host, servi�os e
endere�os de rede, funcionando como uma interface entre nomes simb�licos
e seus endere�os n�mericos, como "educa.ime.eb.br" -> "192.120.1.2".

Caso esteja em Windows e n�o possa ver, experimente:
	https://github.com/openbsd/src/blob/master/include/netdb.h
*/
#include <netdb.h>


#include "RobovizDraw.h"
#include "Singular.h"


/*//////////////////////////////////////////////////////////////////////////////

As defini��es a seguir s�o bem restritas aos t�cnicos, mas farei o poss�vel.

*/////////////////////////////////////////////////////////////////////////////

#define ROBOVIZ_HOST "localhost"
#define ROBOVIZ_PORT "32769"


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

class RobovizLogger {
	
private:
	// Desejamos impedir o uso indiscriminado.
	
	// Construtores
	RobovizLogger() {}
	RobovizLogger( const RobovizLogger& ) {}
	RobovizLogger& operator=( const RobovizLogger& ) {}
	
	// Destrutores
	/*
	Qual a diferen�a entre usarmos:
	
	-> ~ RobovizLogger();
	
	-> virtual ~ RobovizLogger();
	
	Est� no comportamento da destrui��o de objetos em hierarquias de heran�a.
	
	~classe(); � um destrutor comum, chamado automaticamente quando
	um objeto da classe � destru�do, mas n�o garante a destrui��o correta
	de objetos derivados se for chamado atrav�s de um ponteiro para a
	classe base.
	
	Exemplo:
	
		delete ponteiroBase;
		
		+------------------+      
		|   ClasseBase     |       < s� essa parte � deletada
		+------------------+
		
		+------------------+
		| ClasseDerivada   |     < essa parte continua na mem�ria!
		|  (camada extra)  |
		+------------------+
	
	virtual ~classe(); � um destrutor virtual, que garante que,	ao deletar
	um objeto derivado por meio de um ponteiro para a 	classe base, o 
	estrutor do objeto derivado seja chamado corretamente, 	evitando 
	azamento de mem�ria ou destrui��o incompleta.
	
	Exemplo:
	
		delete ponteiroBase;

		+------------------+
		| ClasseDerivada   |     ? primeiro essa parte � destru�da
		+------------------+
		
		+------------------+
		|   ClasseBase     |     ? depois essa aqui
		+------------------+
	*/
	virtual ~RobovizLogger() {}
	
	// Atributos
	bool se_ja_esta_inicializada = false;
	
	/*
	Depois que entendermos melhor o c�digo, devemos alterar oq s�o esses nomes.
	*/
	int socket_number;
	struct addrinfo *p;
	struct addrinfo *servinfo;
	
	
	// Amizades
	friend class Singular<RobovizLogger>;
	
public:	
	
	static RobovizLogger* 
	obter_instancia(){
		/*
		Criar uma inst�ncia �nica da classe.
		*/	
		return Singular<RobovizLogger>::obter_instancia();
	}
	
	int init(){
		
		if(
		// garantir que haja apenas uma inst�ncia.
			se_ja_esta_inicializada
		){
			return 0;
		}
		
		struct addrinfo criterios_de_busca;
		int rv;
		int numbytes;
		
		criterios_de_busca = {0};
		
		
		
		
		
	}
	
	
	
	
};












#endif // ROBOVIZLOGGER_H
