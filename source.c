#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 10000
#define INT_MAX 100000
#define TRUE 1
#define MAX_VERTICES 100

typedef struct GraphType {// 그래프를 나타내는 구조체
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];// 2차원 인접행렬
} GraphType;

typedef struct GraphStruct {// 그래프를 나타내는 구조체
    int num_vertices; // 정점의 개수
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];// 2차원 인접행렬
} GraphStruct;

#pragma warning(disable:4996)

void dijkstra(int graph[100][100], int start, int vertices);
void printPath(int start, int end, int* predecessor, int* distance);
void insert_vertex(GraphType* g);
void insert_edge(GraphType* g, int start, int end);
int countGraph();
int countGraph1();
void addVertex(GraphStruct* graph);
void addEdge(GraphStruct* graph, int start, int end);
void breadthFirstSearch(GraphStruct* graph, int start, int visitedB[MAX_VERTICES]);

void initializeGraph(GraphStruct* graph) { // 그래프를 초기화하는 함수
    int row, col;
    graph->num_vertices = 0;// 정점의 개수를 초기화
    for (row = 0; row < MAX_VERTICES; row++) // 인접 행렬의 모든 요소 0으로 초기화

        for (col = 0; col < MAX_VERTICES; col++)
            graph->adj_matrix[row][col] = 0;
}

// 그래프에 정점을 추가하는 함수
// 매개변수로는 그래프 구조체의 포인터를 받음
void addVertex(GraphStruct* graph) {

    if (((graph->num_vertices) + 1) > MAX_VERTICES) {// 정점의 개수가 최대 정점 개수(MAX_VERTICES)를 초과하면 오류 메시지 출력 후 함수 종료
        fprintf(stderr, "Graph: Exceeded the number of vertices");
        return;
    }

    graph->num_vertices++; // 정점 개수를 1 증가시킴
}
// 그래프에 간선을 추가하는 함수
// 매개변수로는 그래프 구조체의 포인터, 시작 정점 번호, 끝 정점 번호를 받음
void addEdge(GraphStruct* graph, int start, int end) {

    // 시작 정점 번호나 끝 정점 번호가 정점 개수를 초과하면 오류 메시지 출력 후 함수 종료
    if (start >= graph->num_vertices || end >= graph->num_vertices) {
        fprintf(stderr, "Graph: Vertex number error");
        return;
    }

    // 시작 정점에서 끝 정점으로 가는 간선을 1로 설정
    graph->adj_matrix[start][end] = 1;
}

// 그래프에 대해 너비 우선 탐색을 수행하는 함수
void breadthFirstSearch(GraphStruct* graph, int start,int visitedB[MAX_VERTICES]) {
    int queue[MAX_VERTICES] = { 0, }; // BFS를 위한 큐 초기화
    int front = -1, rear = -1;

    visitedB[start] = TRUE;// 시작 정점을 방문으로 표시

    printf("%d ", start+1);// 방문한 정점 출력

    queue[++rear] = start;// 큐에 시작 정점을 삽입

    while (front != rear) { // 큐가 비어있지 않은 동안 반복

        int vertex = queue[++front]; // 큐에서 정점을 하나 꺼냄
        for (int neighbor = 0; neighbor < graph->num_vertices; neighbor++) { // 인접 정점 탐색
            if (graph->adj_matrix[vertex][neighbor] && !visitedB[neighbor]) { // 정점이 인접하고 방문하지 않았으면
                visitedB[neighbor] = TRUE; // 정점을 방문으로 표시
                printf("- %d ", neighbor+1); // 방문한 정점 출력
                queue[++rear] = neighbor; // 큐에 정점을 삽입
            }
        }

    }

    printf("\n");
}

