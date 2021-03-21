#include <iostream>
using namespace std;

class HashTable
{
public:
    HashTable(){};
    virtual bool exists(int val) = 0;
    virtual void insert(int val) = 0;
    virtual int remove(int val) = 0;
    virtual void print() = 0;
};

class Node
{
public:
    int val;
    Node *next;
    Node(int val = 0)
    {
        this->val = val;
        next = nullptr;
    }
};

class ChainNode
{
public:
    int block_size;
    Node *link;
    ChainNode()
    {
        block_size = 0;
        link = nullptr;
    }
};

//load_Factor = (total# of values stored in hashtable)/(size of hashtable(keys));
class sepChain : public HashTable
{
    int m_size;         //size of hashtable
    ChainNode **chains; //chain links to store hashed values
    int m_total;        //total# of elements in the hashtable
    int gethash(int val)
    {
        return val % m_size;
    }

public:

    sepChain(int r_size = 10)
    {
        r_size = max(r_size,1);
        m_size = r_size;
        m_total = 0;
        chains = new ChainNode *[m_size];
        for (int i = 0; i < m_size; ++i)
        {
            chains[i] = new ChainNode();
        }
    }

    bool exists(int val)
    {

        int id = gethash(val);
        Node *tmpnode = chains[id]->link;
        while (tmpnode)
        {
            if (tmpnode->val == val)
                return true;
            tmpnode = tmpnode->next;
        }
        return false;
    }

    void insert(int val)
    {
        if (!exists(val))
        {
            int id = gethash(val);
            m_total++;
            chains[id]->block_size++;
            Node *tmpNode = new Node(val);
            tmpNode->next = chains[id]->link;
            chains[id]->link = tmpNode;
            if(chains[id]->block_size > (m_size*75)/100)
            {
                rehash();
            }
        }
    }

    int remove(int val)
    {
        if (exists(val))
        {
            int id = gethash(val);
            Node *tmp = chains[id]->link;
            Node *prev = nullptr;
            while (tmp)
            {
                if (tmp->val == val)
                {
                    break;
                }
                prev = tmp;
                tmp = tmp->next;
            }
            if (prev)
            {
                prev->next = tmp->next;
            }
            else if (tmp)
            {
                tmp = tmp->next;
                chains[id]->link = tmp;
            }
            chains[id]->block_size--;
            m_total--;
            return 1;
        }
        return 0;
    }

    void rehash()
    {
        m_size += m_size;                //double the hash
        ChainNode **old_chains = chains; //temporary hold the old values
        chains = new ChainNode *[m_size];
        for (int i = 0; i < m_size; ++i)
        {
            chains[i] = new ChainNode();
        }
        for (int i = 0; i < m_size / 2; ++i)
        {
            Node *head = old_chains[i]->link;
            m_total -= old_chains[i]->block_size;
            while (head)
            {
                int val = head->val;
                insert(val);
                head = head->next;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < m_size; ++i)
        {
            Node *head = chains[i]->link;
            cout << i << " : ";
            while (head)
            {
                cout << head->val << " ";
                head = head->next;
            }
            cout << "\n";
        }
    }
};

int main()
{
    int _size;
    cin >> _size;
    HashTable *h = new sepChain(_size);
    while (true)
    {
        cout <<":: OPERATIONS ::\n";
        cout << "0: insert: \n";
        cout << "1: check: \n";
        cout << "2: remove: \n";
        cout << "3: print: \n";
        cout << "4: exit\n";
        int c;
        cin >> c;
        int val;
        switch (c)
        {
        case 0:
            cin >> val;
            h->insert(val);
            break;
        case 1:
            cin >> val;
            cout << h->exists(val) << "\n";
            break;
        case 2:
            cin >> val;
            cout << h->remove(val) << "\n";
            break;
        case 3:
            h->print();
            break;
        case 4:
            exit(0);
        default:
            break;
        };
    }
    return 0;
}