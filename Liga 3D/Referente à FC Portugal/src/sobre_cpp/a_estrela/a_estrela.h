/*
Matheus Deyvisson, 2025
*/

#ifndef A_ESTRELA_H
#define A_ESTRELA_H

////////////////////////////////////////////////////////////////////////////
/// Vari�veis Inerentes ao Algoritmo
////////////////////////////////////////////////////////////////////////////

struct Node{
    // Inerentes a Grafos BST
    // Por favor nao, algumas coisas devem sempre ser ingl�s.
    Node* left = nullptr;  // Filho Esquerdo (Conex�o de Descida)
    Node* right = nullptr;  // Filho Direito (Conex�o de Descida)
    Node* up = nullptr;  // Pai (conex�o de subida)

    // Inerentes ao algoritmo.
    Node* parente = nullptr;
    float custo_pontual = 0;
    float valor = 0;
    
    
    // Inicializa��es
    Node(int valor) : valor(valor) {}
	
	Node(int valor, Node* left) : valor(valor), left(left) {}
	
	Node(int valor, Node* left, Node* right) : valor(valor), left(left), right(right) {}
	
};

extern void a_estrela(
    float parametros[],
    int quantidade_de_parametros
);

extern float caminho_final[
    // Acredito que seja o comprimento total
    2050
];

extern int tamanho_caminho_final;

////////////////////////////////////////////////////////////////////////////
/// Defini��es Inerentes � Otimiza��o
////////////////////////////////////////////////////////////////////////////

#define SQRT_2 1.414213562373095f
#define QUANT_LINHAS 321
#define QUANT_COLUNAS 221
#define DIST_MAX 5  // Por exemplo, m�xima dist�ncia � um alvo.
#define LINHA_DO_GOL 312  // Linha alvo quando a vari�vel ir_ao_gol � verdadeira.

#define TAMANHO_DO_AMORTECIMENTO 6  // relacionado � fun��o adicionar_espaco_de_amortecimento.
////////////////////////////////////////////////////////////////////////////
/// Representa��o do Campo
////////////////////////////////////////////////////////////////////////////

/*
Map dimensions: 32m*22m 
col 0  ...  col 220
                   line 0
 --- our goal ---  line 1
 |              |  line 2        
 |              |  line 3
 |--------------|  ...
 |              |  line 317
 |              |  line 318
 -- their goal --  line 319
                   line 320
N�o me atrevi a alterar isso.
Cr�ditos: Miguel Abreu.               
*/  

/*
[(H)ard wall: -3, (S)oft wall: -2, (E)mpty: 0, 0 < Cost < inf] 
As seguintes defini��es representam a matriz de pontos dispon�veis do campo.
Note que h� -3, -2, 0, sendo respectivamente Hard Wall, Soft Wall e Empty.

Parece e � confuso, entretanto, foque apenas no fato da representa��o e que fazemos
assim para preservar a legibilidade.
*/
#define H27 -3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3  // Elementos de Hard Wall
#define S11 -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2  // Elementos de SoftWall
#define S19 S11,-2,-2,-2,-2,-2,-2,-2,-2  // Elementos de SoftWall
#define S97 S11,S11,S11,S11,S11,S11,S11,S11,-2,-2,-2,-2,-2,-2,-2,-2,-2  //
#define S98 S11,S11,S11,S11,S11,S11,S11,S11,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2
#define S221 S98,S98,S11,S11,-2,-2,-2
#define E19 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
#define E197 E19,E19,E19,E19,E19,E19,E19,E19,E19,E19,0,0,0,0,0,0,0
#define L0 S221                              // Line 0: soft W
#define L0_1 L0,L0
#define L2 S97,H27,S97                       // Line 2: soft W, (goal post, back net, goal post), soft W
#define L2_5 L2,L2,L2,L2
#define L6 S98,-3,-3,-3,S19,-3,-3,-3,S98     // Line 6: soft W, goal post, soft W, goal post, soft W
#define L6_10 L6,L6,L6,L6,L6
#define L11 S98,-2,-3,-3,S19,-3,-3,-2,S98  // Line 11:soft W, empty field, goal post, soft W, goal post,empty field, soft W
#define L12 S11,-2,E197,-2,S11                     // Line 12:soft W, empty field, soft W

#define L12x33 L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12,L12
#define LIN12_308 L12x33,L12x33,L12x33,L12x33,L12x33,L12x33,L12x33,L12x33,L12x33

#define L309 S98,-2,-3,-3,E19,-3,-3,-2,S98  // Line 309: soft W, empty field, goal post, empty field, goal post,empty field, soft W
#define L310 S98,-3,-3,-3,E19,-3,-3,-3,S98    // Line 310: soft W, goal post, inside goal, goal post, soft W
#define L310_314 L310,L310,L310,L310,L310




























#endif // A_ESTRELA_H
