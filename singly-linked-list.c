/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	
	printf("[----- [Yongho Bae] [2020039008] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //�߰��� node �޸� �Ҵ�
	node->key = key; //�߰��� node�� key�� ����

	node->link = h->first; 
	h->first = node; 
	// node�� ù��°�� �߰�

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //�߰��� node �޸� �Ҵ�
	listNode* search = h->first; //���� ��ġ �˻��� ���� ��������� ���� �� ó����带 ����Ű�� �ʱ�ȭ
	node -> key = key; //�߰��� node�� key�� ����
	node -> link = NULL; //node�� link �ʱ�ȭ

	if(h->first == NULL){
			h->first = node;
			return 0;
	} //����ִ� ����Ʈ�� �ٷ� node ���� �� �Լ�����

	while(search != NULL){
			if(h->first->key > key){
				node->link = h->first;
				h->first = node;
				break; 
			} //�߰��� key���� ���� �۾Ƽ� ù��° ��� �տ� node�� �����ؾ��ϴ� ���
			else if(search->link == NULL){
				search->link = node;
				break;
			} //�߰��� key���� ���� Ŀ�� ������ ��� �ڿ� node�� �����ؾ��ϴ� ���
			else if(search->link->key > key){
				node->link = search->link;
				search->link = node;
				break;
			} //�߰��� node�� �����ؾ��ϴ� ���

			search = search->link; //���� ��� �˻��� ����
	}

	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //�߰��� node �޸� �Ҵ�
	listNode* search = h->first; //���� ��ġ �˻��� ���� ��������� ���� �� ó����带 ����Ű�� �ʱ�ȭ
	node->key = key; //�߰��� node�� key�� ����
	node->link = NULL; //node�� link �ʱ�ȭ

	if(h->first == NULL){
		h->first = node;
		return 0;
	} //����ִ� ����Ʈ�� �ٷ� node ���� �� �Լ�����

	while(search->link != NULL){	
		search = search->link;
	} //������ ��� �˻�
	search->link = node; //������ ��� ���Ŀ� node ����
	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; //ù��° ����� ������ ���� �� �޸��Ҵ���ü�� ���� ��������ͼ��� �� �ʱ�ȭ

	if(h->first==NULL){
		printf("����ִ� ����Ʈ�Դϴ�\n");
		return 0;
	} // ����ִ� ����Ʈ�� �Լ�����

	h->first = h->first->link; //����忡�� �ι�° ���� ���� 
	free(temp); //ù��°���� ��� �޸��Ҵ�����

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* search= h->first; //�ش� key�� �������ִ� ��带 ã�� ���� ��������ͼ��� �� �ʱ�ȭ
	listNode* temp= h->first; //������ ���� �� �޸��Ҵ���ü�� ���� ��������ͼ��� �� �ʱ�ȭ

	if(h->first==NULL){
			printf("����ִ� ����Ʈ�Դϴ�\n");
			return 0;
	} //����ִ� ����Ʈ�� �Լ�����

	while(search != NULL){
		if(h->first->key == key){
			h->first = h->first->link;
			free(temp);
			break;
		} //ù��° ����� key�� ���� ��� ����忡�� �ι�° ���� ���� �� �޸��Ҵ�����
		else if(search->link == NULL){
			printf("������ key: %d�� �����ϴ�.\n",key);
			break;
		} //����Ʈ �ȿ� ������ key�� ���� ��� 
		else if(search->link->key == key){
			temp = search->link;
			search->link = search->link->link;
			free(temp);
			break;
		} //�� ���Ŀ� key���� ���� ��尡 ���� ��� 
		
		search = search->link; // ���� ��� �˻��� ���ؼ�
	}

	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* prev = NULL; //��������� ���� �� �������� ��� ��ũ�� NULL ������ ���� ��Ʈ������ 
	listNode* search = h->first; //������ ��� �˻��� ���� ��Ʈ������ ���� �� �ʱ�ȭ
	
	if(h->first == NULL){
		printf("����ִ� ����Ʈ�Դϴ�\n");
		return 0;
	} //����ִ� ����Ʈ�� ��� �Լ�����
	
	if(h->first->link == NULL){
		free(h->first);
		h->first = NULL;
		return 0;
	} //ù��° ��尡 ������ ����� ���(=��尡 �ϳ��� ���), �ش� ��� �޸��Ҵ�����

	while(search->link != NULL){
		prev = search;
		search = search->link;
	} //������ ��� Ž��(search->���������, prev->����������� ���� ���)
	
	prev->link = NULL; //���������� ��������� ��������
	free(search); //��������� �޸��Ҵ� ����

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
    listNode* prev = NULL; //���� ���������
    listNode* curr = h->first; //���� ������ ������ ���������
    listNode* next = NULL; //���� ���������

    if (h->first == NULL) {
        printf("����ִ� ����Ʈ�Դϴ�\n");
        return 0;
    }//����ִ� ����Ʈ�� �Լ�����

    while (curr != NULL) {
        next = curr->link; //curr ���� ��带 next�� ����Ŵ
        curr->link = prev; 
		//ó������ ���翡�� �������� ���� ����� ������ ���� �������ʹ� ���� ��带 ���� ���� ��������
        prev = curr; //���� ��尡 ���� ��尡 �ǰ�
        curr = next; //���� ��尡 ���� ��尡 ��.
    } //����Ʈ�� ������ �ݺ��۾�

    h->first = prev; //prev�� �����ִ� ��������带 �����尡 ����Ű����.

    return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

