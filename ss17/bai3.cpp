#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Cau truc mot nut trong cay nhi phan
typedef struct Node {
    int data;             // Gia tri cua nut
    struct Node* left;    // Con tro den nut con trai
    struct Node* right;   // Con tro den nut con phai
} Node;

// Ham tao mot nut moi
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Cap phat bo nho cho nut moi
    newNode->data = value; // Gan gia tri
    newNode->left = NULL;  // Con tro trai ban dau la NULL
    newNode->right = NULL; // Con tro phai ban dau la NULL
    return newNode;
}

// Ham chen gia tri vao cay nhi phan tim kiem
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value); // Tao nut moi neu cay rong
    }
    if (value < root->data) {
        root->left = insert(root->left, value); // Chen vao nhanh trai neu gia tri nho hon nut hien tai
    } else {
        root->right = insert(root->right, value); // Chen vao nhanh phai neu gia tri lon hon nut hien tai
    }
    return root;
}

// Duyet cay theo thu tu truoc (pre-order): goc -> trai -> phai
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data); // In gia tri nut goc
        preOrder(root->left);     // Duyet nhanh trai
        preOrder(root->right);    // Duyet nhanh phai
    }
}

// Duyet cay theo thu tu giua (in-order): trai -> goc -> phai
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);      // Duyet nhanh trai
        printf("%d ", root->data); // In gia tri nut goc
        inOrder(root->right);     // Duyet nhanh phai
    }
}

// Duyet cay theo thu tu sau (post-order): trai -> phai -> goc
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);   // Duyet nhanh trai
        postOrder(root->right);  // Duyet nhanh phai
        printf("%d ", root->data); // In gia tri nut goc
    }
}

// Ham chuyen cay nhi phan thanh do thi vo huong su dung danh sach ke
void convertTreeToGraph(Node* root, int adjacencyList[][100], int* count) {
    if (root == NULL) return;

    // Tao canh giua nut cha va nut con trai
    if (root->left != NULL) {
        adjacencyList[root->data][root->left->data] = 1; // Tao canh
        adjacencyList[root->left->data][root->data] = 1; // Nguoc lai
        convertTreeToGraph(root->left, adjacencyList, count); // De quy cho nhanh trai
    }

    // Tao canh giua nut cha va nut con phai
    if (root->right != NULL) {
        adjacencyList[root->data][root->right->data] = 1; // Tao canh
        adjacencyList[root->right->data][root->data] = 1; // Nguoc lai
        convertTreeToGraph(root->right, adjacencyList, count); // De quy cho nhanh phai
    }
}

// Duyet do thi su dung BFS
void BFS(int adjacencyList[][100], int visited[], int start, int size) {
    int queue[100], front = 0, rear = 0; // Hang doi
    queue[rear++] = start; // Them dinh bat dau vao hang doi
    visited[start] = 1;    // Danh dau da tham

    while (front < rear) {
        int current = queue[front++]; // Lay dinh tu dau hang doi
        printf("%d ", current);      // In dinh hien tai

        for (int i = 0; i < size; i++) { // Duyet danh sach ke
            if (adjacencyList[current][i] == 1 && !visited[i]) { // Neu co canh va chua tham
                queue[rear++] = i;    // Them dinh vao hang doi
                visited[i] = 1;       // Danh dau da tham
            }
        }
    }
}

// Duyet do thi su dung DFS
void DFS(int adjacencyList[][100], int visited[], int start, int size) {
    printf("%d ", start); // In dinh hien tai
    visited[start] = 1;   // Danh dau da tham

    for (int i = 0; i < size; i++) { // Duyet danh sach ke
        if (adjacencyList[start][i] == 1 && !visited[i]) { // Neu co canh va chua tham
            DFS(adjacencyList, visited, i, size); // De quy goi DFS
        }
    }
}

int main() {
    Node* root = NULL; // Khoi tao cay rong

    int n, value;
    printf("Nhap so luong nut trong cay: ");
    scanf("%d", &n);

    printf("Nhap cac gia tri nut:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value); // Chen gia tri vao cay
    }

    // Duyet cay
    printf("Duyet cay theo pre-order: ");
    preOrder(root);
    printf("\n");

    printf("Duyet cay theo in-order: ");
    inOrder(root);
    printf("\n");

    printf("Duyet cay theo post-order: ");
    postOrder(root);
    printf("\n");

    // Chuyen cay sang do thi
    int adjacencyList[100][100] = {0}; // Ma tran ke
    int count = 0;
    convertTreeToGraph(root, adjacencyList, &count);

    // Duyet do thi su dung BFS
    int visited[100] = {0}; // Khoi tao mang visited
    printf("Duyet do thi theo BFS: ");
    BFS(adjacencyList, visited, 0, 100);
    printf("\n");

    // Duyet do thi su dung DFS
    for (int i = 0; i < 100; i++) visited[i] = 0; // Reset mang visited
    printf("Duyet do thi theo DFS: ");
    DFS(adjacencyList, visited, 0, 100);
    printf("\n");

    return 0;
}

