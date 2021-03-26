#include<iostream>
#include<pthread.h>

using namespace std;

int buffer ;
const int buffer_size = 20;
pthread_mutex_t mutex;
pthread_cond_t empty;
pthread_cond_t full;

void produce(){
	pthread_mutex_lock(&mutex);
	//检查缓冲区是否满了
	while(buffer==buffer_size){
		cout<<"produce failed,bufffer overside"<<endl;
		pthread_cond_wait(&full,&mutex);
	}
	//上所，生产
//	pthread_mutex_lock(&mutex);
	buffer++;
	cout<<"生产了一个，当前："<<buffer<<endl;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&empty);
	//pthread_mutex_unlock(&mutex1);
}

void consume(){
	pthread_mutex_lock(&mutex);
	//检查缓冲区为空
	while(buffer==0){
		cout<<"consume failed, buffer NULL"<<endl;
		pthread_cond_wait(&empty,&mutex);
	}
	//上所 消费
//	pthread_mutex_lock(&mutex);
	buffer--;
	cout<<"消费了一个，剩余:"<<buffer<<endl;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&full);
//	pthread_mutex_unlock(&mutex1);
}

void init(){
	buffer = 0;
	//buffer_size = 20;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&empty,NULL);
	pthread_cond_init(&full,NULL);
}

void* test1(void* arg){
	for(int i=0;i<100;i++){
		produce();
	}
}

void* test2(void* arg){
	for(int i=0;i<100;i++){
		consume();
	}
}

int main(){
	init();
	pthread_t p1,p2,p3,p4;
	pthread_create(&p1,NULL,test1,NULL);
	pthread_create(&p2,NULL,test2,NULL);
	pthread_create(&p3,NULL,test1,NULL);
	pthread_create(&p4,NULL,test2,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	cout<<"main end"<<endl;
	return 0;
}
