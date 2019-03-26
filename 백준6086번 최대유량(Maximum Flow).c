#include <stdio.h> // ������ ī�� �˰���(Edmonds-Karp algorithm) -> BFS (���� ǮĿ�� �˰��� -> DFS)
#include <stdlib.h>
#include <string.h>

#define element int
//#define min(a, b) ((a < b) ? a : b)
//#define max(a, b) ((a > b) ? a : b) 

typedef struct vertex { // �������� ���Ḯ��Ʈ

	int destination; // ��������
	int capacity; // �뷮
	int flow; // ����
	struct vertex *adjacencyVertex; // ���� ����

}Vertex;

typedef struct list { // �׷����� �� ���� ����Ʈ

	Vertex *head;

}List;

typedef struct graph { // �׷��� ����ü

	int V; // ������ ��
	List *list; // �ε����� �� ������ ��Ÿ����

}Graph;

typedef struct dequeNode { // ��(����)�� Front ��(������)�� rear

	element data;
	struct dequeNode *leftLink;
	struct dequeNode *rightLink;

}DequeNode;

typedef struct dequeType {

	int size;
	DequeNode *front;
	DequeNode *rear;

}DequeType;

int ctoi(char c);
Graph *newGraph();
void newList(Graph *graph, int max);
Vertex *newAdjacencyVertex(int destination, int capacity);
void addEdge(Graph *graph, int u, int v, int capacity);
Vertex *findEdge(Graph *graph, int u, int v);
DequeType *newDeque(); // �� ����
DequeNode *newDequeNode(); // �� ��� ����
int isEmptyDeque(DequeType *deque); // ���� ����ִ��� Ȯ��
void enqueueRear(DequeType *deque, element data); // ���� �ڿ� ����
element dequeueFront(DequeType *deque); // ���� ���� ��� ����
element peekFront(DequeType *deque); // ���� ���� ��� ����

int main() {

	Graph *graph = newGraph(); // ��������Ʈ �׷��� ����
	DequeType *deque = NULL;
	Vertex *vertex = NULL;
	int E = 0; // ������ ����
	int i = 0, capacity = 0, flow = 0; // �뷮�� ����
	char u = 0, v = 0; // u : ��������, v : ��������
	int total = 0; // �� ����
	int S = ctoi('A'), T = ctoi('Z'); //  S : �ҽ�, T : ��ũ
	int *visited = (int *)malloc(sizeof(int) * 52);
	int curr = 0, next = 0; // ���� ������ ���������� Ű��
	int INF = 1000000000;
	
	scanf("%d", &E); // ������ ���� �Է�
	getchar();
	for (i = 0; i < E; i++) {
		scanf("%c %c %d", &u, &v, &capacity);
		getchar();
		addEdge(graph, ctoi(u), ctoi(v), capacity);
		addEdge(graph, ctoi(v), ctoi(u), capacity); // ������ ������ �߰����ش�
	}
	
	while (1) { // ���� ���(augmenting path)�� �� ã�� ������ ����, ���� ��θ� BFS�� ã��

		deque = newDeque();
		enqueueRear(deque, S);
		memset(visited, -1, sizeof(int) * 52); // �湮���� �ʱ�ȭ
	
		while (!isEmptyDeque(deque)) { // BFS�� ��� ã��
			curr = peekFront(deque);
			dequeueFront(deque);
			vertex = graph->list[curr].head;
			while(vertex != NULL) { // curr���� ������ ��� ������ ����
				// vertex->capacity - vertex->flow > 0: u���� v�� ������ �긱 ������ ����
				// visited[next] == -1: next ������ ���� �湮 ���� �ʾҴٸ�
				next = vertex->destination;
				if (vertex->capacity - vertex->flow > 0 && visited[next] == -1) {
					enqueueRear(deque, next);
					visited[next] = curr; // ��θ� ����ϱ� ���� visited �迭 ���
					if (next == T) // ��ũ�� �����ϸ� ���� 
						break; 
				}
				vertex = vertex->adjacencyVertex;
			}
			if (next == T && visited[T] != -1) {// ��ũ�� �����ϸ� ���� 
				while (!isEmptyDeque(deque))
					dequeueFront(deque);
				break;
			}
		}

		// ��ũ�� ���� ��ΰ� �� ������ ���� Ż��
		if (visited[T] == -1) 
			break;

		// ��λ󿡼� ���� ���ġ�� ���� ���� ã��
		flow = INF;
		for (i = T; i != S; i = visited[i]) {
			vertex = graph->list[visited[i]].head;
			while (vertex->destination != i)
				vertex = vertex->adjacencyVertex;
			flow = min(flow, vertex->capacity - vertex->flow);
		}

		// ã�� flow��ŭ �ش� ��ο� ���� �����
		for (i = T; i != S; i = visited[i]) {
			vertex = findEdge(graph, visited[i], i);
			vertex->flow += flow;
			vertex = findEdge(graph, i, visited[i]);
			vertex->flow -= flow;
		}

		// �� ���� �� ����
		total += flow;
		free(deque);
	}

	// ��� ���
	printf("%d\n", total);
}

