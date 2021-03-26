#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int main(){
	int * ptr = NULL;
	free(ptr);
	return 0;
}
