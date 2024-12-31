#include <stdio.h>
#include <stdlib.h>

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

    // In ket qua cac phep duyet cay
    printf("Duyet theo thu tu truoc (pre-order): ");
    preOrder(root);
    printf("\n");

    printf("Duyet theo thu tu giua (in-order): ");
    inOrder(root);
    printf("\n");

    printf("Duyet theo thu tu sau (post-order): ");
    postOrder(root);
    printf("\n");

    return 0;
}

