/*************************************
* Lab 1 Exercise 3
* Name     : Eugene
* Matric No: A0116631N
* Lab Group: 8
*************************************/

#include <stdio.h>

// Aliases
typedef int (*arithFuncPtr)(int, int);

// Function Prototype 
// (Use leading underscore to avoid conflict with the built in keyword)
int _add(int x, int y);
int _sub(int x, int y);
int _mul(int x, int y);
int _div(int x, int y);
int _zero(int x, int y);

int main(){
	int x, y, op, result;
	arithFuncPtr opPtr;
	while (scanf("%i %i %i", &x, &y, &op) == 3){
		switch (op){
			case 1: opPtr = _add; break;
			case 2: opPtr = _sub; break;
			case 3: opPtr = _mul; break;
			case 4: opPtr = _div; break;
            default: opPtr = _zero; break;
		}
		result = (*opPtr)(x, y);
		printf("%i\n", result);
	}
	return 0;
}

int _add(int x, int y){
	return x + y;
}

int _sub(int x, int y){
	return x - y;
}

int _mul(int x, int y){
	return x * y;
}

int _div(int x, int y){
	return x / y;
}

int _zero(int x, int y){
    return 0;
}
