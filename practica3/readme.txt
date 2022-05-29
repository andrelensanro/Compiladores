	
	En esta practica se pretende crear afd sin usar el menu. 
	Se creara el AFN mediante las acciones semanticas del descenso recursivo. 
	
	Se hará uso de:
	** Analizador lexico, que está en la carpeta de librerías.
	** Gramatica de expresiones regulares.

	Inicio: 28-12-2020
	Video: clase 7 Descenso Recursivo-Expr Regulares a AFN 
	
	AFD que entra en el analizador lexico es el que detecte
	los siguientes simbolos terminales:

	#define union 1000
	#define concatenacion 1010
	#define transicion 1020
	#define cerradura_K 1030
	#define operador_opcional 1040
	#define parentIzq 1050
	#define parentDer 1060
	#define corchIzq 1070
	#define corchDer 1080
	#define guion 1090
	#define simb 1100

	Notas:
	FECHA		DESCRIPCION:
	03-12-2021	Esta versión trabaja a partir de una expresion regular que se da desde .cpp 
			El afd que usa para el analizador lexico, está en las misma ubicación que 
			el construccionAFN_gramExpReg.cpp 
			En ese .txt el rango [!-~] es para simb y se usa ascii.
			
			Las expresiones con las que se probó y fueron soluciones correctas son: 3/3
			[s-s]*|[t-t]*
			([s-s]*)|[t-t]*
			[s-s]|[t-t]+|[p-p]*
	
			Da como respuesta un afn, que se ve mediante printMy_afn(solve) en consola. 

			OJO.

			Los txt que estan en la carpeta inputs, nunca los use, ya que no me agarra los archivos para leer si estan en otra carpeta. 
			

