#include<iostream>
#include<pthread.h>

using namespace std;
int lock = 0;
int a = 0;
void initLock(){
	lock = 0;
}
void t_lock(){
	while(lock==1){
		cout<<"thread "<<pthread_self()<<" is waiting"<<endl;
		if(sched_yield()==-1){
			cout<<"sched_yiled failed"<<endl;
		}
	}
	lock++;
}
void t_unlock(){
	lock--;
}
void add(){
	a++;
	cout<<"thread "<<pthread_self()<<" is operating,a="<<a<<endl;
}
void* test1(void* arg){
	for(int i=0;i<10;i++){
		t_lock();
		add();
		t_unlock();
	}
}
int main(){
	pthread_t p1;
	pthread_t p2;
	pthread_create(&p1,NULL,test1,NULL);	
	pthread_create(&p2,NULL,test1,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	return 0;
}
