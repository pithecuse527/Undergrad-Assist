#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_STR_LEN 50
#define COUNT 10
#define MAX_TREE_HEIGHT 3

#define TREE_IS_EMPTY(rt) ( !(rt) ? 1 : 0 )
#define THIS_NODE_IS_LEAF(nd) ( !( (nd) -> left ) ? ( !( (nd) -> right ) ? 1 : 0 ) : 0 )
#define CURRENT_NODE_IS_BIGGER(cn, an) ( (cn) -> value > (an) -> value ? 1 : 0 )

#define LEFT_IS_EMPTY(nd) ( (nd) -> left ? 0 : 1 )
#define RIGHT_IS_EMPTY(nd) ( (nd) -> right ? 0 : 1 )
#define FOUND_DATA(dt, nd) ( (dt) -> value == (nd) -> value ? 1 : 0 )

#define MALLOC(mem, type, size)  if( !(mem = (type*)malloc(size)) ){\
                            fprintf(stderr, "Insufficient memory!");\
                            exit(EXIT_FAILURE);\
                            }

typedef struct _node *node_ptr;
typedef struct _node{
    int value;
    node_ptr left;
    node_ptr right;
} Node;

node_ptr initTree();
void addNodeWithThisValue(node_ptr to_be_added_node, node_ptr current_node_ptr);     //why returns node_ptr??
void printTreeIn2D(node_ptr root, int space);
void preOrderPrint(node_ptr current_node_ptr);
void deleteTree(int data, node_ptr root);
int searchByPre(node_ptr to_find, node_ptr current_node_ptr, int level);

int main(void)
{
    int choice, tmp;
    node_ptr root = NULL;
    node_ptr tmp_node;

    while(TRUE)
    {
        printf("1.Initiate\n2.Add\n3.Draw\n4.Retrieve\n5.Delete\n6.Find\n7.Exit\n\n");
        printf("Your Choice? ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                root = initTree(root);
                
                break;
                
            case 2:
                if(!root)
                {
                    printf("\n\n======= You must initiate first =======\n\n");
                    
                    break;
                }
                tmp_node = NULL;
                MALLOC(tmp_node, Node, sizeof(Node));
                tmp_node -> left = tmp_node -> right = NULL;
                
                printf("Value : ");
                scanf("%d", &(tmp_node -> value));
                printf("\n\n");
                
                if(tmp = searchByPre(tmp_node, root, 1))   // if the node already exist
                {
                    printf("Already Existed in level %d...\n\n", tmp);
                    
                    break;
                }
                
                addNodeWithThisValue(tmp_node, root);
                
                break;
            
            case 3:
                printTreeIn2D(root, 3);
                
                break;
                
            case 4:
                printf("\n=============== Retrieved ===============\n");
                preOrderPrint(root);
                printf("\n=========================================\n\n");
                
                break;
                
            case 6:
                tmp_node = NULL;
                MALLOC(tmp_node, Node, sizeof(Node));
                tmp_node -> left = tmp_node -> right = NULL;
                
                printf("Type the value of the node to find ");
                scanf("%d", &(tmp_node -> value));
                
                tmp = searchByPre(tmp_node, root, 1);
                if(tmp) printf("\nIt is in level %d\n\n", tmp);
                else printf("Not found...\n\n");
                
                break;
                
            default:
                printf("Wrong Choice.\n");
            
        }
    }
    
    return 0;
}

node_ptr initTree(node_ptr root)
{
    char choice[MAX_STR_LEN];
    
    while(root)            // if already initialized
    {
        printf("In this way, you'll lose your previous tree. Continue? (y/n) ");
        scanf("%s", choice);
        if(!strcmp(choice, "Yes") || !strcmp(choice, "yes") || !strcmp(choice, "Y") || !strcmp(choice, "y")) break;
        else if(!strcmp(choice, "No") || !strcmp(choice, "no") || !strcmp(choice, "N") || !strcmp(choice, "n")) return root;
        else
        {
            printf("\n\n========== Please type the valid string or char...!! ==========\n\n");
            scanf("%s", choice);
            continue;
        }
    }
    
    MALLOC(root , Node, sizeof(Node));
    root -> left = root -> right = NULL;
    
    printf("Successively initialized. Type the value of this root node : ");
    scanf("%d", &(root -> value));
    
    printf("\n\n");
    
    return root;
}

