#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 4 // Dinh nghia so dinh trong do thi

// Ham them canh vao ma tran ke
void addEdge(int matrix[V][V], int i, int j) {
    matrix[i][j] = 1; // Them canh tu dinh i den dinh j
    matrix[j][i] = 1; // Them canh tu dinh j den dinh i (do thi vo huong)
}

// Ham in ma tran ke ra man hinh
void printMatrix(int matrix[V][V]) {
    for (int i = 0; i < V; i++) { // Lap qua cac dong
        for (int j = 0; j < V; j++) { // Lap qua cac cot
            printf("%d\t", matrix[i][j]); // In gia tri tai vi tri [i][j]
        }
        printf("\n"); // Xuong dong sau khi in het 1 dong
    }
}

// Ham DFS de duyet do thi
void DFS(int matrix[V][V], int visited[V], int v) {
    printf("%d ", v); // In dinh hien tai
    visited[v] = 1;   // Danh dau dinh da duoc tham

    // Duyet tat ca cac dinh ke voi dinh hien tai
    for (int i = 0; i < V; i++) {
        if (matrix[v][i] == 1 && !visited[i]) { // Neu co canh va dinh chua duoc tham
            DFS(matrix, visited, i);           // De quy goi DFS cho dinh i
        }
    }
}

// Ham BFS de duyet do thi
void BFS(int matrix[V][V], int visited[V], int start) {
    int queue[V]; // Hang doi de luu cac dinh se tham
    int front = 0, rear = 0; // Chi so dau va cuoi hang doi

    queue[rear++] = start; // Them dinh bat dau vao hang doi
    visited[start] = 1;    // Danh dau dinh da duoc tham

    while (front < rear) { // Lap khi hang doi khong rong
        int v = queue[front++]; // Lay dinh dau tien trong hang doi
        printf("%d ", v);       // In dinh dang duoc tham

        // Duyet tat ca cac dinh ke voi dinh hien tai
        for (int i = 0; i < V; i++) {
            if (matrix[v][i] == 1 && !visited[i]) { // Neu co canh va dinh chua duoc tham
                queue[rear++] = i;                 // Them dinh vao hang doi
                visited[i] = 1;                    // Danh dau dinh da duoc tham
            }
        }
    }
}

int main() {
    int matrix[V][V] = {0}; // Khoi tao ma tran ke ban dau voi tat ca gia tri bang 0
    int visited[V];         // Mang danh dau cac dinh da duoc tham

    // Them cac canh vao do thi
    addEdge(matrix, 0, 1);
    addEdge(matrix, 0, 2);
    addEdge(matrix, 1, 2);
    addEdge(matrix, 2, 3);

    // In ma tran ke
    printf("Ma tran ke cua do thi:\n");
    printMatrix(matrix);

    // Duyet do thi bang DFS
    printf("\nDFS tu dinh 0: ");
    for (int i = 0; i < V; i++) visited[i] = 0; // Khoi tao mang visited
    DFS(matrix, visited, 0);

    // Duyet do thi bang BFS
    printf("\nBFS tu dinh 0: ");
    for (int i = 0; i < V; i++) visited[i] = 0; // Khoi tao lai mang visited
    BFS(matrix, visited, 0);

    return 0;
}

