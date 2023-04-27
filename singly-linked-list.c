/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 node 메모리 할당
	node->key = key; //추가할 node의 key값 대입

	node->link = h->first; 
	h->first = node; 
	// node를 첫번째에 추가

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 node 메모리 할당
	listNode* search = h->first; //넣을 위치 검색을 위한 노드포인터 선언 및 처음노드를 가리키게 초기화
	node -> key = key; //추가할 node의 key값 대입
	node -> link = NULL; //node의 link 초기화

	if(h->first == NULL){
			h->first = node;
			return 0;
	} //비어있는 리스트면 바로 node 삽입 후 함수종료

	while(search != NULL){
			if(h->first->key > key){
				node->link = h->first;
				h->first = node;
				break; 
			} //추가할 key값이 가장 작아서 첫번째 노드 앞에 node를 삽입해야하는 경우
			else if(search->link == NULL){
				search->link = node;
				break;
			} //추가할 key값이 가장 커서 마지막 노드 뒤에 node를 삽입해야하는 경우
			else if(search->link->key > key){
				node->link = search->link;
				search->link = node;
				break;
			} //중간에 node를 삽입해야하는 경우

			search = search->link; //다음 노드 검색을 위해
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 node 메모리 할당
	listNode* search = h->first; //넣을 위치 검색을 위한 노드포인터 선언 및 처음노드를 가리키게 초기화
	node->key = key; //추가할 node의 key값 대입
	node->link = NULL; //node의 link 초기화

	if(h->first == NULL){
		h->first = node;
		return 0;
	} //비어있는 리스트면 바로 node 삽입 후 함수종료

	while(search->link != NULL){	
		search = search->link;
	} //마지막 노드 검색
	search->link = node; //마지막 노드 이후에 node 삽입
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; //첫번째 노드의 연결이 끊긴 후 메모리할당해체를 위한 노드포인터선언 및 초기화

	if(h->first==NULL){
		printf("비어있는 리스트입니다\n");
		return 0;
	} // 비어있는 리스트면 함수종료

	h->first = h->first->link; //헤드노드에서 두번째 노드로 연결 
	free(temp); //첫번째였던 노드 메모리할당해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* search= h->first; //해당 key를 가지고있는 노드를 찾기 위한 노드포인터선언 및 초기화
	listNode* temp= h->first; //연결이 끊긴 후 메모리할당해체를 위한 노드포인터선언 및 초기화

	if(h->first==NULL){
			printf("비어있는 리스트입니다\n");
			return 0;
	} //비어있는 리스트면 함수종료

	while(search != NULL){
		if(h->first->key == key){
			h->first = h->first->link;
			free(temp);
			break;
		} //첫번째 노드의 key가 맞을 경우 헤드노드에서 두번째 노드로 연결 후 메모리할당해제
		else if(search->link == NULL){
			printf("삭제할 key: %d가 없습니다.\n",key);
			break;
		} //리스트 안에 삭제할 key가 없는 경우 
		else if(search->link->key == key){
			temp = search->link;
			search->link = search->link->link;
			free(temp);
			break;
		} //그 이후에 key값을 가진 노드가 있을 경우 
		
		search = search->link; // 다음 노드 검색을 위해서
	}

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* prev = NULL; //마지막노드 삭제 후 마지막인 노드 링크에 NULL 대입을 위한 노트포인터 
	listNode* search = h->first; //마지막 노드 검색을 위한 노트포인터 선언 및 초기화
	
	if(h->first == NULL){
		printf("비어있는 리스트입니다\n");
		return 0;
	} //비어있는 리스트일 경우 함수종료
	
	if(h->first->link == NULL){
		free(h->first);
		h->first = NULL;
		return 0;
	} //첫번째 노드가 마지막 노드일 경우(=노드가 하나일 경우), 해당 노드 메모리할당해제

	while(search->link != NULL){
		prev = search;
		search = search->link;
	} //마지막 노드 탐색(search->마지막노드, prev->마지막노드의 이전 노드)
	
	prev->link = NULL; //마지막노드와 이전노드의 연결해제
	free(search); //마지막노드 메모리할당 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* prev = NULL; //이전 노드포인터
    listNode* curr = h->first; //현재 역으로 연결할 노드포인터
    listNode* next = NULL; //다음 노드포인터

    if (h->first == NULL) {
        printf("비어있는 리스트입니다\n");
        return 0;
    }//비어있는 리스트면 함수종료

    while (curr != NULL) {
        next = curr->link; //curr 다음 노드를 next로 가리킴
        curr->link = prev; 
		//처음에는 현재에서 다음으로 가는 노드의 연결을 끊고 다음부터는 현재 노드를 이전 노드로 연결해줌
        prev = curr; //현재 노드가 이전 노드가 되고
        curr = next; //다음 노드가 현재 노드가 됨.
    } //리스트의 끝까지 반복작업

    h->first = prev; //prev에 남아있는 마지막노드를 헤더노드가 가리키게함.

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

