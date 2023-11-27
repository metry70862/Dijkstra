#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 100000

#pragma warning(disable:4996)
void dijkstra(int graph[100][100], int start, int vertices);
void printPath(int start, int end, int* predecessor, int* distance);

int** allocateIntMemory(int m, int n) {
    int** A;
    A = (int**)malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++) {
        A[i] = (int*)malloc(sizeof(int) * n);
    }
    return A;
}



void releseMemory(int** A, int m) {
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
}

int printpath(int start, int current, int* predecessor) {

    if (current != start) {
        int cur = predecessor[current];
        printpath(start, cur, predecessor);
        printf(" - %d", current + 1);
    }

    return 0;
}


int countGraph() {
    FILE* fp = fopen("input2.txt", "r");
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
        return -1; //파일 오픈 실패시
    }

}

int** adjacencyMatrix(int countgraph) {
    int graphNo = 1;
    int a;
    int data[100][100];
    FILE* fp;
    fp = fopen("input2.txt", "r");

    if (fp != NULL) {


        for (int i = 0; i < countgraph; i++) {
            char strTemp[255];

            fgets(strTemp, sizeof(strTemp), fp);



            if (sscanf(strTemp, "%d", &a) != 1) {
                break;
            }

            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 100; j++) {
                    if (i == j) {
                        data[i][j] = 0;
                    }
                    else {
                        data[i][j] = MAX;
                    }
                }
            }

            int index;
            int index1;
            int weight;
            int count = 1;
            char* pStr = NULL;
            for (int k = 0; k < a; k++) {

                fgets(strTemp, 255, fp);
                pStr = (char*)malloc(256);
                strcpy(pStr, strTemp);
                sscanf(pStr, "%d", &index);
                pStr += 2;

                while (sscanf(pStr, "%d %d", &index1, &weight) == 2) {
                    if (index - 1 >= 0 && index1 - 1 >= 0) {
                        data[index - 1][index1 - 1] = weight;
                    }

                    int count = 0;

                    while (weight / 10 != 0) {
                        count++;
                        weight /= 10;
                    }

                    pStr += (count + 4);
                }
            }

            printf("그래프 [%d]\n", graphNo);
            printf("---------------------------\n");
            graphNo++;
            dijkstra(data, 1, a);
            printf("===========================\n\n\n");
        }
    }

    else {
        printf("파일이 존재하지 않습니다.");
        return NULL;
    }
    fclose(fp);

}


void printPath(int start, int end, int* predecessor, int* distance) {
    if (end == start) {
        printf("시작점: %d\n", start + 1);
    }
    else if (predecessor[end] == -1) {
        printf("정점 [%d]: No path from %d to %d\n", end + 1, start + 1, end + 1);
    }
    else {
        printf("정점 [%d]: %d", end + 1, start + 1);

        int current = predecessor[end];

        printpath(start, current, predecessor);

        printf(" - %d, 길이: %d\n", end + 1, distance[end]);
    }
}

void dijkstra(int graph[100][100], int start, int vertices) {
    int* distance = (int*)malloc(vertices * sizeof(int));
    int* visited = (int*)malloc(vertices * sizeof(int));
    int* predecessor = (int*)malloc(vertices * sizeof(int));


    for (int i = 0; i < vertices; i++) {
        distance[i] = MAX;
        visited[i] = 0;
        predecessor[i] = -1;
    }

    distance[start - 1] = 0;


    for (int count = 0; count < vertices - 1; count++) {
        int u = -1;


        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && (u == -1 || distance[v] < distance[u]))
                u = v;
        }

        visited[u] = 1;
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                predecessor[v] = u;
            }
        }
    }

    for (int i = 0; i < vertices; i++) {
        printPath(start - 1, i, predecessor, distance);
        printf("\n");
    }

    free(distance);
    free(visited);
    free(predecessor);
}




int main() {
    printf("2. 최단 경로 구하기 수행 결과\n\n");
    int lineCount = countGraph();
    adjacencyMatrix(lineCount);
    /* Dijkstra */
}
