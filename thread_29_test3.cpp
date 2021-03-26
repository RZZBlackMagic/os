#include<iostream>
#include<pthread.h>
#include<queue>
using namespace std;
int a = 1;
struct Node{
	int node_num;
	int val;
	Node* next;
};

struct Queue{
	Node node;
	Node* queue_head;
	Node* queue_tail;
	pthread_mutex_t mutex;
};

Node* create_node();
Queue* create_queue(){
	Node* node = create_node();
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->node = *node;
	q->queue_head=node;
	q->queue_tail = q->queue_head ;
	return q;
}
Node* create_node(){
	Node* node = (Node*)malloc(sizeof(Node));
	if(node!=NULL){
		node->node_num=a;
		node->val=a;
		node->next=NULL;
		a++;	
	}else{
		cout<<"create Node failed"<<endl;
		exit(0);
	}
	return node;
}

void in_queue(Queue* queue){
	pthread_mutex_lock(&queue->mutex);
	if(queue==NULL){
		cout<<"please init queue"<<endl;
		return ;
	}
	Node* node = create_node();
//	if(node==NULL){
//		cout<<"node create failed"<<endl;
//		return ;
//	}
//	cout<<node->val<<endl;
	queue->queue_tail->next=node;
	queue->queue_tail=queue->queue_tail->next;
	node=NULL;
//	cout<<queue->queue_head->val<<endl;
	pthread_mutex_unlock(&queue->mutex);
}

void de_queue(Queue* queue){
	if(queue->queue_head==queue->queue_tail){
		cout<<"queue is clear"<<endl;
		return ;
	}
	pthread_mutex_lock(&queue->mutex);
	Node* node=queue->queue_head;
	queue->queue_head = queue->queue_head->next;
	cout<<"node is de_queue ,node_num:"<<node->node_num<<"node_val:"<<node->val<<endl;
	free(node);
	pthread_mutex_unlock(&queue->mutex);
}
void* in_test(void* arg){
	cout<<1<<endl;
	Queue* queue = (Queue*)arg;
	for(int i=0;i<10;i++){
		in_queue(queue);
	}
	cout<<2<<endl;
}
void* de_test(void* arg){
	Queue* queue = (Queue*)arg;
	for(int i=0;i<10;i++){
		de_queue(queue);
	}
}
void print_queue(Queue* queue){
	pthread_mutex_lock(&queue->mutex);
	Node* node = queue->queue_head;
	while(node!=queue->queue_tail){
		cout<<"node_num:"<<node->node_num<<" node_val:"<<node->val<<endl;
		node=node->next;
	}
	node=NULL;
	pthread_mutex_unlock(&queue->mutex);
}
void free_queue(Queue* queue){
	int i = 0;
	Node* node = NULL;
	while(queue->queue_head!=queue->queue_tail){
		node = queue->queue_head;
		queue->queue_head=queue->queue_head->next;
//		cout<<node->val<<endl;
		free(node);
		i++;
		node = NULL;
	}
}
int main(){
	Queue* queue = create_queue();
//	cout<<1<<endl;
	pthread_t p1,p2,p3;
	pthread_create(&p1,NULL,in_test,(void*)queue);
	pthread_create(&p2,NULL,in_test,(void*)queue);
	pthread_create(&p3,NULL,in_test,(void*)queue);
//	pthread_join(p1,NULL);
//	pthread_join(p2,NULL);
//	pthread_join(p3,NULL);
//	int a =1;
//	Node* node = queue->queue_head;
//	while(node!=queue->queue_tail){
//		a++;
//		node=node->next;
//	}
	print_queue(queue);
	pthread_t p4,p5,p6;
	pthread_create(&p4,NULL,de_test,(void*)queue);
	pthread_create(&p5,NULL,de_test,(void*)queue);
	pthread_create(&p6,NULL,de_test,(void*)queue);
	pthread_join(p4,NULL);
	pthread_join(p5,NULL);
	pthread_join(p6,NULL);
	pthread_join(p1,NULL);
        pthread_join(p2,NULL);
        pthread_join(p3,NULL);

//	free_queue(queue);
	queue=NULL;
	return 0;
}
