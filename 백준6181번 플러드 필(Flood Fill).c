#include <stdio.h>
#include <stdlib.h>

#define element int
#define max(a, b) ((a > b) ? a : b)

typedef struct point {

	int x;
	int y;
	
}Point;

typedef struct vertex { // ��������

	int destination; // ��������
	struct vertex *adjacencyVertex; // ���� ����

}Vertex;

typedef struct list { // �׷����� �� ����

	Point V;
	Vertex *head;
	int visited;

}List;

typedef struct graph { // �׷��� ����ü 

	int V; // ������ ��
	List *list; // �ε����� �� ������ ��Ÿ����

}Graph;

typedef struct stackNode { // ���ó��

	element data;
	struct stackNode *link;

}StackNode;

typedef struct stackType { // ����Ÿ�� ADT

	int size;
	StackNode *top;

}StackType;

Graph *newGraph();
List *newList(Graph *graph, List *list, int max);
Vertex *newAdjacencyVertex(int destination);
void addEdge(Graph *graph, int u, int v);

StackType *newStack();
StackNode *newStackNode();
void initStack(StackType **s);
int isEmptyStack(StackType *s);
void push(StackType *s, element data);
element pop(StackType *s);
element peek(StackType *s);

int main() {

	Graph *graph = newGraph();
	StackType *stack = newStack();
	int D = 0; // ����ư�Ÿ��� ũ��
	int i = 0, j = 0;
	int graphCount = 0;
	int graphMaxSize = 0;
	int graphSize = 0;
	int vertex;
	Vertex *temp = NULL;
	Point point;
	
	scanf("%d %d", &(graph->V), &D); // �׷����� ���������� ����ư�Ÿ��� �Է¹���
	graph->list = newList(graph, graph->list, graph->V); // ������ ��ŭ ����Ʈ ũ�� �Ҵ�
	for (i = 0; i <= graph->V; i++) { // ����Ʈ ù���� ������ ��� �ʱ�ȭ
		graph->list[i].head = NULL;
	}

	for (i = 0; i < graph->V; i++) { // �� ������ ��ġ�Է�
		scanf("%d %d", &(point.x), &(point.y));
		graph->list[i].V.x = point.x;
		graph->list[i].V.y = point.y;
	}

	for (i = 0; i < graph->V; i++) { // ����ư �Ÿ��� ���Ͽ� D���ϸ� ��������
		for (j = i + 1; j < graph->V; j++) {
			if (abs(graph->list[i].V.x - graph->list[j].V.x) + abs(graph->list[i].V.y - graph->list[j].V.y) <= D) {
				addEdge(graph, i, j);
				addEdge(graph, j, i);
			}
		}
	}

	/*
	for (i = 0; i < graph->V; i++) { // ��������Ʈ ���� ���
		printf("%d %d: ", graph->list[i].V.x, graph->list[i].V.y);
		temp = graph->list[i].head;
		while (temp != NULL) {
			printf("%d %d   ", graph->list[temp->destination].V.x , graph->list[temp->destination].V.y);
			temp = temp->adjacencyVertex;
		}
		printf("\n");
	}
	*/

	for (i = 0; i < graph->V; i++) { // DFS������� Ž���Ͽ� �׷����� ũ�� �� ���� Ȯ��

		vertex = i; // ���� Ž�������� ��ġ�� i�� ����
		push(stack, i); // i�� ���ÿ� Ǫ��

		if (graph->list[vertex].visited != 1) { // ������ġ�� �湮�� ������ �ƴ϶��
			graph->list[vertex].visited = 1; // �湮ǥ��
			graphSize++; // �׷��� ũ�� 1����

			while (!isEmptyStack(stack)) { // ������ ��������� ���� �ݺ�

				if (graph->list[vertex].visited == 1)
					pop(stack);

				temp = graph->list[vertex].head;

				while (temp != NULL) {
					if (graph->list[temp->destination].visited != 1) {
						push(stack, temp->destination);
						graph->list[temp->destination].visited = 1;
						graphSize++;
					}
					temp = temp->adjacencyVertex;
				}

				vertex = peek(stack); // ���� ��ġ�� ������ top�̴�
			}
		}
		else {
			pop(stack);
		}

		if (graphSize != 0)
			graphCount++;
		graphMaxSize = max(graphMaxSize, graphSize);
		graphSize = 0;
	}

	printf("%d %d\n", graphCount, graphMaxSize);
}

Graph *newGraph() {
	return (Graph *)calloc(1, sizeof(Graph));
}

List *newList(Graph *graph, List *list, int max) {
	int i = 0;

	list = (List *)realloc(list, (max + 1) * sizeof(List)); // ���ο� ���� ū ������ ũ�⸸ŭ ���Ҵ� ���ְ�
	for (i = graph->V; i <= max; i++) { // ���� �ִ� ���� ���ĺ��� ���ο� �ִ� �������� �ʱ�ȭ ���ش�
		list[i].head = NULL;
	}
	return list;
}

Vertex *newAdjacencyVertex(int destination) {
	Vertex *vertex = (Vertex *)calloc(1, sizeof(Vertex));
	vertex->destination = destination;

	return vertex;
}

void addEdge(Graph *graph, int u, int v) {

	Vertex *vertex = NULL;
	Vertex *temp = NULL;

	if (graph->V < max(u, v)) { // ���� �׷����� ���������� ū ������ ������ ������ ����
		graph->list = newList(graph, graph->list, max(u, v));
		graph->V = max(u, v);
	}

	vertex = graph->list[u].head;

	if (vertex == NULL) { // u ������ ���� ��尡 �ϳ��� �����ٸ� 
		graph->list[u].head = newAdjacencyVertex(v); // �ٷο���
	}

	else { // ���� ������ �־��ٸ� ���������� ũ������� �־��ش�
		temp = vertex;
		if (vertex->destination > v) { // ó�� ������ ������������ ���� ũ���
			graph->list[u].head = newAdjacencyVertex(v);
			graph->list[u].head->adjacencyVertex = vertex;
		}
		else { // ó�� ������ ���� �������� ū ũ��� ������ ��ġ�� ã�´�
			while (vertex != NULL && vertex->destination < v) {
				temp = vertex;
				vertex = vertex->adjacencyVertex;
			}
			temp->adjacencyVertex = newAdjacencyVertex(v);
			temp->adjacencyVertex->adjacencyVertex = vertex;
		}
	}
}

StackType *newStack() { // ���� ����
	return (StackType *)calloc(1, sizeof(StackType));
}

StackNode *newStackNode() { // ���ó�� ����
	return (StackNode *)calloc(1, sizeof(StackNode));
}

void initStack(StackType **s) { // ���� �ʱ�ȭ
	free(*s);
	*s = NULL;
}

int isEmptyStack(StackType *s) { // ������ ����ִ��� Ȯ��
	return (s->top == NULL);
}

void push(StackType *s, element data) { // ������ data�� push

	StackNode *node = newStackNode();

	if (node == NULL)
		return;

	node->data = data;
	node->link = s->top;
	s->top = node;
	s->size++;
}

element pop(StackType *s) { // ������ data�� pop

	StackNode *tempStackNode = newStackNode();
	element data;

	if (isEmptyStack(s))
		return 0;

	tempStackNode = s->top;
	data = tempStackNode->data;
	s->top = tempStackNode->link;
	free(tempStackNode);
	s->size--;

	return data;
}

element peek(StackType *s) { // ������ data�� peek

	if (isEmptyStack(s))
		return 0;

	return s->top->data;
}