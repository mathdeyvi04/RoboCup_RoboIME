/*
Matheus Deyvisson, 2025

Utilizei apenas um arquivo header a fim de evitar a repeti��o 
desnecess�ria de v�rios arquivos.

Inclui os arquivos:
    -> Vector3f.cpp
    -> Vector3f.h
    -> Geometry.cpp
    -> Geometry.h

Fiz algumas modifica��es para aprimorar legibilidade.
Testes j� foram realizados.
*/
#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include <cmath>
#include <math.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

#define EPSILON 1e-6  // No Original, era 1e-10, o que eu julgo desnecessariamente pequeno..
#define PI 3.1415926535f

/*
Fun��es que ser�o amplamente utilizadas
*/

inline float cos_deg(
	float ang_degraus
){
	/*
	Descri��o:
		A fun��o base da biblioteca somente aceita radianos.
	*/
	return cos( ang_degraus * PI / 180 );
}


inline float sin_deg(
	float ang_degraus
){
	return sin( ang_degraus * PI / 180 );
}


inline float atan2_deg(
	float img,
	float real
){
	/*
	Descri��o:
		Calcula o arco cuja tangente � img / real, em degraus.
	*/
	
	if(
		fabs(img) < EPSILON && fabs(real) < EPSILON
	){
		return 0.0f;
	}
	
	return atan2(img, real) * 180 / PI;
}


class Vetor2D {
public:
	/*
	Descri��o:
		Representa a posi��o no espa�o 2D.
		
		Uma posi��o ser� representada em coordenadas
		cartesianas, (x, y).
		
		Cr�ditos para o Alto N�vel de Trabalho:
		- @author Hugo Picado (hugopicado@ua.pt)
		- @author Nuno Almeida (nuno.alm@ua.pt)
		- Adapted - Miguel Abreu
	*/
	
	float x;
	float y;
	
	Vetor2D(
		/*
		Iniciamos um vetor com componentes x e y.
		Caso nenhum valor seja passado, assumir� 0.
		*/
		float valor_x,
		float valor_y
	) : x(valor_x), y(valor_y) {}
	
	static void verificar(const Vetor2D& vetor){
		printf("(%f, %f)", vetor.x, vetor.y);
	}
	
	////////////////////////////////////////////////////////////////////////
	/// Operadores de Aritm�tica
	////////////////////////////////////////////////////////////////////////
	
	/*
	Observe que passaremos argumentos por refer�ncia! Como se fossem
	ponteiros.
	
	O const no final indica que n�o estaremos modificando o vetor dado, 
	estaremos criando um novo!
	*/
	
	// - Vector2D( 1, 2 ) -> Vector2D( -1, -2 )
	Vetor2D operator-() const {
		return Vetor2D( - x, - y );
	}
	
	
	Vetor2D operator+( const float   &escalar     ) const {
		/*
		Soma com escalar resulta em componentes somadas ao escalar.
		*/
	    return Vetor2D( x + escalar, y + escalar );
	}
	Vetor2D operator+( const Vetor2D &outro_vetor ) const {
		/*
		Soma de outros vetores � a soma de suas componentes.
		*/
		return Vetor2D( x + outro_vetor.x, y + outro_vetor.y );
	}
	
	
	Vetor2D operator-( const float   &escalar     ) const {
		return Vetor2D( x - escalar, y - escalar);
	}
	Vetor2D operator-( const Vetor2D &outro_vetor ) const {
		return Vetor2D( x - outro_vetor.x, y - outro_vetor.y );
	}
	
	
	Vetor2D operator*( const float   &escalar     ) const {
		return Vetor2D( x * escalar, y * escalar );
	}
	Vetor2D operator*( const Vetor2D &outro_vetor ) const {
		/*
		N�o � produto escalar pois gerar� novo vetor.
		*/
		return Vetor2D( x * outro_vetor.x, y * outro_vetor.y);
	}
	
	
	Vetor2D operator/( const float   &escalar     ) const {
		/*
		Assim como no produto com escalar, aqui faremos divis�o com escalar.
		*/
		return Vetor2D( x / escalar, y / escalar );
	}
	Vetor2D operator/( const Vetor2D &outro_vetor ) const {
		/*
		Divis�o de componente por componente.
		*/
		return Vetor2D( x / outro_vetor.x, y / outro_vetor.y);
	}
	
