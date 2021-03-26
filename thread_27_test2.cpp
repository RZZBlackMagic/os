#include<iostream>
#include<pthread.h>
#include<thread>
#include<unistd.h>
using namespace std;

int a = 0;
pthread_mutex_t mutex;
void add(){
	pthread_mutex_lock(&mutex);
	a++;
	cout<<"this is thread "<<std::this_thread::get_id()<<",a="<<a<<endl;
	pthread_mutex_unlock(&mutex);
}
void* mutex_test1(void* arg){
	cout<<"thread 1 strat"<<endl;
	for(int i=0;i<10;i++)
	{
		add();
		cout<<"this is thread1 a="<<a<<endl;
	}
	cout<<"thread 1 over"<<endl;
}
void* mutex_test2(void* arg){
	cout<<"thread2 start"<<endl;
	for(int i=0;i<10;i++){
		add();
		cout<<"this is thread2 a="<<a<<endl;
	}
	cout<<"thread2 over"<<endl;
}
int main(){
	cout<<"main start"<<endl;
	pthread_mutex_init(&mutex,NULL);
	pthread_t p;
	pthread_t p2;
	pthread_create(&p,NULL,mutex_test1,NULL);
	pthread_create(&p2,NULL,mutex_test2,NULL);
	pthread_detach(p);
	pthread_detach(p2);
	sleep(5);
	cout<<"main over"<<endl;
	return 0;
}
