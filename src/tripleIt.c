/*
 *	Libary functions 
 *	Authored by Mr. Paschal Ahanmisi
 *	Copyright (c) 2024 - 2025 , 2026 Mr Paschal Ahanmisi All rights reserved 
 * */


#include <stdio.h>

/*
 *	Compute and return the triple of the integr input values
 * */

#if WINDOWS
__declspec(dllexport) int __cdecl tripleIt(int x) 
#else 
int tripleIt(int x) 
#endif
{
	printf("The libary function tripleIt() was called \n");
	return (3 * x) ; 
}