	////////////////////////////////////////////////////////////////////////
	/// Operadores de Atribui��o
	////////////////////////////////////////////////////////////////////////
	
	/*
	Os m�todos a seguir alteram o seu pr�prio valor.
	N�o criam novos.
	*/
	
	// Vetor2D vetor = 1 -> Vector2D( 1, 1 )
	void operator =( const float   &escalar     ) {
		x = escalar;
		y = escalar;
	}
	
	void operator+=( const float   &escalar     ){
		/*
		Soma o escalar �s componentes.
		*/
		x += escalar;
		y += escalar;
	}
	void operator+=( const Vetor2D &outro_vetor ) {
		/*
		Somar� as respectivas componentes
		*/
		x += outro_vetor.x;
		y += outro_vetor.y;
	}
	
	void operator-=( const float   &escalar     ) {
		x -= escalar;
		y -= escalar;
	}
	void operator-=( const Vetor2D &outro_vetor ) {
		x -= outro_vetor.x;
		y -= outro_vetor.y;
	}
	
	void operator*=( const float   &escalar     ) {
		x *= escalar;
		y *= escalar;
	}
	void operator*=( const Vetor2D &outro_vetor ) {
		x *= outro_vetor.x;
		y *= outro_vetor.y;
	}
	
	void operator/=( const float   &escalar     ) {
		x /= escalar;
		y /= escalar;
	}
	void operator/=( const Vetor2D &outro_vetor ) {
		x /= outro_vetor.x;
		y /= outro_vetor.y;		
	}
	
	bool operator!=( const float   &escalar     ) {
		return ( x != escalar ) || ( y != escalar );
	}
	bool operator!=( const Vetor2D &outro_vetor ) {
		return ( x != outro_vetor.x ) || ( y != outro_vetor.y );
	}
	
	bool operator==( const float   &escalar     ) {
		return ( x == escalar) && ( y == escalar );
	}
	bool operator==( const Vetor2D &outro_vetor ) {
		return ( x == outro_vetor.x ) && ( y == outro_vetor.y );
	}
	
	//////////////////////////////////////////////////////////////////////
	/// M�todos
	//////////////////////////////////////////////////////////////////////
	
	// Admito que os nomes em ingl�s s�o mais fodas.
	float InnerProduct( const Vetor2D &outro_vetor) const {
		//	N�o far� modifica��es nos vetores.
		return x * outro_vetor.x + y * outro_vetor.x;
	}
	
	float CrossProduct( const Vetor2D outro_vetor ) {
		/*
		Componente da 3� dimens�o vetor produto vetorial dos vetores dados.
		*/
		return x * outro_vetor.y - y * outro_vetor.x;
	}
	
	float modulo() const {
		return sqrt(x * x + y * y);
	}
	
	float obter_distancia    ( const Vetor2D outro_vetor ) {
		/*
		Note que � o m�dulo do vetor diferen�a.
		*/
		return (*this - outro_vetor).modulo();
	}
};


class Vetor3D {
	/*
	Descri��o:
		Representar� a posi��o em 3 valores float.
		
	Cr�ditos:
	* \author Hugo Picado (hugopicado@ua.pt)
 	* \author Nuno Almeida (nuno.alm@ua.pt)
 	* Adapted - Miguel Abreu
	*/
	
public:
	
	float x;
	float y;
	float z;
	
	/////////////////////////////////////////////////////////////////////
	/// Construtores e Destrutores
	/////////////////////////////////////////////////////////////////////		
	