void init(GraphType* g) { // 그래프 초기화 함수
    int r, c; // 반복문 사용을 위한 변수
    g->n = 0; // 정점의 개수를 0으로 초기화
    for (r = 0; r < MAX_VERTICES; r++) // 인접 행렬의 모든 요소 0으로 초기화
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g) { //
    if (((g->n) + 1) > MAX_VERTICES) { // 정점의 개수가 최대 정점 개수(MAX_VERTICES)를 초과하면 오류 메시지 출력 후 함수 종료
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++; // 정점의 개수를 1 증가
}

void insert_edge(GraphType* g, int start, int end) { // 간선 삽입 연산

    if (start >= g->n || end >= g->n) { // 정점 번호가 정점의 개수보다 크면 오류 메시지 출력 후 함수 종료
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }

    g->adj_mat[start][end] = 1; // 시작 정점에서 끝 정점으로 가는 간선을 1로 설정

}

void dfs_mat(GraphType* g, int v, int visitedD[MAX_VERTICES]) { // 깊이 우선 탐색 함수
    int w;
    visitedD[v] = TRUE; // 정점 v의 방문 표시
    printf("%d ", v+1); // 방문한 정점 출력
    for (w = 0; w < 100; w++) {// 인접 정점 탐색
        if (g->adj_mat[v][w] && !visitedD[w]) {  // 정점이 인접하고 방문하지 않았으면
            printf("- ");
            dfs_mat(g, w,visitedD); // 정점을 방문
        }
    }
}

int printpath(int start, int current, int* predecessor) { // 경로 출력 함수

    if (current != start) { // 시작 정점이 아니면
        int cur = predecessor[current]; // 현재 정점의 선행 정점을 구함
        printpath(start, cur, predecessor); // 선행 정점으로 재귀 호출
        printf(" - %d", current + 1); // 정점 출력
    }

    return 0;
}

int search() { //dfs, bfs 수행 함수
    FILE* fp = fopen("input1.txt", "r"); // 파일 오픈
    if (fp == NULL) { // 파일 오픈 실패시
        printf("파일이 존재하지 않습니다.\n"); // 오류 메시지 출력
        return -1;
    }
    int count = countGraph1(); // 그래프 개수를 구함

    for (int j = 0; j < count; j++) { // 그래프 개수만큼 반복

        int visitedD[MAX_VERTICES] = { 0, }; // 깊이 우선 탐색을 위한 배열 초기화
        GraphType* g; // 그래프 구조체 포인터 선언
        g = (GraphType*)malloc(sizeof(GraphType)); // 그래프 구조체 동적 할당
        init(g); // 그래프 초기화

        int visitedB[MAX_VERTICES] = { 0, }; // 너비 우선 탐색을 위한 배열 초기화
        GraphStruct* myGraph; // 그래프 구조체 포인터 선언
        myGraph = (GraphStruct*)malloc(sizeof(GraphStruct)); // 그래프 구조체 동적 할당
        initializeGraph(myGraph); // 그래프 초기화

        int num_vertices; // 정점의 개수를 저장할 변수
        char strTemp[255]; // 파일에서 문자열을 읽어올 변수
        fgets(strTemp, sizeof(strTemp), fp); // 파일에서 문자열을 읽어옴
        sscanf(strTemp, "%d", &num_vertices); // 정점의 개수를 읽어옴

        for (int i = 0; i < num_vertices; i++) { // 정점의 개수만큼 반복
            addVertex(myGraph); // 그래프에 정점을 추가
            insert_vertex(g); // 그래프에 정점을 추가
        }
        int start, end; // 시작 정점, 끝 정점을 저장할 변수
        char* pStr = NULL; // 문자열을 자르기 위한 포인터
        for (int i = 0; i < num_vertices; i++) { // 정점의 개수만큼 반복

            fgets(strTemp, 255, fp); // 파일에서 문자열을 읽어옴
            pStr = (char*)malloc(256); // 문자열을 자르기 위한 포인터 동적 할당
            strcpy(pStr, strTemp); // 문자열을 자르기 위한 포인터에 문자열 복사
            sscanf(pStr, "%d", &start); // 시작 정점을 읽어옴
            pStr += 2; //

            while (sscanf(pStr, "%d", &end) == 1) { // 끝 정점을 읽어옴
                insert_edge(g, start - 1, end - 1); // 그래프에 간선을 추가
                addEdge(myGraph, start - 1, end - 1); // 그래프에 간선을 추가
                int count = 0; //끝 정점의 자릿수를 저장할 변수

                while (end / 10 != 0) { // 끝 정점의 자릿수를 구함
                    count++; // 자릿수 증가
                    end /= 10; // 끝 정점을 10으로 나눔
                }

                pStr += (count + 2);// 문자열을 자르기 위한 포인터 이동
            }
        }
        printf("그래프 [%d]\n", j+1);
        printf("---------------------------\n");
        printf("깊이 우선 탐색\n");

        dfs_mat(g, 0, visitedD); // 깊이 우선 탐색 수행
        printf("\n");

        printf("너비 우선 탐색\n");
        breadthFirstSearch(myGraph, 0, visitedB); // 너비 우선 탐색 수행
        printf("===========================\n\n\n");
        free(myGraph); // 그래프 구조체 동적 할당 해제
        free(g);
    }
}

int countGraph() { // 그래프 개수를 구하는 함수
    FILE* fp = fopen("input2.txt", "r"); // 파일 오픈
    if (fp != NULL) { // 파일 오픈 성공시
        int count = 0; // 그래프 개수를 저장할 변수
        int firstNumber; // 파일에서 읽어온 첫 번째 정수를 저장할 변수

        while (fscanf(fp, "%d", &firstNumber) == 1) { // 파일에서 정수를 읽어옴
            if (firstNumber == 1) { // 읽어온 정수가 1이면
                count++; // 그래프 개수 증가
            }

            while (fgetc(fp) != '\n') { // 파일에서 개행 문자를 읽어옴
                if (feof(fp)) { // 파일의 끝이면
                    break;
                }
            }
        }

        fclose(fp);
        return count;
    }
    else { // 파일 오픈 실패시
        printf("파일이 존재하지 않습니다.\n");
        return -1;
    }

}

int countGraph1() {
    FILE* fp = fopen("input1.txt", "r");
    if (fp != NULL) {
        int count = 0;
        int firstNumber;

        while (fscanf(fp, "%d", &firstNumber) == 1) {
            if (firstNumber == 1) {
                count++;
            }

            while (fgetc(fp) != '\n') {
                if (feof(fp)) {
                    break;
                }
            }
        }
        fclose(fp);
        return count;
    }
    else {
        printf("파일이 존재하지 않습니다.\n");
        return -1; // 파일 오픈 실패시
    }
}

int** adjacencyMatrix(int countgraph) { // 인접 행렬을 구하는 함수
    int graphNo = 1; // 그래프 번호를 저장할 변수
    int a; // 정점의 개수를 저장할 변수
    int data[100][100]; // 인접 행렬을 저장할 2차원 배열
    FILE* fp; // 파일 포인터 선언
    fp = fopen("input2.txt", "r"); // 파일 오픈

    if (fp != NULL) {// 파일 오픈 성공시
        for (int i = 0; i < countgraph; i++) { // 그래프 개수만큼 반복
            char strTemp[255]; // 파일에서 문자열을 읽어올 변수
            fgets(strTemp, sizeof(strTemp), fp); // 파일에서 문자열을 읽어옴

            if (sscanf(strTemp, "%d", &a) != 1) {  // 정점의 개수를 읽어옴
                break;
            }

            for (int i = 0; i < 100; i++) { // 인접 행렬을 0으로 초기화
                for (int j = 0; j < 100; j++) {
                    if (i == j) {
                        data[i][j] = 0;
                    }
                    else {
                        data[i][j] = MAX; // 인접 행렬을 무한대로 초기화
                    }
                }
            }

            int index; // 시작 정점을 저장할 변수
            int index1; // 끝 정점을 저장할 변수
            int weight; // 가중치를 저장할 변수
            char* pStr = NULL; // 문자열을 자르기 위한 포인터

            for (int k = 0; k < a; k++) { // 정점의 개수만큼 반복

                fgets(strTemp, 255, fp); // 파일에서 문자열을 읽어옴
                pStr = (char*)malloc(256); // 문자열을 자르기 위한 포인터 동적 할당
                strcpy(pStr, strTemp); // 문자열을 자르기 위한 포인터에 문자열 복사
                sscanf(pStr, "%d", &index); // 시작 정점을 읽어옴
                pStr += 2; // 문자열을 자르기 위한 포인터 이동

                while (sscanf(pStr, "%d %d", &index1, &weight) == 2) { // 끝 정점과 가중치를 읽어옴
                    if (index - 1 >= 0 && index1 - 1 >= 0) { // 시작 정점과 끝 정점이 0보다 크거나 같으면
                        data[index - 1][index1 - 1] = weight; // 인접 행렬에 가중치 저장
                    }

                    int count = 0; //가중치의 자리수를 저장할 변수

                    while (weight / 10 != 0) { // 가중치의 자리수를 구함
                        count++; // 자릿수 증가
                        weight /= 10; // 가중치를 10으로 나눔
                    }

                    pStr += (count + 4); // 문자열을 자르기 위한 포인터 이동
                }
            }

            printf("그래프 [%d]\n", graphNo);
            printf("---------------------------\n");
            graphNo++; // 그래프 번호 증가
            dijkstra(data, 1, a);
            printf("===========================\n\n\n");
        }
    }

    else { // 파일 오픈 실패시
        printf("파일이 존재하지 않습니다.");
        return NULL;
    }
    fclose(fp);

}

void printPath(int start, int end, int* predecessor, int* distance) { // 경로 출력 함수
    if (end == start) { // 시작 정점이면
        printf("시작점: %d\n", start + 1); // 시작점 출력
    }
    else if (predecessor[end] == -1) { // 선행 정점이 없으면
        printf("정점 [%d]: No path from %d to %d\n", end + 1, start + 1, end + 1); // 경로가 없음을 출력
    }
    else {
        printf("정점 [%d]: %d", end + 1, start + 1); // 정점 출력

        int current = predecessor[end]; // 현재 정점을 선행 정점으로 설정

        printpath(start, current, predecessor); // 경로 출력

        printf(" - %d, 길이: %d\n", end + 1, distance[end]); // 끝 정점과 길이 출력
    }
}

void dijkstra(int graph[100][100], int start, int vertices) { // 다익스트라 알고리즘 함수
    int* distance = (int*)malloc(vertices * sizeof(int)); // 시작 정점에서 각 정점까지의 거리를 저장할 배열
    int* visited = (int*)malloc(vertices * sizeof(int)); // 방문 여부를 저장할 배열
    int* predecessor = (int*)malloc(vertices * sizeof(int)); // 선행 정점을 저장할 배열


    for (int i = 0; i < vertices; i++) { // 배열 초기화
        distance[i] = INT_MAX; // 거리를 무한대로 초기화
        visited[i] = 0; // 방문 여부를 0으로 초기화
        predecessor[i] = -1;// 선행 정점을 -1로 초기화
    }

    distance[start - 1] = 0;// 시작 정점의 거리를 0으로 설정


    for (int count = 0; count < vertices - 1; count++) { // 정점의 개수 - 1만큼 반복
        int u = -1; // 방문하지 않은 정점 중에서 가장 거리가 짧은 정점을 저장할 변수

        for (int v = 0; v < vertices; v++) { // 방문하지 않은 정점 중에서 가장 거리가 짧은 정점을 구함
            if (!visited[v] && (u == -1 || distance[v] < distance[u]))
                // 방문하지 않았고, u가 -1이거나, v의 거리가 u의 거리보다 작으면 u에 v를 저장
                u = v;
        }

        visited[u] = 1; // 정점 u를 방문으로 표시
        for (int v = 0; v < vertices; v++) { // 정점 u에 인접한 정점들에 대해
            // 방문하지 않았고, 정점 u와 정점 v가 인접하고, 정점 u의 거리가 무한대가 아니고,
            // 정점 u의 거리와 정점 v의 거리의 합이 정점 v의 거리보다 작으면
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v]; // 정점 v의 거리를 정점 u의 거리와 정점 u와 정점 v의 거리의 합으로 설정
                predecessor[v] = u;// 정점 v의 선행 정점을 정점 u로 설정
            }
        }
    }

    for (int i = 0; i < vertices; i++) { // 모든 정점에 대해
        printPath(start - 1, i, predecessor, distance); // 경로 출력
        printf("\n");
    }

    free(distance);
    free(visited);
    free(predecessor);
}

int main() { // 메인 함수
    printf("1. 그래프 탐방 수행 결과\n\n"); // 그래프 탐방 수행 결과 출력
    int lineCount = countGraph(); // 그래프 개수를 구함
    search(); // dfs, bfs 수행, 결과 출력
    printf("2. 최단 경로 구하기 수행 결과\n\n"); // 최단 경로 구하기 수행 결과 출력
    printf("\n");
    adjacencyMatrix(lineCount);// 인접 행렬을 구함, 다익스트라 실행, 결과 출력
}
