#include<iostream>
#include<pthread.h>
using namespace std;

struct my_sem{
	int value;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

void mysem_wait(my_sem* sem){
	pthread_mutex_lock(&sem->mutex);
	sem->value--;
	while(sem->value<0){
		pthread_cond_wait(&sem->cond);
	}
	pthread_mutex_unlock(&sem->mutex);
}

void mysem_post(my_sem* sem){
	pthread_mutex_lock(&sem->mutex);
	pthread_cond_signal(&sem->cond);
	sem->value++;
	pthread_mutex_unlock(&sem->mutex);
}

