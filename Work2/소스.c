// 전략 1 : 시작하는 점에서 모든 점에 대해 정보전달을 할 때 이전노드와의 친밀도가 높은 순으로 이동
//			즉  친밀도가 높은 순서부터 방문을 하는데 이때는 found는 쓰지 않는다. 값이 다시 바뀔 가능성
//			이 있어서 found가 되는 시점은 다시 시작하는 노드(v 가 될 때)가 될 때 이다. 그리고 시작하는 점에서 앞으로 나아가야해서 돌때 가장 친밀도가 높은 선도
//			체크해서 시작점에서 더 이상 나아갈 수 없다면 친밀도가 높은 선의 시작점과 연결된 점
//			에 대해 다시 시작한다. 아쉬운 점은 min_heap을 써서 구현을 하고 코드 실행시간에 대해 
//			트릭을 써서 O(nlogn)의 시간 복잡도를 내지 못하였다. 
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

///거리 방문여부 이전노드 친밀도///
double distance[MAX_VERTICES];
int found[MAX_VERTICES];
int pre_node[MAX_VERTICES];
int closedness[MAX_VERTICES];

// 이전노드와 연결대상만 하길 원함
// 이전 노드의 closedness값을 초기화 시키고 들어가야함
int choose(int vertex, graph*g) { // vertex값으로 이전 노드가 들어가야함
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
 // 책을 기반으로 작성한 다익스트라 알고리즘 //
void short_path(graph* g, int start_index) {
	int i, v, w;
	// 모든 점 초기화
	for (i = 0; i < g->numberOfVertices; i++) {
		distance[i] = -INF; // distance값을 10000으로
		closedness[i] = g->graph_matrix[start_index][i]; // 친밀도는 행렬을 통해
		if (g->graph_matrix[start_index][i] > INF) { // 값이 바뀐 경우
			distance[i] = 0; // 시작점과 연결된 선의 거리를 0
			pre_node[i] = start_index; // 시작 점 그리고 시작 점과 연결된 점의 이전 점은 시작점
		}
		else
			pre_node[i] = -1; // 시작점과 연결되지 않은 점들은 이전 점을 -1
		found[i] = 0; // 모든 점은 찾지 못한 상태
	}
	found[start_index] = 1;
	int k = start_index;

	int max_Cindex = start_index;
	int max_C = INF;

	for (i = 0; i < g->numberOfVertices; i++) {
		v = choose(k, g); // number와 그래프를 변경/////////////////////////////////////////////////***
		//printf("\ni의 값 : %d\n", i); //##오류체크##
		if (v == -1) { // 시작점과 인접한 노드들이 다 방문한경우
			//printf("맥스 c인덱스 : %d\n", max_Cindex); // ##오류체크##
			v = choose(max_Cindex,g);
			max_C = INF;
		}
		if (v == -1) break;
		found[v] = 1;
		//printf("v(%d)의 방문 여부 : %d\n", v, found[v]); //##오류체크##
		k = pre_node[v];
		for (w = 0; w < g->numberOfVertices; w++) {
			if (g->graph_matrix[v][w] == INF || distance[w] == 0) // w가 시작점, 시작점과 인접한 점, v와 인접하지않은경우
				continue;
			else if(found[w] == 0){ // 방문한점이 아닐경우
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
// 합계와 출력함수
double printfunction(int start_node, int number) {
	char start = 'A' + start_node;
	char adjacency_node = 'A';
	double sum = 0;
	printf("시작점이 %c인 경우 :\n", start);
	for (int i = 0; i < number; i++) {
		sum += distance[i];
		if (distance[i] > 0.0){
			printf("   %c 까지의 최소 거리 :  %f\n", adjacency_node + i, distance[i]);
		}
			
	}
	return sum;
}


int main(void) {
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
	printf("최종걸린시간 : %f\n", result);
	stop = clock();
	duration = (double)(stop - start) / CLOCKS_PER_SEC;
	printf("이 전략의 수행시간은 %f초 입니다.\n", duration);
	return 0;
}