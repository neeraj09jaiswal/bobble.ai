#include<cstdio> 
#define MARKER ')' 
#define N 5 
using namespace std; 
struct Node { 
   char key; 
   Node *child[N];  // An array of pointers for N children 
}; 
Node *newNode(char key) 
{ 
    Node *temp = new Node; 
    temp->key = key; 
    for (int i = 0; i < N; i++) 
        temp->child[i] = NULL; 
    return temp; 
} 
  
//function stores the given N-ary tree in a file pointed by fp 
void serialize(Node *root, FILE *fp) 
{ 
    // Base case 
    if (root == NULL) return; 
  
    // Else, store current node and recur for its children 
    fprintf(fp, "%c ", root->key); 
    for (int i = 0; i < N && root->child[i]; i++) 
         serialize(root->child[i],  fp); 
  
    // Store marker at the end of children 
    fprintf(fp, "%c ", MARKER); 
} 
 
int deSerialize(Node *&root, FILE *fp) 
{ 
    // Read next item from file. If theere are no more items or next 
    // item is marker, then return 1 to indicate same 
    char val; 
    if ( !fscanf(fp, "%c ", &val) || val == MARKER ) 
       return 1; 
  
    // Else create node with this item and recur for children 
    root = newNode(val); 
    for (int i = 0; i < N; i++) 
      if (deSerialize(root->child[i], fp)) 
         break; 
  
    // Finally return 0 for successful finish 
    return 0; 
} 
Node *createDummyTree() 
{ 
    Node *root = newNode('A'); 
    root->child[0] = newNode('B'); 
    root->child[1] = newNode('C'); 
    root->child[2] = newNode('D'); 
    root->child[0]->child[0] = newNode('E'); 
    root->child[0]->child[1] = newNode('F'); 
    root->child[2]->child[0] = newNode('G'); 
    root->child[2]->child[1] = newNode('H'); 
    root->child[2]->child[2] = newNode('I'); 
    root->child[2]->child[3] = newNode('J'); 
    root->child[0]->child[1]->child[0] = newNode('K'); 
    return root; 
} 
void traverse(Node *root) 
{ 
    if (root) 
    { 
        printf("%c ", root->key); 
        for (int i = 0; i < N; i++) 
            traverse(root->child[i]); 
    } 
} 
int main() 
{ 
    Node *root = createDummyTree(); 
  
    // Let us open a file and serialize the tree into the file 
    FILE *fp = fopen("tree.txt", "w"); 
    if (fp == NULL) 
    { 
        puts("Could not open file"); 
        return 0; 
    } 
    serialize(root, fp); 
    fclose(fp); 
  
    // Let us deserialize the storeed tree into root1 
    Node *root1 = NULL; 
    fp = fopen("tree.txt", "r"); 
    deSerialize(root1, fp); 
  
    printf("Constructed N-Ary Tree from file is \n"); 
    traverse(root1); 
  
    return 0; 
}
