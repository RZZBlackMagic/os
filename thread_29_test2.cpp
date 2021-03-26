#include<iostream>
#include<pthread.h>

using namespace std;

int a =0;

struct Node{
	int n_num;
	int val;
	pthread_mutex_t mutex;
	Node* next;
};

struct List{
	Node* head;
};

void init(List* list){
	list->head=NULL;
}
void list_create(List* list){
	Node* n;
	if(list->head==NULL){
		Node* node = (Node*)malloc(sizeof(Node));
	        node->n_num=a;
	        node->val= a;
	        a++;
	        node->next = NULL;
		list->head=node;
		n=list->head;	
	}else{
		n = list->head;
		while(n->next!=NULL){
			n=n->next;	
		}
	}
	for(int i=0;i<10;i++){
	        Node* node = (Node*)malloc(sizeof(Node));
       		node->n_num=a;
        	node->val= a;
        	a++;
        	node->next = NULL;
		n->next=node;
		n = n->next;
	}
}

void list_update(List* list,int num){
	if(list->head==NULL){
		cout<<"list is NULL"<<endl;
	}
	Node* node = list->head;
	for(int i=0;i<num;i++){
		node=node->next;
		if(node==NULL){
			cout<<"sorry,list is too short"<<endl;
			return;
		}
	}
	pthread_mutex_lock(&node->mutex);
	for(int i=0;i<10;i++){
		node->val++;
	cout<<"thread "<<pthread_self()<<" is operating,node:"<<node->n_num<<" val:"<<node->val<<endl;
	}
        pthread_mutex_unlock(&node->mutex);	
}

void list_print(List* list){
	if(list->head==NULL){
		cout<<"list is NULL"<<endl;
	}else
	{
		Node* node = list->head;
		while(node!=NULL){
			cout<<"node:"<<node->n_num<<" val:"<<node->val<<endl;
			node=node->next;
		}
	}
}
void* test(void* arg){
	List* list = (List*)arg;
	list_update(list,3);
}
int main(){
	List* list;
        init(list);
	list_create(list);
	list_print(list);
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_create(&p1,NULL,test,(void*)list);
	pthread_create(&p2,NULL,test,(void*)list);
	pthread_create(&p3,NULL,test,(void*)list);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	cout<<"........."<<endl;
	list_print(list);
	return 0;
}
