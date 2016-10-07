#include <iostream>
#include <utility>

using namespace std;

typedef int (*hash_code_fxn_ptr)(string);
typedef int (*compression_fxn_ptr)(int);

class hash_set {
    protected:
        hash_code_fxn_ptr hash_code_fxn;
        compression_fxn_ptr compression_fxn;
        int size;
        bool equals(string a, string p) {
            // in this case always a.length()=b.length()
            for (unsigned i = 0; i < a.length(); i++) {
                if (p.at(i) != '?' && a.at(i) != p.at(i)) {
                    return false;
                }
            }
            return true;
        }
    public:
        hash_set(hash_code_fxn_ptr hcf, compression_fxn_ptr cfn, int _N) {
            this->hash_code_fxn = hcf;
            this->compression_fxn = cfn;
            this->size = _N;
        }
        virtual void insert(string t)=0;
        virtual pair<int, int> contains(string t)=0;
        virtual ~hash_set() {
        }
};

class hash_set_linear_probing: hash_set {
    private:
        bool* occupied;
        pair<string, int>* table;
    public:
        hash_set_linear_probing(hash_code_fxn_ptr hcf, compression_fxn_ptr cfn, int _N)
                : hash_set(hcf, cfn, _N) {
            occupied = new bool[size];
            table = new pair<string, int> [size];
            for (int i = 0; i < size; i++) {
                occupied[i] = false;
                table[i] = make_pair("", 0);
            }
        }
        void insert(string str) {
            int hash_value = (*compression_fxn)((*hash_code_fxn)(str));
            while (occupied[hash_value]) {
                hash_value++;
                hash_value %= size;
            }
            if (!occupied[hash_value]) {
                occupied[hash_value] = true;
                table[hash_value].first = str;
                table[hash_value].second = (*compression_fxn)((*hash_code_fxn)(str));
            }
        }
        pair<int, int> contains(string str) { // pair of (false positive, total string compares)
            int hash_value = (*compression_fxn)((*hash_code_fxn)(str));
            if (!occupied[hash_value]) {
                return make_pair(0, 0); //true negative
            }
            int cmp = 0, fp = 0;
            while (occupied[hash_value]) {
                if (table[hash_value].second == hash_value) {
                    cmp++;
                    if (equals(table[hash_value].first, str)) {
                        return make_pair(fp, cmp); //positive
                    } else {
                        fp++; //false positive
                    }
                }
                hash_value++;
                hash_value %= size;
            }
            return make_pair(fp, cmp); // negative
        }
        virtual ~hash_set_linear_probing() {

        }
};

class hash_set_chaining: public hash_set {
    private:
        struct Node {
                Node* next;
                int key;
                string value;
                Node(int k, string s)
                        : next(NULL), key(k), value(s) {
                }
        };
        Node** table;
    public:
        hash_set_chaining(hash_code_fxn_ptr hcf, compression_fxn_ptr cfn, int _N)
                : hash_set(hcf, cfn, _N) {
            table = new Node*[size];
            for (int i = 0; i < size; i++) {
                table[i] = NULL;
            }
        }
        void insert(string str) {
            int h = (*compression_fxn)((*hash_code_fxn)(str));
            if (table[h] == NULL) {
                table[h] = new Node(h, str);
            } else {
                Node* head = table[h];
                while (head->next != NULL) {
                    head = head->next;
                }
                head->next = new Node(h, str);
            }
        }
        pair<int, int> contains(string str) {
            int h = (*compression_fxn)((*hash_code_fxn)(str));
            if (table[h] == NULL) {
                return make_pair(0, 0);
            } else {
                Node* head = table[h];
                int cmp = 0, fp = 0;
                do {
                    cmp++;
                    if (equals(head->value, str)) {
                        return make_pair(fp, cmp);
                    } else {
                        fp++;
                    }
                } while ((head = head->next) != NULL);
                return make_pair(fp, cmp);
            }
        }
        virtual ~hash_set_chaining() {

        }

};
