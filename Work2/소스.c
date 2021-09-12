// ���� 1 : �����ϴ� ������ ��� ���� ���� ���������� �� �� ���������� ģ�е��� ���� ������ �̵�
//			��  ģ�е��� ���� �������� �湮�� �ϴµ� �̶��� found�� ���� �ʴ´�. ���� �ٽ� �ٲ� ���ɼ�
//			�� �־ found�� �Ǵ� ������ �ٽ� �����ϴ� ���(v �� �� ��)�� �� �� �̴�. �׸��� �����ϴ� ������ ������ ���ư����ؼ� ���� ���� ģ�е��� ���� ����
//			üũ�ؼ� ���������� �� �̻� ���ư� �� ���ٸ� ģ�е��� ���� ���� �������� ����� ��
//			�� ���� �ٽ� �����Ѵ�. �ƽ��� ���� min_heap�� �Ἥ ������ �ϰ� �ڵ� ����ð��� ���� 
//			Ʈ���� �Ἥ O(nlogn)�� �ð� ���⵵�� ���� ���Ͽ���. 
//
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

#define MAX_VERTICES  30
#define INF -10000


////////graph////////
typedef struct graph {
	int numberOfVertices;
	int graph_matrix[MAX_VERTICES][MAX_VERTICES];
}graph;

///�Ÿ� �湮���� ������� ģ�е�///
double distance[MAX_VERTICES];
int found[MAX_VERTICES];
int pre_node[MAX_VERTICES];
int closedness[MAX_VERTICES];

// �������� ������ �ϱ� ����
// ���� ����� closedness���� �ʱ�ȭ ��Ű�� ������
int choose(int vertex, graph*g) { // vertex������ ���� ��尡 ������
	int max_index = -1;
	int max_closedness = 0;
	for (int i = 0; i < g->numberOfVertices; i++) {
		if (!found[i] && closedness[i] > max_closedness && g->graph_matrix[vertex][i] != INF) {
			max_closedness = closedness[i];
			max_index = i;
		}
	}
	return max_index;
}
 // å�� ������� �ۼ��� ���ͽ�Ʈ�� �˰����� //
void short_path(graph* g, int start_index) {
	int i, v, w;
	// ��� �� �ʱ�ȭ
	for (i = 0; i < g->numberOfVertices; i++) {
		distance[i] = -INF; // distance���� 10000����
		closedness[i] = g->graph_matrix[start_index][i]; // ģ�е��� ����� ����
		if (g->graph_matrix[start_index][i] > INF) { // ���� �ٲ� ���
			distance[i] = 0; // �������� ����� ���� �Ÿ��� 0
			pre_node[i] = start_index; // ���� �� �׸��� ���� ���� ����� ���� ���� ���� ������
		}
		else
			pre_node[i] = -1; // �������� ������� ���� ������ ���� ���� -1
		found[i] = 0; // ��� ���� ã�� ���� ����
	}
	found[start_index] = 1;
	int k = start_index;

	int max_Cindex = start_index;
	int max_C = INF;

	for (i = 0; i < g->numberOfVertices; i++) {
		v = choose(k, g); // number�� �׷����� ����/////////////////////////////////////////////////***
		//printf("\ni�� �� : %d\n", i); //##����üũ##
		if (v == -1) { // �������� ������ ������ �� �湮�Ѱ��
			//printf("�ƽ� c�ε��� : %d\n", max_Cindex); // ##����üũ##
			v = choose(max_Cindex,g);
			max_C = INF;
		}
		if (v == -1) break;
		found[v] = 1;
		//printf("v(%d)�� �湮 ���� : %d\n", v, found[v]); //##����üũ##
		k = pre_node[v];
		for (w = 0; w < g->numberOfVertices; w++) {
			if (g->graph_matrix[v][w] == INF || distance[w] == 0) // w�� ������, �������� ������ ��, v�� ���������������
				continue;
			else if(found[w] == 0){ // �湮������ �ƴҰ��
				if (closedness[w] < g->graph_matrix[v][w]) {
					closedness[w] = g->graph_matrix[v][w];
					//printf("closedness[w(%d)] = %d\n", w, closedness[w]);
				}
				if (closedness[w] > max_C) {
					max_C = closedness[w];
					max_Cindex = v;
				}
				
				
				if (distance[w] > 1 / (double)g->graph_matrix[k][v] + distance[v]) {
					distance[w] = 1 / (double)g->graph_matrix[k][v] + distance[v];
					pre_node[w] = v;
					//printf("pre_node[w(%d)] = %d\n", w, pre_node[w]);
				}
			}
		}
	}
}
// �հ�� ����Լ�
double printfunction(int start_node, int number) {
	char start = 'A' + start_node;
	char adjacency_node = 'A';
	double sum = 0;
	printf("�������� %c�� ��� :\n", start);
	for (int i = 0; i < number; i++) {
		sum += distance[i];
		if (distance[i] > 0.0){
			printf("   %c ������ �ּ� �Ÿ� :  %f\n", adjacency_node + i, distance[i]);
		}
			
	}
	return sum;
}


int main(void) {
	printf("시작");
	clock_t start, stop;
	double duration;
	start = clock();
	graph g = { 11,{{0,19,3,11,13,INF,INF,INF,INF,INF,INF}
				  , {19,0,4,5,INF,INF,INF,INF,INF,INF,INF}
				  , {3,4,0,8,21,INF,INF,INF,INF,INF,INF}
				  , {11,5,8,0,INF,7,5,INF,14,INF,15}
				  , {13,INF,21,INF,0,24,INF,INF,INF,6,INF}
				  , {INF,INF,INF,7,24,0,17,8,3,INF,INF}
				  , {INF,INF,INF,5,INF,17,0,INF,15,INF,12}
				  , {INF,INF,INF,INF,INF,8,INF,0,11,7,INF}
				  , {INF,INF,INF,14,INF,3,15,11,0,INF,INF}
				  , {INF,INF,INF,INF,6,INF,INF,7,INF,0,INF}
				  , {INF,INF,INF,15,INF,INF,12,INF,INF,INF,0}}
	};

	double result = 0;
	for (int i = 0; i < g.numberOfVertices; i++) {
		short_path(&g, i);
		result += printfunction(i, g.numberOfVertices);
		printf("\n\n\n");
	}
	printf("�����ɸ��ð� : %f\n", result);
	stop = clock();
	duration = (double)(stop - start) / CLOCKS_PER_SEC;
	printf("�� ������ ����ð��� %f�� �Դϴ�.\n", duration);
	return 0;
}