int ctoi(char c) { // ���ĺ� ���ڸ� 0~51 ������ ������ �ٲ��ִ� �Լ�
	if (c <= 'Z') 
		return c - 'A';
	else
		return c - 'a' + 26;
}

Graph *newGraph() {
	return (Graph *)calloc(1, sizeof(Graph));
}

void newList(Graph *graph, int max) {

	int i = 0;

	if (graph->list == NULL) { // �ʱ� �׷����� ����������ŭ�� ����Ʈ �������Ҵ�
		graph->list = (List *)calloc(max + 1, sizeof(List));
	}

	else {
		graph->list = (List *)realloc(graph->list, (max + 1) * sizeof(List)); // ���ο� ���� ū ������ ũ�⸸ŭ ���Ҵ� ���ְ�
		for (i = graph->V + 1; i <= max; i++) { // ���� �ִ� ���� ���ĺ��� ���ο� �ִ� �������� �ʱ�ȭ ���ش�
			graph->list[i].head = NULL;
		}
	}

	graph->V = max; // �������� ����
}

Vertex *newAdjacencyVertex(int destination, int capacity) {

	Vertex *vertex = (Vertex *)calloc(1, sizeof(Vertex));
	vertex->destination = destination;
	vertex->capacity = capacity;

	return vertex;
}

void addEdge(Graph *graph, int u, int v, int capacity) {

	Vertex *vertex = NULL;
	Vertex *temp = NULL;

	if (graph->V < max(u, v)) { // ���� �׷����� ���������� ū ������ ������ ������ ����
		newList(graph, max(u, v));
	}

	vertex = graph->list[u].head;

	if (vertex == NULL || vertex->destination > v) { // u ������ ���� ��尡 �ϳ��� ���ų� ó�� ������ ������������ ���� ũ���
		graph->list[u].head = newAdjacencyVertex(v, capacity);
		graph->list[u].head->adjacencyVertex = vertex;
	}
	else { // ó�� ������ ���� �������� ũ�ų� ������ ������ ��ġ�� ã�´�
		temp = vertex;
		while (vertex != NULL && vertex->destination < v) {
			temp = vertex;
			vertex = vertex->adjacencyVertex;
		}
		if (temp->destination == v)
			temp->capacity += capacity;
		else {
			temp->adjacencyVertex = newAdjacencyVertex(v, capacity);
			temp->adjacencyVertex->adjacencyVertex = vertex;
		}
	}

}

Vertex *findEdge(Graph *graph, int u, int v) {
	
	Vertex *vertex = graph->list[u].head;

	while (vertex != NULL && vertex->destination != v)
		vertex = vertex->adjacencyVertex;

	return vertex;
}

DequeType *newDeque() { // �� ����
	return (DequeType *)calloc(1, sizeof(DequeType));
}

DequeNode *newDequeNode() { // �� ��� ����
	return (DequeNode *)calloc(1, sizeof(DequeNode));
}

int isEmptyDeque(DequeType *deque) { // ���� ����ִ��� Ȯ��
	return (deque->size == 0); // ����� 0�̸� 1����, �׿ܴ� 0����
}

void enqueueRear(DequeType *deque, element data) { // ���� rear�� data�� �߰��Ѵ�

	DequeNode *node = newDequeNode();

	node->data = data;

	if (isEmptyDeque(deque)) { // ���� ��� �ִٸ�
		deque->front = node;
	}
	else { // ���� ������� �ʴٸ�
		node->leftLink = deque->rear;
		deque->rear->rightLink = node;
	}
	deque->rear = node;
	deque->size++;
}

element dequeueFront(DequeType *deque) { // ���� front�� �ִ� data�� �����ϰ� data�� �����Ѵ�.

	DequeNode *temp = NULL;
	element data = 0;

	if (isEmptyDeque(deque)) // ���� ����ִٸ� �׳� �����Ѵ�
		return 0;

	else if (deque->front == deque->rear) // ���� ��尡 �ϳ� ���̶�� ������ NULL �����ش�.
		deque->rear = NULL;

	temp = deque->front;
	data = temp->data;

	deque->front = temp->rightLink;
	free(temp);
	deque->size--;

	if (!isEmptyDeque(deque)) // ������ ���� ��尡 �ϳ��� �����ִٸ�
		deque->front->leftLink = NULL; // ���� ���� ������ �ʱ�ȭ�����ش�.

	return data;
}

element peekFront(DequeType *deque) { // ���� front�� �ִ� data�� peek�Ѵ�

	if (isEmptyDeque(deque)) // ���� ����ִٸ� �׳� �����Ѵ�
		return 0;

	else
		return deque->front->data;
}