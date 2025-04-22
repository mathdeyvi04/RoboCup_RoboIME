/*
Por respeito � genialidade, os direitos autorais:
	Copyright (C) 2011 Justin Stoecker
	
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0
	
	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
	
Objetivo do C�digo:
	Desenvolver ferramentas que permitir�o o desenho de formas poligonais e
	retas dentro do RoboViz.
	
	� interessante que vendo o c�digo, � como se estivessemos escrevemos C.
*/
#ifndef ROBOVIZDRAW_H
#define ROBOVIZDRAW_H

#include <string>  // Biblioteca padr�o de strings em C++
#include <cstdio>  // Vers�o da biblioteca <stdio.h> escrita em C++
#include <cstring> // Vers�o da biblioteca <string.h> escrita em C++

using namespace std;

#define QUANT_DE_CARAC_PARA_PRECISAO_DE_FLOATS 6
#define FORMAT_PARA_SPRINTF "%6f"

/////////////////////////////////////////////////////////////////////////
/// Fun��es Inline
////////////////////////////////////////////////////////////////////////////

inline int 
escrever_char_no_buffer(
	unsigned char *buffer,
	unsigned char  valor
){
	/*
	Apenas trazemos a responsabilidade de atribui��o para esta fun��o.
	*/
	
	*buffer = valor;
	return 1;
}


inline int 
escrever_float_no_buffer(
	unsigned char *buffer,
	float          valor
){
	/*
	Descri��o:
		Houve um discuss�o s�ria sobre como construir essa fun��o. 
		Se confirmou que estamos trabalhando em um n�vel baixo demais
		e n�o h� necessidade de tratar o terminador nulo aqui, o que 
		impede o uso inteligente da fun��o snprintf.
		
		Sendo assim, somos for�ados a usar sprintf e memcpy.
		
	Retorno:
		Quantidade de caracteres do n�mero que foi colocada no buffer.
	*/
	
	/*
	Escrevemos o float que pode ser absolutamente qualquer coisa
	em um buffer tempor�rio.
	
	** Tentei usar um buffer tempor�rio maior, mas o maldito warning de 
	overflow estava acabando comigo.
	
	Essa fun��o faz o trabalho de formata��o e de limita��o do float.
	*/
	char temp[16];
	sprintf(
		temp,
		FORMAT_PARA_SPRINTF,
		valor
	);
	
	/*
	Garante a c�pia em exatamente a quantidade de  bytes.
	*/
	memcpy(
		buffer, 
		temp,
		QUANT_DE_CARAC_PARA_PRECISAO_DE_FLOATS 
	);
	
	return QUANT_DE_CARAC_PARA_PRECISAO_DE_FLOATS;
}


inline int 
escrever_cor_no_buffer(
	unsigned char *buffer,
	const float   *cor,		 // Cor em RGB, lembrando que os n�meros s�o menores que 1.
	int canais               // R = 0, G = 1, B = 2
){
	
	int index = 0;
	while(
		index < canais
	){
		
		escrever_char_no_buffer(
			buffer + index,
			(unsigned char) (cor[index] * 255)
		);
		
		index++;
	}
	
	// Em teoria, apenas a quantidade de canais.
	return index;
}


inline int
escrever_string_no_buffer(
	unsigned char *buffer,
	const string  *texto
){
	
	long int index = 0;  // Estaremos mexendo com stack, n�meros ser�o grandes mesmo.
	
	if(
		texto != NULL
	){
		index += (*texto).copy(
								/*
								Colocamos + index para deixar em condi��es 
								de qualquer altera��o acima.
								*/
								(char*) buffer + index,
								(*texto).length(),
								0
							  );
	}
	
	index += escrever_char_no_buffer(
		buffer + index,
		0 // colocamos o terminador nulo
	);
	
	return index;
}


////////////////////////////////////////////////////////////////////////////
/// Fun��es Amplas
////////////////////////////////////////////////////////////////////////////

/*
Cabe�alho 1: 

	0 -> Buffer Vazio
	1 -> Buffer Preenchido Com Informa��es Geom�tricas
	2 -> Buffer Preenchido Com Informa��es Textuais

Cabe�alho 2:
	
	Para Informa��es Geom�tricas
	
		0 -> C�rculo
		1 -> Linha
		2 -> Ponto
		3 -> Esfera
		4 -> Poligono
		
	Para Informa��es Textuais
		
		0 -> Anota��o Simples
		1 -> Anota��o de Agente com Texto
		2 -> Anota��o de Agente sem Texto

Para mais informa��es, veja a fun��o criar_novo_buffer.

Cada buffer criado possui uma formata��o diferente, j� que armazena informa��es
diferentes e precisa armazen�-las de forma inteligente.
*/