	// Defini��o vazia
	Vetor3D() : x(0), y(0), z(0) {}
	
	
	// Defini��o usando n�meros como entrada
	Vetor3D(
		float v_x, 
		float v_y,
		float v_z
	) : x(v_x), y(v_y), z(v_z) {}
	
	
	// Defini��o usando outro vetor, criar� uma c�pia do mesmo
	Vetor3D(
		const Vetor3D& outro_vetor
	) : x(outro_vetor.x), y(outro_vetor.y), z(outro_vetor.z) {}
	
	
	// Defini��o usando um vetor 2D, criando um novo vetor e de componente z nula
	Vetor3D(
		const Vetor2D& outro_vetor
	) : x(outro_vetor.x), y(outro_vetor.y), z(0) {}
		
	~Vetor3D() {} // Apenas o destrutor.
	
	static void verificar(const Vetor3D& vetor){
		printf("(%f, %f, %f)", vetor.x, vetor.y, vetor.z);
	}
	
	///////////////////////////////////////////////////////////////////////
	/// Outros M�todos de Defini��o
	///////////////////////////////////////////////////////////////////////
	
	float obter_x() const { return x; }
	float obter_y() const { return y; }
	float obter_z() const { return z; }

	void setar_todos(
		float v_x,
		float v_y,
		float v_z
	){

		x = v_x;
		y = v_y;
		z = v_z;
	}
	void setar_x( float v_x ) { x = v_x; }
	void setar_y( float v_y ) { y = v_y; }
	void setar_z( float v_z ) { z = v_z; }
	
	float operator[]( const int index ) const {
		/*
		Acessar elementos do vetor a partir de indexs de um array.
		*/
		float valor = 0;
		switch ( index ){
			case 0:
				valor = x;
				break;
			case 1:
				valor = y;
				break;
			case 2:
				valor = z;
				break;

			default:
				/*Houve um erro obviamente.*/
				break;
		}

		return valor;
	}
	
	///////////////////////////////////////////////////////////////////////
	/// Operadores de Aritm�tica
	///////////////////////////////////////////////////////////////////////
	
	Vetor3D operator+( const Vetor3D& outro_vetor ) const {
		return Vetor3D(
						x + outro_vetor.x,
						y + outro_vetor.y,
						z + outro_vetor.z
					  );
	}   
	Vetor3D operator+( float escalar ) const {
		return Vetor3D(
						x + escalar,
						y + escalar,
						z + escalar
					  );
	}                   
	            
				          
	Vetor3D operator-( const Vetor3D& outro_vetor ) const {
		return Vetor3D(
						x - outro_vetor.x,
						y - outro_vetor.y,
						z - outro_vetor.z
					  );
	}
	Vetor3D operator-( float escalar ) const {
		return Vetor3D(
						x - escalar,
						y - escalar,
						z - escalar
					  );
	} 
	Vetor3D operator-() const {
		return Vetor3D(
						- x,
						- y,
						- z
			   		  );
	}
	
	
	Vetor3D operator*( const Vetor3D& outro_vetor ) const {
		return Vetor3D(
						x * outro_vetor.x,
						y * outro_vetor.y,
						z * outro_vetor.z
					  );
	}
	Vetor3D operator*( float escalar ) const {
		return Vetor3D(
						x * escalar,
						y * escalar,
						z * escalar
					  );
	}
	
	
	Vetor3D operator/( const Vetor3D& outro_vetor ) const {
		return Vetor3D(
						x / outro_vetor.x,
						y / outro_vetor.y,
						z / outro_vetor.z
					  );
	}
	Vetor3D operator/( float escalar) const {
		return Vetor3D(
						x / escalar,
						y / escalar,
						z / escalar
					  );
	}
	
	
	Vetor3D operator%( float escalar ) const {
		return Vetor3D(
						fmod(x, escalar),
						fmod(y, escalar),
						fmod(z, escalar)
					  );
	}
	
