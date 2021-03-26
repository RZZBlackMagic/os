#include<iostream>
#include<pthread.h>
#include<mutex>
using namespace std;

int a = 0;

struct Node {
	int p_id;
	int p_num;
	struct Node * next;
};

struct List {
	struct Node *head;
	pthread_mutex_t mutex;
};

void lock();
void unlock();
void init(List* list);
List* create_link(List* list);
void print_link1(List* list);

void lock(){
}

void unlock(){
}

void init(List* list){
//	pthread_mutex_init(&(list->mutex),NULL);
	list->head = NULL;
}

List* create_link(List* list){
//	cout<<pthread_self()<<endl;
	pthread_mutex_lock(&list->mutex);
	Node* n;
	if(list->head==NULL){
		Node* node = (Node*)malloc(sizeof(Node));
		if(node==NULL){
			pthread_mutex_unlock(&list->mutex);
			return ;
		}
		node->p_num=a;
		node->p_id=pthread_self();
		node->next=NULL;
		list->head=node;
		n = list->head;
		a++;
	}
	else{
		n=list->head;
		while(n->next!=NULL){
			n = n->next;
		}
	}
	for(int i=0;i<100;i++){
		cout<<pthread_self()<<endl;
		Node* node = (Node*)malloc(sizeof(Node));
		if(node==NULL)
			continue;
	        node->p_num=a;
		node->p_id=pthread_self();
	        node->next=NULL;
	        n->next = node;
		a++;
		n = n->next;
		node = NULL;
	}
	n=NULL;
	pthread_mutex_unlock(&list->mutex);
}

void print_link1(List* list){
//	pthread_mutex_lock(&list->mutex);
	Node* n = list->head;
	while(n!=NULL){
		cout<<"thread "<<n->p_id<<" is creating Node:"<<n->p_num<<endl;
		n = n->next;
	}
//	pthread_mutex_unlock(&list->mutex);
}

void delete_list(List* list){
	Node* node = list->head;
	while(node!=NULL){
		node=node->next;
		free(node);
	}
}

void* test(void* l){
	List* list = (List*)l;
	create_link(list);
}
int main(){
	cout<<1<<endl;
	List* list = (List*)malloc(sizeof(List));
	list->head=NULL;
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_create(&p1,NULL,test,(void*)list);
	pthread_create(&p2,NULL,test,(void*)list);
	pthread_create(&p3,NULL,test,(void*)list);
	pthread_join(p1,NULL);
//	cout<<2<<endl;
	pthread_join(p2,NULL);
//	cout<<3<<endl;
	pthread_join(p3,NULL);
	print_link1(list);
	return 0;
}