unsigned char* 
criar_buffer(
	const string *string_buffer,
	int          *tamanho_do_buffer
){
	/*
	Descri��o:
		Criamos um buffer que ser� usado pelas fun��es anteriores.
	
	Retorno:
		Buffer.
		
		+-----+-----+---------------------+-----+
		| 0x00| 0x00|    string_buffer    | 0x00|
		+-----+-----+---------------------+-----+
		
		Os dois espa�os vazios correspondem aos indicadores de controle, cabe�alho.
		Indicam informa��es importantes, como quantidade total ou se pode ser preenchido 
		com mais informa��es.
	*/
	
	// 1 slot para Terminador nulo do final
	// 2 slots para Cabe�alhos
	// String buffer
	*tamanho_do_buffer = 1 + 2 + ((string_buffer != NULL) ? (*string_buffer).length() : 0);
	
	// Aloca dinamicamente, logo devemos fazer o delete por fora.
	unsigned char *buffer = new unsigned char[*tamanho_do_buffer];  
	
	long int index = 0;
	
	index += escrever_char_no_buffer  ( buffer + index,             0 );  // Zeramos os cabe�alhos
	index += escrever_char_no_buffer  ( buffer + index,             0 );  // Zeramos os cabe�alhos
	index += escrever_string_no_buffer( buffer + index, string_buffer );  // 
	
	return buffer;
} 


unsigned char*
criar_circulo(
	const float  *centro,
	      float   raio,
	      float   grossura,
	const float  *cor,
	const string *nome_a_ser_setado,
	        int  *tamanho_do_buffer
){
	/*
	Criamos um buffer para transportar informa��es de c�rculo.
	*/
	
	*tamanho_do_buffer = 30 + ((nome_a_ser_setado != NULL) ? (*nome_a_ser_setado).length() : 0);
	
	unsigned char *buffer = new unsigned char[*tamanho_do_buffer];
	
	long int i = 0;
	 
	i += escrever_char_no_buffer  ( buffer + i,                 1 );  
	i += escrever_char_no_buffer  ( buffer + i,                 0 );
	
	i += escrever_float_no_buffer ( buffer + i,         centro[0] );
	i += escrever_float_no_buffer ( buffer + i,         centro[1] );
	i += escrever_float_no_buffer ( buffer + i, 	         raio );
	i += escrever_float_no_buffer ( buffer + i,          grossura );
	
	i += escrever_cor_no_buffer   ( buffer + i,            cor, 3 );
	i += escrever_string_no_buffer( buffer + i, nome_a_ser_setado );
	
	return buffer;
}


unsigned char*
criar_linha(
	const float  *inicio,
	const float  *final,
	      float   grossura,
	const float  *cor,
	const string *nome_a_ser_setado,
	        int  *tamanho_do_buffer
){
	/*
	Criamos um buffer para transportar informa��es de linha.
	*/	
	*tamanho_do_buffer = 48 + ((nome_a_ser_setado != NULL) ? (*nome_a_ser_setado).length() : 0);
	
	unsigned char *buffer = new unsigned char[*tamanho_do_buffer];
	
	long int i = 0;
	
	i += escrever_char_no_buffer(buffer + i, 1);
	i += escrever_char_no_buffer(buffer + i, 1);
	
	i += escrever_float_no_buffer( buffer + i, inicio[0] );
	i += escrever_float_no_buffer( buffer + i, inicio[1] );
	i += escrever_float_no_buffer( buffer + i, inicio[2] );
	i += escrever_float_no_buffer( buffer + i,  final[0] );
	i += escrever_float_no_buffer( buffer + i,  final[1] );
	i += escrever_float_no_buffer( buffer + i,  final[2] );
	
	i += escrever_float_no_buffer ( buffer + i,         grossura );
	i += escrever_cor_no_buffer   ( buffer + i,            cor, 3);
	i += escrever_string_no_buffer( buffer + i, nome_a_ser_setado);
	
	return buffer;
}


unsigned char*
criar_ponto(
	const float  *ponto,
	      float   tamanho,
	const float  *cor,
	const string *nome_a_ser_setado,
	        int  *tamanho_do_buffer
){
	/*
	Criando buffer para transportar informa��es de ponto.
	*/
	
	*tamanho_do_buffer = 30 + ((nome_a_ser_setado != NULL) ? (*nome_a_ser_setado).length() : 0);
	
	unsigned char *buffer = new unsigned char[*tamanho_do_buffer];
	
	long int i = 0;
	
	i += escrever_char_no_buffer  ( buffer + i,        1 );
	i += escrever_char_no_buffer  ( buffer + i,        2 );
	
	i += escrever_float_no_buffer ( buffer + i, ponto[0] );
	i += escrever_float_no_buffer ( buffer + i, ponto[1] );
	i += escrever_float_no_buffer ( buffer + i, ponto[2] );
	i += escrever_float_no_buffer ( buffer + i, tamanho  );

	i += escrever_cor_no_buffer   ( buffer + i,            cor, 3);
	i += escrever_string_no_buffer( buffer + i, nome_a_ser_setado);
	
	return buffer;
}


