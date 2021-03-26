#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

pthread_mutex_t lock;
pthread_cond_t cond;
int a = 0;
void* test1(void* arg){
	pthread_mutex_lock(&lock);
	while(a==0){
		cout<<"a="<<a<<",wait"<<endl;
		pthread_cond_wait(&cond,&lock);
	}
	cout<<"wait over,a="<<a<<endl;
	pthread_mutex_unlock(&lock);
}

void* test2(void* arg){
	pthread_mutex_lock(&lock);
	cout<<"a shezhi wei 1,notify"<<endl;
	a = 1;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
}
int main(){
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&lock,NULL);
	pthread_t p1;
	pthread_t p2;
	pthread_create(&p1,NULL,test1,NULL);
	pthread_create(&p2,NULL,test2,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);	
	return 0;
}
