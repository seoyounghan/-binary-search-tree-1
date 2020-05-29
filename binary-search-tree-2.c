/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;//노드의 데이터 저장
	struct node *left;//노드의 왼족 자식 저장
	struct node *right;//노드의 오른쪽 자식 저장
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];//스택 저장
int top = -1;//스택의 top 저장

Node* pop();//스택 에서 빼기
void push(Node* aNode);//스택에 넣기

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];//큐 저장 공간
int front = -1;//큐의 front
int rear = -1;//큐의 rear

Node* deQueue();//큐에서 데이터 빼기
void enQueue(Node* aNode);//큐에 데이터 저장


int initializeBST(Node** h);//초기화

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */





int main()
{
	char command;//사용자에게 메뉴 입력 받음
	int key;//key 값 입력 받음
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("-------------2019038038   한서영--------------------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {//이중 포인터 사용
	//트리 초기화 함수 
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	//헤드노드 생성 루트 노드 생성
	top = -1;

	front = rear = -1;
	//스택과 큐 값도 초기화 해준다
	return 1;
}



void recursiveInorder(Node* ptr)//순환 중위 순회
{
	if (ptr) {//ptr이 존재 한다면
		recursiveInorder(ptr->left);//왼쪽 자식 노드 탐색
		printf(" [%d] ", ptr->key);//노드의 값 출력
		recursiveInorder(ptr->right);//오른쪽 자식 노드 탐색
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)//반복 중위 순회
{
	int top = -1;//top값 초기화

	for (;;)//무한 루프
	{
		for (; node; node = node->left)//노드의 값이 존재할 때까지, 노드를 왼쪽 자식으로 넘겨줌
			push(node);//스택에 node값 넣기
		node = pop();//스택에서 top의 값을 뺀후 node에 대입
		if (!node)//노드가 존재하지 않으면 반복 루프 탈출
			break;
		printf("[%d] ", node->key);//스택에서 뺀 값 출력
		node = node->right;//오른쪽 자식으로 넘어감
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)//레벨 순회
{
	front = rear = 0;//값 초기화

	if (!ptr)
		return;//ptr이 없다면 함수를 탈출해줌
	enQueue(ptr);//ptr의 값 큐에 넣음
	for (;;)//무한 루프
	{
		ptr = deQueue();//큐에서 뺀 값 ptr에 대입
		if (ptr != NULL)//ptr이 존재한다면
		{
			printf("[%d] ", ptr->key);//노드 값 출력
			if (ptr->left)//왼쪽 자식이 존재하면
				enQueue(ptr->left);//왼쪽 자식을 큐에 넣어줌
			if (ptr->right)//오른쪽 자식이 존재하면
				enQueue(ptr->right);//오른쪽 자식을 큐에 넣음
		}
		else
			break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;//임시로 삽입할 노드 생성

	if (head->left == NULL) {
		head->left = newNode;
		return 1;//헤드노드가 없다면 만들어줌
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)//노드 삭제
{
	Node *temp = head->left;
	Node*prenode = temp;
	Node *del;//임시 노드 생성

	while (temp->key != key)//키 값이 같아 질 때 까지 찾음
	{
		prenode = temp;//temp의 부모노드
		if (temp->key < key)
			temp = temp->right;
		else
			temp = temp->left;
	}
	del = temp;//임시로 temp값 할당
	if (temp->key != key)
	{
		printf("키 값이 없음\n");
		return 0;
	}

	if (temp->left == NULL && temp->right == NULL)//리프 노드 삭제
	{
		if (prenode->left)//왼쪽에 존재하는 경우
		{
			if (temp->key == prenode->left->key)
			{
				prenode->left = NULL;
				return 1;//노드 삭제
			}
		}
		prenode->right = NULL;//오른쪽에 존재하는 경우 노드 삭제
		return 1;
	}
	else if (temp->left != NULL && temp->right != NULL)//왼쪽 오른쪽 자손 존재
	{
		temp = temp->left;//temp를 왼쪽 으로 
		if (temp->right == NULL)//오른쪽 자손이 없으면
		{
			del->key = temp->key;
			del->left = temp->left;
			return 1;//삭제하고 왼쪽 자손을 이어줌
		}
		while (1)//무한 루프
		{
			if (temp->right == NULL)//오른쪽 자손이 없으면
			{
				del->key = temp->key;
				prenode->right = temp->left;
				return 1;//노드 삭제 후 왼쪽 자손을 이어줌
			}
			else
			{
				prenode = temp;
				temp = temp->right;
			}//아닌 경우 오른쪽으로 이동
		}
	}
	else {//한쪽만 자손 존재
		if (temp->right != NULL)//오른쪽 자손이 존재한다면
		{
			if (prenode->left->key == key)//노드의 위치 왼쪽
			{
				prenode->left = temp->right;
			}
			else//노드의 위치 오른쪽
			{
				prenode->right = temp->right;
			}
			return 1;
		}
		if (temp->left != NULL)//왼쪽 자손 존재
		{
			if (prenode->left->key == key)//노드의 위치 왼쪽
			{
				prenode->left = temp->left;
			}
			else {//노드의 위치 오른쪽
				prenode->right = temp->left;
			}
			return 1;
		}

	}

}


void freeNode(Node* ptr)//노드 할당 해제
{
	if (ptr) {//ptr이 존재한다면
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);//안에 속한 변수들 할당 해제
	}
}

int freeBST(Node* head)//트리 해제
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}//만약 헤드노드만 존재하면 헤드노드만 해제

	Node* p = head->left;//해드노드가 포인팅 하는 곳 해제

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()//스택에 데이터 저장
{
	Node* temp;
	if (top == -1)
	{

		return NULL;
	}//아무것도 없는 경우
	else
	{
		temp = stack[top];
		stack[top] = NULL;
		top = top - 1;
		return temp;
	}//데이터가 있는 경우 top에서 데이터 삭제후 top를 내려준다
}

void push(Node* aNode)//스택에 데이터 저장
{
	if (stack[MAX_STACK_SIZE] == NULL) {
		top = top + 1;
		stack[top] = aNode;
	}//스택에 데이터 추가
	else
	{
		printf("스택 초과\n");
	}//스택이 맥스를 넘긴 경우
}



Node* deQueue()//큐에서 데이터 삭제
{
	Node*temp = (Node*)malloc(sizeof(Node));
	front = (front + 1) % (MAX_QUEUE_SIZE);
	temp = queue[front];
	queue[front] = NULL;
	//front값 늘려준 후 전의 값은 NULL로 바꿔줌
	return temp;//front큐 값 반환
}

void enQueue(Node* aNode)//큐 추가
{
	rear = (rear + 1) % (MAX_QUEUE_SIZE);
	queue[rear] = aNode;

}//큐의 rear에 노드를 추가해준 후 rear는 증가시킴


