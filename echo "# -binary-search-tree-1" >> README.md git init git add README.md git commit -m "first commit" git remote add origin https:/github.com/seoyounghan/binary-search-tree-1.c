/*
 * Binary Search Tree #1
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
	int key;
	struct node *left;
	struct node *right;
} Node;//노드의 정보를 담을 구조체

int initializeBST(Node** h);//초기화를 담당할 함수

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("[---- - [한서영][2019038038] ---- - ]\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);//널 값이 들어오면 찾지 못했음을 알려줌
			//옳은 값이 있으면 노드의 주소값 프린팅
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);//널 값이 들어오면 찾지 못했음을 알려줌
			else
				printf("\n Cannot find the node [%d]\n", key);//옳은 값이 있으면 노드의 주소값 프린팅
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			printf("\n");
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			printf("\n");
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			printf("\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)//중위 순회
{		
	if (ptr)//ptr이 NULL 값이 아니면 진행
	{
		inorderTraversal(ptr->left);//ptr의 왼쪽 자식 값으로 넘겨줌
		printf("[%d] ",ptr->key);//본인 탐색
		inorderTraversal(ptr->right);//ptr의 오른쪽 자식 값으로 넘겨줌
	}
}

void preorderTraversal(Node* ptr)//전위 순회
{
	if (ptr)//ptr이 NULL 값이 아니면 진행
	{
		printf("[%d] ",ptr->key);//본인 탐색
		preorderTraversal(ptr->left);//ptr의 왼쪽 자식 값으로 넘겨줌
		preorderTraversal(ptr->right);//ptr의 오른쪽 자식 값으로 넘겨줌
	}
}

void postorderTraversal(Node* ptr)//후위 순회
{
	if (ptr)//ptr이 NULL 값이 아니면 진행
	{
		postorderTraversal(ptr->left);//ptr의 왼쪽 자식 값으로 넘겨줌
		postorderTraversal(ptr->right);//ptr의 오른쪽 자식 값으로 넘겨줌
		printf("[%d] ", ptr->key);//본인 탐색
	}
}


int insert(Node* head, int key)//노드 추가
{	
	Node* temp= (Node*)malloc(sizeof(Node));//임시 값 담아줄 노드
	Node*copy = head;//헤드 노드 값을 복사할 노드

	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;//temp노드에  key 값 입력

	if (head->key ==-9999)//헤드노드가 head 인 경우
	{
		if (head->left == NULL)//생성이 안되어있다면
			head->left = temp;//헤드노드로 생성해준다
		else//생성이 되어있다면
			insert(head->left, key);//다음 노드로 넘어가준다
		return 1;
	}

	if (copy->key <= key)//오른쪽 삽입
	{
		if (copy->right != NULL)//오른쪽 노드가 비어있지 않으면
		{
			copy = copy->right;
			insert(copy, key);//오른쪽 자손 노드로 넘겨준다
		}
		else//오른쪽 노드가 비어있는 경우
		{
			head->right = temp;
			return 1;//temp를 이어준다
		}
	}
	else//왼쪽 삽입
	{
		if (copy->left != NULL)//왼쪽 노드가 있는 경우
		{
			copy = copy->left;
			insert(copy, key);//왼쪽 자손으로 넘겨준다
		}
		else//왼쪽 노드가 없다면
		{
			head->left = temp;
			return 1;//왼쪽 자손 부분에 temp삽입
		}
	}

}

int deleteLeafNode(Node* head, int key)//리프 노드 삭제
{
	Node *copy = head->left;//트리 값 복사
	Node *precopy = head;//복사된 것의 부모노드
	Node* del;//넘긴 값 임시 저장

	while (copy->key != key)//리프노드 까지 값 넘겨주기
	{//키값이 같을때까지 반복
		precopy = copy;//precopy값에 copy 값 대입

		if (copy->key < key)//키값이 더 큰경우
		{
			copy = copy->right;//노드를 오른쪽으로 넘겨줌
		}
		else//반대의 경우
		{
			copy = copy->left;//노드를 왼쪽으로 넘겨줌
		}
	}
	del = copy;

	if (copy->left == NULL && copy->right == NULL)
	{//만약 자손이 없는 경우
		if (precopy->left)//노드가 왼쪽에 존재하는 경우
		{
			if (copy->key == precopy->left->key)
			{
				precopy->left = NULL;
				return 1;
			}//리프 노드를 삭제, 부모노드의 왼쪽 포인팅을 끊음
		}
		precopy->right = NULL;
		return 1;//오른족 노드 삭제
	}
	if (del->key == key)
	{
		printf("리프노드의 값이 아닙니다.\n");
		return 0;
	}//트리에 있는 값이지만 리프노드 값이 아닌 경우
	else
	{
		printf("노드에 없는 값\n");
	}//트리에 없는 값인 경우
}

Node* searchRecursive(Node* ptr, int key)//순환 탐색
{
	if (!ptr)//만약 ptr이 존재하지 않으면 NULL 값 반환
		return NULL;
	if (key == ptr->key)//만약 키값이 같으면
		return ptr;//ptr 반환
	if (key < ptr->key)//키값이 더 작은 경우
	{
		return searchRecursive(ptr->left, key);//왼쪽 노드부터 탐색하게 함
	}
	else//키값이 같거나 더 큰 경우
	{
		return searchRecursive(ptr->right, key);//오른쪽 노드부터 탐색하게 함
	}
}

Node* searchIterative(Node* head, int key)//비순환 탐색
{
	Node* copy = (Node*)malloc(sizeof(Node));
	copy = head->left;//헤드노드 복사할 임시 노드

	while (copy != NULL)//copy가 NULL이 아닐 때까지
	{
		if (key == copy->key)
		{
			return copy;
		}//만약 키값이 같으면 copy의 주소 반환
		if (key < copy->key)
			copy = copy->left;//만약 키값이 작다면 오른쪽 값으로 넘겨줌
		else
			copy = copy->right;//키값이 크다면 왼쪽 값으로 넘겨줌
	}
	return NULL;//위에서 키값이 같은 경우에 속하지 않는다면 NULL값 리턴
}


int freeBST(Node* head)//트리 해제
{
	while (1) {//무한반복
		if (head == NULL) {
			break;
		}//헤드값이 빈 경우
		else if (head->left != NULL) {
			freeBST(head->left);
			head->left = NULL;
		}//헤드 다음 값이 있는경우 왼쪽으로 넘겨줌
		else if (head->right != NULL) {
			if (head->right == head)
				break;
			freeBST(head->right);
			head->right = NULL;
		}//헤드 다음 오른쪽 값이 있는 경우 오른쪽으로 넘겨줌
		else {
			free(head);
			return 1;
		}//경우가 없다면 헤드노드 해제
	}
}




