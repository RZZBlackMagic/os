#include<iostream>
#include<pthread.h>

using namespace std;

int done = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;
void thr_exit(){
	//pthread_mutex_lock(&mutex);
	done=1;
	pthread_cond_signal(&cond);
//	pthread_mutex_unlock(&mutex);
}
void* test(void* arg){
	pthread_mutex_lock(&mutex);
	cout<<"child"<<endl;
	thr_exit();
	pthread_mutex_unlock(&mutex);
}

void thr_join(){
	pthread_mutex_lock(&mutex);
	while(done==0)
		pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
}

int main(){
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	cout<<"parent start"<<endl;
	pthread_t p;
	pthread_create(&p,NULL,test,NULL);
	thr_join();
	cout<<"parent end"<<endl;
	return 0;
}