unsigned char*
criar_esfera(
	const float  *centro,
	      float   raio,
	const float  *cor,
	const string *nome_a_ser_setado,
	        int  *tamanho_do_buffer
){
	/*
	Criar buffer para transportar informa��es de esfera.
	*/
	
	*tamanho_do_buffer = 30 + ((nome_a_ser_setado != NULL) ? (*nome_a_ser_setado).length() : 0);
	
	unsigned char *buffer = new unsigned char[*tamanho_do_buffer];
	
	long int i = 0;
	
	i += escrever_char_no_buffer( buffer + i, 1 );
	i += escrever_char_no_buffer( buffer + i, 3 );

	i += escrever_float_no_buffer( buffer + i, centro[0] );	
	i += escrever_float_no_buffer( buffer + i, centro[1] );	
	i += escrever_float_no_buffer( buffer + i, centro[2] );	
	i += escrever_float_no_buffer( buffer + i,      raio );	
	
	i += escrever_cor_no_buffer   ( buffer + i,            cor, 3 );
	i += escrever_string_no_buffer( buffer + i, nome_a_ser_setado );
	
	return buffer;
}


unsigned char*
criar_poligono(
	const float  *vertices,
	        int  numero_de_vertices,
	const float  *cor,
	const string *nome_a_ser_setado,
	        int  *tamanho_do_buffer
){
	/*
	Criamos uma formata��o para transportar informa��es de pol�gono
	em um buffer.
	*/
	
	*tamanho_do_buffer = 18 * numero_de_vertices + 8 + ((nome_a_ser_setado != NULL) ? (*nome_a_ser_setado).length() : 0);
	
	unsigned char *buffer = new unsigned char[*tamanho_do_buffer];
	
	long int i = 0;
	
	i += escrever_char_no_buffer( buffer + i, 1 );
	i += escrever_char_no_buffer( buffer + i, 4 );
	
	i += escrever_char_no_buffer( buffer + i, numero_de_vertices );
	i += escrever_cor_no_buffer ( buffer + i,              cor, 4);
	
	for(
		int index = 0;
		index < numero_de_vertices;
		index++
	){
		
		i += escrever_float_no_buffer( buffer + index, vertices[ index * 3 + 0] );
		i += escrever_float_no_buffer( buffer + index, vertices[ index * 3 + 1] );
		i += escrever_float_no_buffer( buffer + index, vertices[ index * 3 + 2] );
	}
	
	i += escrever_string_no_buffer( buffer + i, nome_a_ser_setado );
	
	return buffer;
}


unsigned char*
criar_anotacao(
	const string *texto,
	const float  *ponto,
	const float  *cor,
	const string *nome_a_ser_setado,
	        int  *tamanho_do_buffer
){
	/*
	Criamos um buffer para transportar informa��es de anota��o e de texto.
	*/
	
	*tamanho_do_buffer = 25 + (*texto).length() + ((nome_a_ser_setado != NULL) ? (*nome_a_ser_setado).length() : 0);
	unsigned char *buffer = new unsigned char[*tamanho_do_buffer];
	
	long int i = 0;
	
	i += escrever_char_no_buffer( buffer + i, 2 );
	i += escrever_char_no_buffer( buffer + i, 0 );
	
	i += escrever_float_no_buffer( buffer + i, ponto[0] );
	i += escrever_float_no_buffer( buffer + i, ponto[1] );
	i += escrever_float_no_buffer( buffer + i, ponto[2] );
	
	i += escrever_cor_no_buffer   ( buffer + i,            cor, 3 );
	i += escrever_string_no_buffer( buffer + i,             texto );
	i += escrever_string_no_buffer( buffer + i, nome_a_ser_setado );
	
	return buffer;
}


unsigned char*
criar_anotacao_de_agente(
	const string *texto,
	 	   bool   left_team,         // ingl�s � bem melhor
	 	    int   numero_do_agente,
	const float  *cor,
	        int  *tamanho_do_buffer
){
	/*
	Em teoria, criar� buffer para transportar informa��o de anota��o de agente,
	por exemplo aquele textinho que fica em cima do agente.
	*/
	
	*tamanho_do_buffer = (texto != NULL) ? (7 + (*texto).length()) : 3;
	
	unsigned char* buffer = new unsigned char[*tamanho_do_buffer];
	
	long int i = 0;
	
	i += escrever_char_no_buffer( buffer + i, 2);
	
	if(
		texto == NULL
	){
		/*
		Note que o segundo cabe�alho � indicado com 2 e n�o h� texto.
		*/
		i += escrever_char_no_buffer( buffer + i, 2 );
		i += escrever_char_no_buffer( buffer + i, (left_team ? numero_do_agente - 1 : numero_do_agente + 127));
	}
	else{
		/*
		Note que o segundo cabe�alho � indicado com 1 e h� texto a ser colocado.
		*/
		i += escrever_char_no_buffer  ( buffer + i,      1 );
		i += escrever_char_no_buffer  ( buffer + i, (left_team ? numero_do_agente - 1 : numero_do_agente + 127));
		i += escrever_cor_no_buffer   ( buffer + i, cor, 3 );
		i += escrever_string_no_buffer( buffer + i, texto  );
	}
	
	return buffer;
}

#endif //ROBOVIZDRAW_H
