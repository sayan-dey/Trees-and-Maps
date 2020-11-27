#include<bits/stdc++.h> 
#include<cmath>
using namespace std; 

//AVL Tree    
template <class T> class AVL 
{

public:
int count=0;  
int c=0;    
class Node  
{  
    public: 
    T key;  
    Node *left;  
    Node *right;  
    int height;  
};  
Node* res;

AVL()
{
    Node *root = NULL;
    Node *res = NULL;  
    T key,l,r;
    int k,ch; //keep these as int

    /* 0.  Exit
       1.  Insertion
       2.  Display (Inorder)
       3.  Delete
       4.  Search
       5.  Count occurrences of element
       6.  lower_bound
       7.  upper_bound
       8.  Closest element to some value  //It will not work for String data type
       9.  Kth largest element
      10. Count no. of elements in given range*/

    while (1)
    {
        cout<<"Enter your choice: ";
        cin>>ch;

        switch(ch)
        {

        case 0:
        exit(1);

        case 1:    
        cout<<"Enter key to be inserted: ";
        cin>>key;
        root = insert(root, key);
        cout<<endl;
        break;
  
        case 2:
        cout << "Inorder traversal of the AVL tree is \n";  
        InOrder(root);  
        cout<<endl<<endl;
        break;

        case 3:
        cout<<"Enter key to be deleted: ";
        cin>>key;
        root = deleteNode(root, key);  
        cout<<endl;
        break;

        case 4:
        cout<<"Enter key to be searched: ";
        cin>>key;
        res=searchNode(root, key);
        if(res==NULL)
        cout<< key <<" is not found"<<endl;
        else
        cout<< key <<" is found"<<endl;
        cout<<endl;
        break;

        case 5:
        cout<<"Enter key whose no. of occurrences is to be found: ";
        cin>>key;
        count=0;
        cout<<"No. of occurrences of "<<key<<" = "<<countNode(root,key)<<endl;
        cout<<endl;
        break;

        case 6:
        cout<<"Enter key whose lower_bound is to be found: ";
        cin>>key;
        res=root;
        c=0;
        res=lower_bound(root,key);
        if(res==NULL)
        cout<<"Lower Bound of "<<key<<" is absent"<<endl;
        else
        cout<<"Lower Bound of "<<key<<" = "<<res->key<<endl;
        cout<<endl;
        break;

        case 7:
        cout<<"Enter key whose upper_bound is to be found: ";
        cin>>key;
        res=root;
        c=0;
        res=upper_bound(root,key);
        if(res==NULL)
        cout<<"Upper Bound of "<<key<<" is absent"<<endl;
        else
        cout<<"Upper Bound of "<<key<<" = "<<res->key<<endl;
        cout<<endl;
        break;
        
        case 8:  //keep it commented for String data type
        cout<<"Enter key whose closest element is to be found: ";
        cin>>key;
        res=root;
        c=0;
        res=closest(root,key);
        if(res==NULL)
        cout<<"Closest element of "<<key<<" is absent"<<endl;
        else
        cout<<"Closest element of "<<key<<" = "<<res->key<<endl;
        cout<<endl;
        break; 

        case 9:
        cout<<"Enter k: ";
        cin>>k;
        c=0;
        kth_largest(root,k);
        //Not printing anything if kth largest is absent
        cout<<endl;
        break;

        case 10:
        cout<<"Enter Lower Limit: ";
        cin>>l;
        cout<<"Enter Upper Limit: ";
        cin>>r;
        cout<<"No. of elements in this range = "<<countElements(root,l,r)<<endl;
        cout<<endl;
        break;

        default:
        cout<<"Wrong Entry"<<endl;
        cout<<endl;
        break;

       }

    }
}

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
  

Node* newNode(T key)  
{  
    Node* node = new Node(); 
    node->key = key;  
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
  
Node* insert(Node* node, T key)  
{  
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else  //for (key >= node->key) as, acc. to problem, duplicates are allowed  
        node->right = insert(node->right, key);  
    
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
Node* deleteNode(Node* root, T key)  
{  
       
    if (root == NULL)  
        return root;  
   
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
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
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
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
            root->right = deleteNode(root->right,  
                                     temp->key);  
        }  
    }  
  
    // If the tree had only one node 
    if (root == NULL)  
    return root;  
  
   
    root->height = 1 + max(height(root->left),  
                           height(root->right));  
  
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

Node* searchNode(Node* root, T key)
{
    
    // Base Cases: root is null or key is present at root 
    if (root == NULL) 
       return NULL; 
    if (key == root->key) 
       return root;

    // Key is greater than root's key 
    if (key > root->key) 
       return searchNode(root->right, key); 
  
    // Key is smaller than root's key 
    return searchNode(root->left, key); 
}  

int countNode(Node* root, T key)
{ 
    if (root == NULL) 
       return count; 
    if (key == root->key) 
    {
        count++;
        countNode(root->right,key);
    }

    if (key > root->key) 
      countNode(root->right, key); 
  
    // Key is smaller than root's key 
    return countNode(root->left, key); 
}  

Node* lower_bound(Node* root, T key)
{
    if ((root==NULL)&&(c>0))
       return res;

    if(root==NULL)
       return NULL;

    if (key == root->key)
       return root;

    if(key < root->key)
    {
        res=root;
        c++;    
        return lower_bound(root->left,key);
    }
   
    // Key is greater than root's key 
    return lower_bound(root->right,key);

}

Node* upper_bound (Node* root, T key)
{
    if ((root == NULL) && (c>0))
       return res; 

    if (root==NULL)
        return NULL;
  
    if (key < root->key) 
    {
        res=root;
        c++;    
        return upper_bound(root->left,key);
    }    
  
    // Key is greater than or equal to root's key 
    return upper_bound(root->right, key); 
}


Node* closest (Node *root, T key)    //keep it commented for String data type
{
    if ((root==NULL) && (c>0))
        return res;

    if (root==NULL)
        return NULL;

    if (key < root->key)
    {
        if(abs(root->key - key) < abs(res->key - key) )
        res=root;
        c++;    
        return closest(root->left,key);
    }

    if (key > root->key)        
    {
        if(abs(root->key - key) <= abs(res->key - key) )
        res=root;
        c++;    
        return closest(root->right,key);
    }
    
    //Key is equal to root's key
    return root;
}


void kth_largest (Node *root, int k) //Time complexity=O(logn+k)=O(logn)
{
    if( (root==NULL) || (c>=k) )
        return ;
    
    kth_largest(root->right, k);
    
    c++;
    if(c==k)
    {
        cout<<k<<"th largest element = "<<root->key<<endl;
        return;
    }

    kth_largest(root->left, k);    

}

int countElements (Node* root, T l, T r)
{
    if(root==NULL)
        return 0;

    if(root->key < l)
        return countElements(root->right,l,r);    

    if(root->key > r)
        return countElements(root->left,l,r);    

    //when (l<=root->key<=r)
    return 1+countElements(root->left,l,r)+countElements(root->right,l,r);
}

void InOrder(Node *root)  
{  
    if(root != NULL)  
    {  
        InOrder(root->left); 
        cout << root->key << " ";  
        InOrder(root->right);  
    }  
}  

};  
 
int main()  
{  
    ios_base::sync_with_stdio(false);
    AVL <int> avltree;
    return 0;  
}  
  

 