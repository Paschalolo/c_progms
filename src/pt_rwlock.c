/*
 *	Read-Write lock 
 *	Copyright (c) Mr Paschal Ahanmisi 2024 - 2026
 * */

#include <pthread.h>
#include <stdio.h>


constexpr int  NREADERS =  2 ; 
constexpr int NWRITERS = 1 ; 
constexpr int NTASKS = 4 ; 
constexpr int DELAY_COUNT_RD = 200'000'000 ; 
constexpr int DELAY_COUNT_WR = 100'000'000 ; 

unsigned int global_count = 0 ; 
