# To implement a suffix trie using the brute-force suffix insertion method.


#include <iostream>
#include <string>
using namespace std;

struct Node
{
    Node* child[256];
    bool isEnd;

    Node()
    {
        for (int i = 0; i < 256; i++)
            child[i] = NULL;

        isEnd = false;
    }
};

class SuffixTrie
{
    Node* root;

public:
    SuffixTrie()
    {
        root = new Node();
    }

    // Insert a suffix
    void insert(string s)
    {
        Node* current = root;

        for (int i = 0; i < s.length(); i++)
        {
            int index = (unsigned char)s[i];

            if (current->child[index] == NULL)
                current->child[index] = new Node();

            current = current->child[index];
        }

        current->isEnd = true;
    }

    // Construct suffix trie
    void build(string text)
    {
        for (int i = 0; i < text.length(); i++)
        {
            insert(text.substr(i));
        }
    }

    // Search a pattern
    bool search(string pattern)
    {
        Node* current = root;

        for (int i = 0; i < pattern.length(); i++)
        {
            int index = (unsigned char)pattern[i];

            if (current->child[index] == NULL)
                return false;

            current = current->child[index];
        }

        return true;
    }
};

int main()
{
    string text, pattern;

    cout << "Enter text: ";
    cin >> text;

    SuffixTrie tree;

    tree.build(text);

    cout << "Enter pattern to search: ";
    cin >> pattern;

    if (tree.search(pattern))
        cout << "Pattern found in text.";
    else
        cout << "Pattern not found.";

    return 0;
}
/**
Enter text: BANANA
Enter pattern to search: APPLE

Pattern not found.
  **/
