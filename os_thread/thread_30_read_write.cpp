#include<iostream>
#include<pthread.h>
#include<semaphore.h>

using namespace std;

int i = 0;
sem_t w_w_t;
sem_t r_w_t;
int read_count = 0;
void reader(void* arg){
	int* ptr = (int*)arg;
	read_count++;
	cout<<"thread:"<<*ptr<<"正在读呢,i:"<<i<<endl;
	read_count--;
	sem_post(&r_w_t);
}

void writer(void* arg){
	int* ptr = (int*)arg;
	sem_wait(&w_w_t);
	while(read_count>0){
		cout<<"正有读者在读，"<<"thread:"<<*ptr<<"写不了"<<endl;
 		sem_wait(&r_w_t);
	}
	cout<<"thread:"<<*ptr<<"正在写呢,i="<<i++<<endl;
	sem_post(&w_w_t);
}

void init(){
	sem_init(&r_w_t,0,1);
	sem_init(&w_w_t,0,1);
}

void* r_test(void* arg){
	for(int i=0;i<100;i++)
		reader(arg);
}

void* w_test(void* arg){
	for(int i=0;i<100;i++)
		writer(arg);
}
int main(){
	init();
	int ptr1 = 1;
	int ptr2 = 2;
	int ptr3 = 3;
	int ptr4 = 4;
	pthread_t p1,p2,p3,p4;
	pthread_create(&p1,NULL,w_test,(void*)&ptr1);
	pthread_create(&p2,NULL,r_test,(void*)&ptr2);
	pthread_create(&p3,NULL,w_test,(void*)&ptr3);
	pthread_create(&p4,NULL,r_test,(void*)&ptr4);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	cout<<"main end"<<endl;
	return 0;
}
