#include<iostream>
#include<pthread.h>

using namespace std;
int a = 0;
void *test(void* arg){
	for(int i=0;i<10;i++){
		a++;
		cout<<"thread "<<pthread_self()<<" a="<<a<<endl;
	}
}
int main(){
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_create(&p1,NULL,test,NULL);
	pthread_create(&p2,NULL,test,NULL);
	pthread_create(&p3,NULL,test,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	return 0;
}
