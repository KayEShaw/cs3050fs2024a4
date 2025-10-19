#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "bst.h"

// Local functions
//insert function to assist TreeInsert
static Node *NewNode(void *satellite, long long key){
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->satellite = satellite;
    node->left = node->right = NULL;
    return node;
}
static Node *Insert(Node *root, void *satellite, long long key){
    //handle an empty tree
    if(root == NULL){
        return NewNode(satellite, key);
    }
    //if the new value is less than the root value go to the left
    //if the new value is greater than the root go to the right
    if(key < root->key){
        root->left = Insert(root->left, satellite, key);
    }else if(key > root->key){
        root->right = Insert(root->right, satellite, key);
    }else{
        //once found update the key
        root->satellite = satellite;
    }
    return root;
}

//in order traversal to assist the In Order public function
static void InOrderNode(Node *node, NODEVISITFUNC func){
    if(node == NULL){
        return;
    }
    //first visit the left subtree
    InOrderNode(node->left, func);
    //once returned from the left subtree 
    func(node->satellite);
    InOrderNode(node->right, func);
}

//post order traversal function 
static void postOrderNode(Node *node, NODEVISITFUNC func){
    if(node == NULL){
        return;
    }
    postOrderNode(node->left, func);
    postOrderNode(node->right, func);
    func(node->satellite);
}
static void preOrderNode(Node *node, NODEVISITFUNC func){
    if(node == NULL){
        return;
    }
    func(node->satellite);
    preOrderNode(node->left, func);
    preOrderNode(node->right, func);
}

//search node function to assist Search
//finds and returns data
static Node *SearchNode(Node *root, long long key){
     //check empty tree
     if(root == NULL){
        return NULL;
     }
     //check current
     if(key == root->key){
        return root;
     }else if(key < root->key){
        return SearchNode(root->left, key);
     }else{
        return SearchNode(root->right, key);
     }
}

static Node *FindMin(Node *root){
    while(root && root->left){
        root = root->left;
    }
    return root;
}

static Node *DeleteNode(Node *root, long long key){
    if (root == NULL) return NULL;

    if (key < root->key){
        root->left = DeleteNode(root->left, key);
    }else if(key > root->key){
        root->right = DeleteNode(root->right, key);
    }else{
        //when you find node
        if(root->left == NULL){
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = FindMin(root->right);
        root->key = temp->key;
        root->satellite = temp->satellite;
        root->right = DeleteNode(root->right, temp->key);
    }
    return root;
}

// These are stubs.  That is, you need to implement these functions.

BST * NewBST()
{
    BST *tree = (BST *)malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

void TreeInsert(BST * pBST, void * satellite, long long key)
{
    pBST->root = Insert(pBST->root, satellite, key);
}

void InOrder(BST * pBST, NODEVISITFUNC func)
{
    InOrderNode(pBST->root, func);
}

void PreOrder(BST * pBST, NODEVISITFUNC func)
{
    preOrderNode(pBST->root, func);
}

void PostOrder(BST * pBST, NODEVISITFUNC func)
{
    postOrderNode(pBST->root, func);
}

void * Search(BST * pBST, long long key)
{
    Node *node = SearchNode(pBST->root, key);
    return node ? node->satellite : NULL;
}

void TreeDelete(BST * pBST, long long key)
{
    pBST->root = DeleteNode(pBST->root, key);
}

