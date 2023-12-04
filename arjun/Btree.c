#include <stdio.h>
#include <stdlib.h>

#define T 2

// Structure for a B-tree node
struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode* children[2 * T];
    int num_keys;
    int leaf; // Flag to indicate whether the node is a leaf
};

// Function to create a new B-tree node
struct BTreeNode* createNode() {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->num_keys = 0;
    newNode->leaf = 1;
    for (int i = 0; i < 2 * T; ++i) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to search a key in a B-tree
struct BTreeNode* search(struct BTreeNode* root, int key) {
    int i = 0;
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }
    if (i < root->num_keys && key == root->keys[i]) {
        return root; // Key found in this node
    } else if (root->leaf) {
        return NULL; // Key not found, and this node is a leaf
    } else {
        return search(root->children[i], key); // Recur to the appropriate child
    }
}

// Function to split a child node of the B-tree
void splitChild(struct BTreeNode* parent, int index, struct BTreeNode* child) {
    struct BTreeNode* newNode = createNode();
    newNode->leaf = child->leaf;
    newNode->num_keys = T - 1;

    // Copy the last T-1 keys of child to newNode
    for (int j = 0; j < T - 1; ++j) {
        newNode->keys[j] = child->keys[j + T];
    }

    // If child is not a leaf, move the last T children of child to newNode
    if (!child->leaf) {
        for (int j = 0; j < T; ++j) {
            newNode->children[j] = child->children[j + T];
        }
    }

    // Reduce the number of keys in child
    child->num_keys = T - 1;

    // Move a key from parent to child
    for (int j = parent->num_keys; j > index; --j) {
        parent->keys[j] = parent->keys[j - 1];
    }
    parent->keys[index] = child->keys[T - 1];

    // Adjust the child pointers in the parent node
    for (int j = parent->num_keys + 1; j > index + 1; --j) {
        parent->children[j] = parent->children[j - 1];
    }
    parent->children[index + 1] = newNode;

    // Increase the number of keys in the parent node
    parent->num_keys++;
}

// Function to insert a key into a B-tree
struct BTreeNode* insert(struct BTreeNode* root, int key) {
    if (root == NULL) {
        struct BTreeNode* newNode = createNode();
        newNode->keys[0] = key;
        newNode->num_keys = 1;
        return newNode;
    }

    if (root->num_keys == 2 * T - 1) {
        struct BTreeNode* newRoot = createNode();
        newRoot->leaf = 0;
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        root = newRoot;
    }

    return insertNonFull(root, key);
}

// Function to insert a key into a non-full B-tree node
struct BTreeNode* insertNonFull(struct BTreeNode* x, int key) {
    int i = x->num_keys - 1;

    if (x->leaf) {
        // If x is a leaf, insert the key into it
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->num_keys++;
    } else {
        // If x is not a leaf, find the child to insert into
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }
        i++;
        if (x->children[i]->num_keys == 2 * T - 1) {
            // If the child is full, split it
            splitChild(x, i, x->children[i]);
            if (key > x->keys[i]) {
                i++;
            }
        }
        x->children[i] = insertNonFull(x->children[i], key);
    }

    return x;
}

// Function to print the inorder traversal of the B-tree
void inorderTraversal(struct BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->num_keys; i++) {
            if (!root->leaf) {
                inorderTraversal(root->children[i]);
            }
            printf("%d ", root->keys[i]);
        }

        if (!root->leaf) {
            inorderTraversal(root->children[i]);
        }
    }
}

// Function to print the B-tree
void printBTree(struct BTreeNode* root, int level) {
    if (root != NULL) {
        int i;
        for (i = root->num_keys - 1; i >= 0; i--) {
            printBTree(root->children[i + 1], level + 1);

            for (int k = 0; k < level; k++) {
                printf("    ");
            }
            printf("%d\n", root->keys[i]);
        }
        printBTree(root->children[i + 1], level + 1);
    }
}

int main() {
    struct BTreeNode* root = NULL;

    int keys[] = {3, 8, 14, 18, 22, 25, 30, 38, 45, 50, 60, 70, 80};
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < numKeys; ++i) {
        root = insert(root, keys[i]);
    }

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n\n");

    printf("B-tree structure:\n");
    printBTree(root, 0);

    return 0;
}
