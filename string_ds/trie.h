#include "stdincludes.h"

//begintemplate trie
//description Basic trie template.  Note that since trie is very versatile and dynamic, editing the template will be needed for almost all questions
#define CHR(x, base) ((int)((x) - base))
template <int ALPHA_SIZE = 26>
struct Trie {
    struct Node {
        Node* ch[ALPHA_SIZE];
        Node() {
            for (int i = 0; i < ALPHA_SIZE; i++)
                ch[i] = nullptr;
        }
        ~Node() {
            for (int i = 0; i < ALPHA_SIZE; i++)
                if (ch[i])
                    delete ch[i];
        }
    };
    Node* root = nullptr; char base;
    void init(char base0) { root = new Node; base = base0; }
    void del() { delete root; }
    inline void insert(string &str, int pos = 0) { __insert(root, str, pos, str.length()); }
    void __insert(Node* &root, string &str, int pos, int sz) {
        if (pos == sz) return;

        int chNum = CHR(str[pos], base);
        Node* &next = root->ch[chNum];
        if (!next) next = new Node;
        __insert(next, str, pos + 1, sz);
    }
    inline bool search(string &str, int pos = 0) { __search(root, str, pos, str.length()); }
    bool __search(Node* root, string &str, int pos, int sz) {
        if (!root) return false;
        if (pos == sz) return true;

        int chNum = CHR(str[pos], base);
        Node* next = root->ch[chNum];
        return __search(next, str, pos + 1, sz);
    }
};
//endtemplate trie

#define insert(x) s = x; test.insert(s)
#define search(x, ans) s = x; ret = test.search(s); assert(ret == ans)
void trie_test() {
    Trie<> test; test.init('a');
    string s; bool ret;

    insert("hello");
    insert("world");

    search("hel", true);
    search("helloo", false);
    search("he", true);
    search("hello", true);
    search("b", false);

    search("w", true);
    search("wor", true);
    search("wo", true);
    search("wa", false);
    search("worlt", false);

    test.del();
}
#undef insert
#undef search