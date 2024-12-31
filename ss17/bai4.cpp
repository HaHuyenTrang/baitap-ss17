#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cau truc nut cua cay nhi phan
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Ham tao nut moi
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Ham chen gia tri vao cay nhi phan
Node* insert(Node *root, int value) {
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    return root;
}

// Ham tao cay nhi phan voi n nut
Node* createBinaryTree(int n) {
    Node *root = NULL;
    for (int i = 1; i <= n; i++) {
        root = insert(root, i); // Gia tri tang dan
    }
    return root;
}

// Duyet cay theo thu tu truoc (pre-order)
void preOrder(Node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

// Duyet cay theo thu tu giua (in-order)
void inOrder(Node *root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

// Duyet cay theo thu tu sau (post-order)
void postOrder(Node *root) {
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}

// Ham them canh vao do thi
void addEdge(int matrix[][100], int u, int v) {
    matrix[u][v] = 1;
    matrix[v][u] = 1;
}

// Ham tao do thi voi n dinh va danh sach canh
void createGraph(int n, int edges[][2], int edgeCount, int matrix[][100]) {
    for (int i = 0; i < edgeCount; i++) {
        addEdge(matrix, edges[i][0], edges[i][1]);
    }
}

// Ham DFS cho do thi
void DFS(int start, int visited[], int matrix[][100], int n) {
    printf("%d ", start);
    visited[start] = 1;
    for (int i = 0; i < n; i++) {
        if (matrix[start][i] && !visited[i]) {
            DFS(i, visited, matrix, n);
        }
    }
}

// Ham BFS cho do thi
void BFS(int start, int visited[], int matrix[][100], int n) {
    int queue[100], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);
        for (int i = 0; i < n; i++) {
            if (matrix[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

// Ham do thoi gian thuc thi
double measureTime(void (*func)(void)) {
    clock_t start = clock();
    func();
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    int n = 10; // So nut cua cay va do thi
    int matrix[100][100] = {0}; // Ma tran ke cho do thi

    // Tao cay nhi phan
    Node *tree = createBinaryTree(n);

    // Tao danh sach canh cho do thi
    int edges[][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {5, 9}};
    int edgeCount = sizeof(edges) / sizeof(edges[0]);
    createGraph(n, edges, edgeCount, matrix);

    // Duyet cay nhi phan
    printf("Duyet cay nhi phan (Pre-order): ");
    preOrder(tree);
    printf("\nDuyet cay nhi phan (In-order): ");
    inOrder(tree);
    printf("\nDuyet cay nhi phan (Post-order): ");
    postOrder(tree);
    printf("\n");

    // Duyet do thi
    int visited[100] = {0};
    printf("Duyet do thi (DFS): ");
    DFS(0, visited, matrix, n);
    printf("\n");
    for (int i = 0; i < n; i++) visited[i] = 0; // Khoi tao lai mang visited

    printf("Duyet do thi (BFS): ");
    BFS(0, visited, matrix, n);
    printf("\n");

    return 0;
}

