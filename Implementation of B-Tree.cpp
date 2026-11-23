# To implement a B-Tree and perform insertion and traversal operations.


#include <iostream>
using namespace std;

class BTreeNode
{
    int *keys;
    int t;
    BTreeNode **child;
    int n;
    bool leaf;

public:
    BTreeNode(int degree, bool isLeaf)
    {
        t = degree;
        leaf = isLeaf;

        keys = new int[2 * t - 1];
        child = new BTreeNode*[2 * t];

        n = 0;
    }

    void traverse()
    {
        int i;

        for (i = 0; i < n; i++)
        {
            if (!leaf)
                child[i]->traverse();

            cout << keys[i] << " ";
        }

        if (!leaf)
            child[i]->traverse();
    }

    void insertNonFull(int k)
    {
        int i = n - 1;

        if (leaf)
        {
            while (i >= 0 && keys[i] > k)
            {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
            n++;
        }
        else
        {
            while (i >= 0 && keys[i] > k)
                i--;

            if (child[i + 1]->n == 2 * t - 1)
            {
                splitChild(i + 1, child[i + 1]);

                if (keys[i + 1] < k)
                    i++;
            }

            child[i + 1]->insertNonFull(k);
        }
    }

    void splitChild(int i, BTreeNode *y)
    {
        BTreeNode *z = new BTreeNode(t, y->leaf);

        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];

        if (!y->leaf)
        {
            for (int j = 0; j < t; j++)
                z->child[j] = y->child[j + t];
        }

        y->n = t - 1;

        for (int j = n; j >= i + 1; j--)
            child[j + 1] = child[j];

        child[i + 1] = z;

        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        keys[i] = y->keys[t - 1];

        n++;
    }

    friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int t;

public:
    BTree(int degree)
    {
        root = NULL;
        t = degree;
    }

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    void insert(int k)
    {
        if (root == NULL)
        {
            root = new BTreeNode(t, true);
            root->keys[0] = k;
            root->n = 1;
        }
        else
        {
            if (root->n == 2 * t - 1)
            {
                BTreeNode *s = new BTreeNode(t, false);

                s->child[0] = root;
                s->splitChild(0, root);

                int i = 0;

                if (s->keys[0] < k)
                    i++;

                s->child[i]->insertNonFull(k);

                root = s;
            }
            else
                root->insertNonFull(k);
        }
    }
};

int main()
{
    BTree tree(3);

    int n, x;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        tree.insert(x);
    }

    cout << "B-Tree traversal: ";
    tree.traverse();

    return 0;
}

/**
Enter number of elements: 8
Enter elements: 10 20 5 6 12 30 7 17

B-Tree traversal: 5 6 7 10 12 17 20 30
  **/

