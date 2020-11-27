#include<bits/stdc++.h> 
#include<cmath>
using namespace std; 

//Ordered Map (using AVL Tree)

template <class T, class U> class Ordered_Map
{

public:

int s=0; //size of the map;
class Node  
{  
    public: 
    T key;  
    U value;
    Node *left;  
    Node *right;  
    int height;  
};  

Node *root = NULL;

// A utility function to get height  
// of the tree  
int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  
  
// A utility function to get maximum 
// of two integers  
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
  

Node* newNode(T key, U value)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->value = value;
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; //Leaf height=1  
    return(node);  
}  
  
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left), height(y->right)) + 1;  
    x->height = max(height(x->left), height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left), height(x->right)) + 1;  
    y->height = max(height(y->left), height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) -  
           height(N->right);  
}  
  
Node* insert(Node* node, T key, U value)  
{  
    if (node == NULL)   
        return(newNode(key, value));  
   
    if (key < node->key)  
        node->left = insert(node->left, key, value);

    else if (key > node->key)  
        node->right = insert(node->right, key, value);  
    else  //(key == node->key)
    {
        s--;
        node->value=value;
        return node;
    }
        
    /* Update height of this ancestor node */
    node->height = 1 + max(height(node->left),  height(node->right));  
  
    //calculating the Balance Factor
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, 
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}  
  
  
Node * minValueNode(Node* node)  
{  
    Node* current = node;  
  
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  

// Recursive function to delete a node  
// with given key from subtree with  
// given root. It returns root of the  
// modified subtree.  
Node* erase(Node* root, T key)  
{  
       
    if (root == NULL)  
        return root;  
   
    if ( key < root->key )  
        root->left = erase(root->left, key);  
  
    else if( key > root->key )  
        root->right = erase(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->left == NULL) || (root->right == NULL) )  
        {  
            Node *temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of the non-empty child   
            s--;
            free(temp);  
        }  
        else
        {  
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            Node* temp = minValueNode(root->right);  
  
            // Copy the inorder successor's  
            // data to this node  
            root->key = temp->key;  
  
            // Delete the inorder successor  
            root->right = erase(root->right, temp->key);  
        }  
    }  
  
    // If the tree had only one node 
    if (root == NULL)  
    return root;  
  
   
    root->height = 1 + max(height(root->left), height(root->right));  
  
    //calculating the Balance Factor
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  

string find(Node* root, T key) 
{ 
    while (root != NULL) { 
        
        if (key > root->key) 
            root = root->right; 
        else if (key < root->key) 
            root = root->left; 
        else
            return "true"; 
    } 
    return "0"; 
} 

void InOrder(Node *root)  
{  
    if(root != NULL)  
    {  
        InOrder(root->left); 
        cout << root->key <<" : "<<root->value<<endl;  
        InOrder(root->right);  
    }  
}  

int size()
{
    return s;
}

void PostOrder(Node *root)  
{  
    if(root != NULL)  
    {  
        PostOrder(root->left); 
        PostOrder(root->right);  
        free(root);
    }
}  

void clear (Node *node)
{
    s=0;
    PostOrder(node);
    root=NULL;
}

Node* search_help(Node* root, T key)
{
    
     
    if (root == NULL) 
       return NULL; 
    if (key == root->key) 
       return root;

    
    if (key > root->key) 
       return search_help(root->right, key); 
  
    
    return search_help(root->left, key); 
}  

U &operator[] (T key)
{

    Node* res = search_help(root, key);
    if (res)
        return res->value;
    
    //else   
        U value;
        cout<<"No value present"<<endl;;
        cout<<"Enter a value: ";
        cin>>value;
        s++;
        root=insert(root,key,value);
        return search_help(root,key)->value;
}

};  
 
int main()  
{  
    ios_base::sync_with_stdio(false);
    Ordered_Map <string,string> omp;

    string key;
    string value;
    int ch; //keep this as int

    /* 0.  Exit
       1.  insert(key, value)
       2.  Display 
       3.  erase(key)
       4.  find(key)
       5.  map_obj [key]
       6.  size()
       7.  clear()
      */
       

    while (1)
    {
        cout<<"Enter your choice: ";
        cin>>ch;

        switch(ch)
        {

        case 0:
        exit(1);

        case 1:    
        cout<<"Enter key : ";
        cin>>key;
        cout<<"Enter value : ";
        cin>>value;
        omp.s=omp.s+1;
        omp.root = omp.insert(omp.root, key, value);
        cout<<endl;
        break;
  
        case 2:
        cout << "Currently, the Ordered Map is: \n";  
        omp.InOrder(omp.root);  
        cout<<endl;
        break;

        case 3:
        cout<<"Enter key to be deleted: ";
        cin>>key;
        omp.root = omp.erase(omp.root, key);  
        cout<<endl;
        break;

        case 4:
        cout<<"Enter key to be searched: ";
        cin>>key;
        cout<<"Search returned: "<<omp.find(omp.root, key)<<endl;
        cout<<endl;
        break;

        case 5:
        cout<<"Enter key: ";
        cin>>key;
        cout<<"omp["<<key<<"] = "<<omp[key]<<endl;
        cout<<endl;
        break;

        case 6:
        cout<<"Size = "<<omp.size() <<endl;
        cout<<endl;
        break;
        
        case 7:
        omp.clear(omp.root);
        break;

        default:
        cout<<"Wrong Entry"<<endl;
        cout<<endl;
        break;

       }

    }
    

    return 0;  
}  
  

 