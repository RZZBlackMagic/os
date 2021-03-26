#include<iostream>
#include<pthread.h>
#include<queue>
#include<linux/futex.h>

using namespace std;
int s = 0;
int a = 1;
struct thread{
	int * flag;
	pthread_t* pt;
	int * temp;
}Thread;

queue<Thread*> q;


void lock(void*arg){
	Thread* t = (Thread*)arg;
	*(t->flag)++;
	if(*(t->flag)>=0){
		//add in queue
		futex_wait(t->flag,1);
		q.push(t);
		cout<<"thread "<<pthread_self()<<" add in queue"<<endl;
		return;
	}
}

void unlock(void* arg){
	Thread* t = (Thread*)arg;
	*(t->flag)--;
	
}

void add(void* arg){
	lock(void* arg);
	*(arg->temp)++;
	unlock(void* arg);
}
void* test(void * arg){
	add(void* arg);
	Thread* t = (Thread*)arg;
	if(t->flag==1){
		//add in queue
		q.push(t);
		futex_wait(t->flag,1);
		cout<<"thread "<<pthread_self()<<" add in queue"<<endl;
		return;
	}
	cout<<"thread "<<pthread_self()<<" is operating"<<endl;
	return;
}
int main(){
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	Thread *t1 = (Thread*)malloc(sizeof(Thread));;
        t1->flag = &a;
	t1->temp = &s
        t1->pt = &p1;
	Thread* t2 = (Thread*)malloc(sizeof(Thread));
	t2->flag = &a;
	t2->temp = &s;
	t2->pt = &p2
	Thread t3 = (Thread*)malloc(sizeof(Thread));
	t3->flag = &a;
	t3->temp = &s;
	t3->pt = &p3;
	Thread* t4 = (Thread*)malloc(sizeof(Thread));
	t4->flag = &a;
	t4->temp = &s;
	t4->pt = &p4
	pthread_create(&p1,NULL,test,(void*)t1);
	pthread_create(&p2,NULL,test,(void*)t2);
	pthread_create(&p3,NULL,test,(void*)t3);
	pthread_create(&p4,NULL,test,(void*)t4);
	return 0;
}