int searchByPre(node_ptr to_find, node_ptr current_node_ptr, int level)
{
    if(!current_node_ptr) return 0;
    
    if(FOUND_DATA(to_find, current_node_ptr)) return level;
    
    if(!THIS_NODE_IS_LEAF(current_node_ptr))
    {
        if(CURRENT_NODE_IS_BIGGER(current_node_ptr, to_find)) return searchByPre(to_find, current_node_ptr -> left, level + 1);
        else return searchByPre(to_find, current_node_ptr -> right, level + 1);
    }
    
    return 0;
}

// node_ptr insertNodeWithThisValue(int to_insert, node_ptr current_node_ptr)       // parameter name changed : "root" to "current_node_ptr"  &  "data" to "to_insert"
//                                                                                  // since you implement this function as recursive, you should named parameter as its role (please pay attention always)
// {
//     if(searchByPre(data, current_node_ptr))          // move this control statement to main function You should avoid using multiple searchByPre function SINCE this function(insertNodeWithThisValue) is recursive.
//     {
//         printf("ALREADY EXISTS...\n");
//         return NULL;                 // if you don't have to return something, just give back nil(NULL)
//     }
//     else
//     {
//         if(!current_node_ptr)
//         {
//             root = (Node*)malloc(sizeof(Node));
//             root->leftChild = root->rightChild = NULL;
//             root->value = value;
//             return root;
//         }
//         else
//         {
//             if(root -> value > value) root -> leftChild = insertTree(data, root -> left);
//             else root -> rightChild = insertTree(data, root -> right);
//         }
//     }
// }


// 1. parameter name changed : "root" to "current_node_ptr"  &  "data" to "to_insert"
//    since you implement this function as recursive, you should named parameter as its role (please pay attention always)
// 2. avoid using search function in this function since this function is recursive (use it in main function)
void addNodeWithThisValue(node_ptr to_be_added_node, node_ptr current_node_ptr)
{
    // Base case1
    if(LEFT_IS_EMPTY(current_node_ptr) && CURRENT_NODE_IS_BIGGER(current_node_ptr, to_be_added_node))
    {
        current_node_ptr -> left = to_be_added_node;
        return;
    }
    // Base case2
    else if(RIGHT_IS_EMPTY(current_node_ptr) && !CURRENT_NODE_IS_BIGGER(current_node_ptr, to_be_added_node))
    {
        current_node_ptr -> right = to_be_added_node;
        return;
    }
    else
    {
        if(CURRENT_NODE_IS_BIGGER(current_node_ptr, to_be_added_node)) addNodeWithThisValue(to_be_added_node, current_node_ptr -> left);
        else addNodeWithThisValue(to_be_added_node, current_node_ptr -> right);
    }
    
    return;
}

void printTreeIn2D(node_ptr root, int space) 
{ 
    // Base case 
    if (root == NULL) return;
    int i;
  
    // Increase distance between levels 
    space += COUNT;
  
    // Process right child first 
    printTreeIn2D(root -> right, space);
  
    // Print current node after space 
    // count
    printf("\n");
    for(i = COUNT; i < space; i++) printf(" ");
    printf("%d\n", root -> value);
  
    // Process left child
    printTreeIn2D(root -> left, space);
    
}

void preOrderPrint(node_ptr current_node_ptr)
{
    if(current_node_ptr)
    {
        printf("%d ", current_node_ptr -> value);
        preOrderPrint(current_node_ptr -> left);
        preOrderPrint(current_node_ptr -> right);
    }
}

node_ptr delNode(int data, node_ptr root)
{
    
}