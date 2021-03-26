#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<pthread.h>

using namespace std;
void * mythread(void * arg){
	cout<<"this is a thread"<<endl;
	cout<<"this arg is :"<< *(int*)arg<<endl;
	int temp = 0;

	return (void*)(&temp);
}
int main(){
	pthread_t pt;
	int a = 1;
	int res = pthread_create(&pt,NULL,mythread,&a);
	void * ress;
	pthread_join(pt,&ress);
	cout<<"aaa"<<endl;
	return 0;
}