	//////////////////////////////////////////////////////////////////////
	/// Operadores de Atribui��o
	//////////////////////////////////////////////////////////////////////
	
	bool operator==( const Vetor3D& outro_vetor ) const {
		return x == outro_vetor.x && y == outro_vetor.y && z == outro_vetor.z;
	}
	
	
	Vetor3D operator+=( const Vetor3D& outro_vetor) {
		x += outro_vetor.x;
		y += outro_vetor.y;
		z += outro_vetor.z;
		
		return *this;  // Garantir a sem�ntica	
	}
	Vetor3D operator+=( float escalar ) {
		x += escalar;
		y += escalar;
		z += escalar;	
		
		return *this;  // Garantir a sem�ntica
	}
	
	
	Vetor3D operator-=( const Vetor3D& outro_vetor) {
		x -= outro_vetor.x;
		y -= outro_vetor.y;
		z -= outro_vetor.z;
		
		return *this;	
	}
	Vetor3D operator-=( float escalar ) {
		x -= escalar;
		y -= escalar;
		z -= escalar;
		
		return *this;	
	}
	
	
	Vetor3D operator/=( float escalar ) {
		x /= escalar;
		y /= escalar;
		z /= escalar;
		
		return *this;
	}
	
	//////////////////////////////////////////////////////////////////////
	/// M�todos de C�lculo
	//////////////////////////////////////////////////////////////////////
	
	float InnerProduct( const Vetor3D& outro_vetor ) const {
		return x * outro_vetor.x + y * outro_vetor.y + z * outro_vetor.z;
	}
	
	
	Vetor3D CrossProduct( const Vetor3D& outro_vetor ) const {
		/*
		Retornar� o produto vetorial.
		*/
		return Vetor3D(
						y * outro_vetor.z - z * outro_vetor.y,
						z * outro_vetor.x - x * outro_vetor.z,
						x * outro_vetor.y - y * outro_vetor.x
					  );
	}
	
	
	float modulo() const {
		return sqrt(x * x + y * y + z * z);
	}
		
	
	Vetor3D normalize() const {
		/*
		Vamos pegar versor unit�rio do vetor.
		*/
		return (*this) / (*this).modulo();
	}
	
	
	Vetor3D para_cartesiano() const {
		/*
		Receberemos um vetor em coordenadas esfericas, o qual:
			x -> distancia
			y -> theta, em graus, �ngulo horizontal segundo original.
			z -> phi, em graus,   �ngulo vertical   segundo original.
		Para transform�-lo em cartesianas.
		*/
		return Vetor3D(
						x * cos_deg( z ) * cos_deg( y ),
						x * cos_deg( z ) * sin_deg( y ),
						x * sin_deg( z )
					  );
	} 
	
	
	Vetor3D para_esferica() const {
		/*
		Receberemos um vetor em coordenadas cartesianas e 
		o levamos para coordenadas esf�ricas.
		x -> distancia
		y -> theta
		z -> phi
		*/
		
		return Vetor3D(
						(*this).modulo(),
						atan2_deg( y, x ),
						atan2_deg( z, sqrt(x * x + y * y))
					  );
	}
	
	
	float obter_distancia( const Vetor3D& outro_vetor ) const {
		return (*this - outro_vetor).modulo();
	}
	
	
	Vetor2D para_2D() const {
		/*
		Transformar� o vetor de 3 dimens�es em de 2 dimens�es,
		ignorando a terceira.
		*/
		return Vetor2D(
						x,
						y
					  );
	}
	
	/*
	Esse static � como se fosse o staticmethod do Python. Garante
	que n�o seja necess�rio uma inst�ncia da classe para execu��o 
	do mesmo.
	*/
	static Vetor3D ponto_medio(
		const Vetor3D v1,
		const Vetor3D v2
	) {
		return (v1 + v2) / 2;
	}
};

#endif // GEOMETRIA_H
