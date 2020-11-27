#include <bits/stdc++.h>
#define ll long long
#define size 5000  //size of the Hash Table
using namespace std;

//Unordered Map using Hashing
template <class T, class U> class Unordered_Map
{
  public:
    long prm = 37;  //a prime number 
    
    class node
    {
      public:
        T key;
        U value;
        node *next;
    };
    T key;
    U value;
    node *store[size];

    Unordered_Map()
    {
        for (ll i = 0; i < size; i++)
            store[i] = NULL;
        int ch;
        pair<U, bool>ans;

        cout << "0. Exit" <<endl;
        cout << "1. insert(key,value)" << endl; //insert (key,value) pair
        cout << "2. erase(key)" << endl; //erase if key is present, otherwise do nothing
        cout << "3. find(key)" << endl; //returns true or false
        cout << "4. map(key)" <<endl;   //returns the value mapped to key
        cout<< endl;

        while(1)
        {
        cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch)
        {     
            case 0:
            exit(1);

            case 1:
            cout << "Enter Key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            ans = insert();
            if (ans.second)
               cout << "Inserted Successfully" << endl;
            else
               cout << "Key already present" << endl;
            cout<<endl;   
            break;

            case 2:     
            cout << "Enter key: ";
            cin >> key;
            ans = erase_key();
            if (ans.second)
                cout << "Deleted Successfully" << endl;
            else
                cout << "Key not present" << endl; 
            cout<<endl;    
            break;

            case 3:
            cout << "Enter key: ";
            cin >> key;
            ans = search_key();
            if (ans.second)
                cout << "true" << endl;
            else
                cout << "false" << endl;
            cout<<endl;    
            break;

            case 4:
            cout << "Enter key: ";
            cin >> key;
            ans = search_key();
            if (ans.second)
                cout << "Value = " << ans.first << endl;
            else
                cout << "Key not present" << endl;
            cout<<endl;    
            break;

            default:
            cout<<"Wrong choice"<<endl;
            cout<<endl;
            break;
        }

        }

    }

    ll Hash_fn(string k)
    {
        ll i, mul = 1, index = 0;
        for (i = 0; i < k.length(); i++)
        {
            if (i == 0)
                index = index + (mul * k[i]);
            else
            {
                mul = (mul * prm) % size;
                index = index + (mul * k[i]);
            }
        }
        index = index % size;
        return index;
    }

    pair<U, bool> insert()
    {
        pair<U, bool> res;
        ll index;
        ostringstream str1;
        str1 << key;
        string k = str1.str();
        index = Hash_fn(k);
        class node *new_node = new node;
        new_node->next = NULL;
        new_node->key = key;
        new_node->value = value;

        class node *head = store[index];

        if (head == NULL)
        {
            head = new_node;
            store[index] = head;
            res.second = true;
            return res;
        }
        else
        {
            ll flag = 0;
            while (head->next != NULL)
            {
                if (head->key == key)
                {
                    flag = 1;
                    res.second = false;
                    return res;
                }
                head = head->next;
            }
            if (flag == 0)
            {
                if (head->key != key)
                    head->next = new_node;
                else
                {
                    res.second = false;
                    return res;
                }
            }

            res.second = true;
            return res;
        }
        return res; //to get rid of compilation error
    }

   
   pair<U, bool> erase_key()
    {

        pair<U, bool> p;
        ll index;
        ostringstream str1;
        str1 << key;
        string k = str1.str();
        index = Hash_fn(k);
        class node *head = store[index];
        if (head == NULL)
        {
            p.second = false;
            return p;
        }
        else
        {
            if (head->next == NULL)
            {
                if (head->key == key)
                {
                    store[index] = NULL;
                    p.second = true;
                    free(head);
                    return p;
                }
                else
                {
                    p.second = false;
                    return p;
                }
            }
            else if (head->key == key)
            {
                store[index] = head->next;
                free(head);
                p.second = true;
                return p;
            }
            else
            {
                class node *prev = head;
                head = head->next;
                while (head != NULL)
                {
                    if (head->key == key)
                    {
                        prev->next = head->next;
                        free(head);
                        p.second = true;
                        return p;
                    }
                    prev = head;
                    head = head->next;
                }
                p.second = false;
                return p;
            }
        }
        return p; //to get rid of compilation error
    }

    pair<U, bool> search_key()
    {
        pair<U, bool> res;
        ll index;
        ostringstream str1;
        str1 << key;
        string k = str1.str();
        index = Hash_fn(k);
        class node *head = store[index];
        if (head == NULL)
        {
            res.second = false;
            return res;
        }
        else
        {
            while (head->next != NULL)
            {
                if (head->key == key)
                {
                    res.first = head->value;
                    res.second = true;
                    return res;
                }
                head = head->next;
            }
            if (head->key == key)
            {
                res.first = head->value;
                res.second = true;
                return res;
            }
            else
            {
                res.second = false;
                return res;
            }
        }
        return res; //to get rid of compilation error
    }

    
};

int main()
{
    ios_base::sync_with_stdio(false);
    Unordered_Map<string, string> ump;
    return 0;
}
