#include<iostream>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

sem_t mutex;
sem_t empty;
sem_t full;
int buffer;
const int buffer_size=20;

void produce(){
//	if(buffer==buffer_size){
//	sem_wait(&mutex);
	sem_wait(&full);
	sem_wait(&mutex);
	buffer++;
	cout<<"生产了一个当前有:"<<buffer<<endl;
	sem_post(&mutex);
	sem_post(&empty);
}

void consume(){
	sem_wait(&empty);
	sem_wait(&mutex);
	buffer--;
	cout<<"消费了一个，当前剩余："<<buffer<<endl;
	sem_post(&mutex);
	sem_post(&full);
}
void init(){
	buffer = 0;
	sem_init(&mutex,0,1);
	sem_init(&empty,0,0);
	sem_init(&full,0,20);
}
void* p_test(void* arg){
	for(int i=0;i<100;i++)
		produce();	
}

void* c_test(void* arg){
	for(int i=0;i<100;i++)
		consume();
}
int main(){
	init();
	pthread_t p1,p2,p3,p4;
	pthread_create(&p1,NULL,p_test,NULL);
	pthread_create(&p2,NULL,c_test,NULL);
	pthread_create(&p3,NULL,p_test,NULL);
	pthread_create(&p4,NULL,c_test,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	return 0;
}
