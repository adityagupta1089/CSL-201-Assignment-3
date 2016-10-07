#include "../include/include.h"
#include "progress_bar.cpp"

#include <fstream>
#include "hash_set.cpp"
#include "print.cpp"

using namespace std;

int main(int argv, char** argc) {
    //============================================================
    hash_code_fxn_ptr hcs[] = { integer_casting, component_sum, polynomial_sum, cyclic_sum };
    compression_fxn_ptr cfs[] = { division, mad, multiplication };

    int hcn = sizeof(hcs) / sizeof(hash_code_fxn_ptr);
    int cfn = sizeof(cfs) / sizeof(compression_fxn_ptr);

    int tfn = hcn * cfn;
    //============================================================
    hash_set_linear_probing** hslp = new hash_set_linear_probing*[tfn];
    for (int i = 0; i < hcn; i++)
        for (int j = 0; j < cfn; j++)
            hslp[i * cfn + j] = new hash_set_linear_probing(hcs[i], cfs[j], _N);
    //============================================================
    hash_set_chaining** hsc = new hash_set_chaining*[tfn];
    for (int i = 0; i < hcn; i++)
        for (int j = 0; j < cfn; j++)
            hsc[i * cfn + j] = new hash_set_chaining(hcs[i], cfs[j], _N);
    //============================================================
    string line;
    string text = "";
    ifstream ifs_t;
    ifs_t.open("../data/T.txt");
    if (ifs_t.is_open()) {
        while (ifs_t >> line)
            text += line;
    } else {
        cout << "Could not open T.txt.";
        return 0;
    }

    ifs_t.close();
    //============================================================
    int pl = 0;
    ifstream ifs_p;
    ifs_p.open("../data/P.txt");
    //============================================================
    int*** values_lp = new int**[hcn]; //linear probing
    int*** values_c = new int**[hcn]; //chaining
    for (int i = 0; i < hcn; i++) {
        values_lp[i] = new int*[cfn];
        values_c[i] = new int*[cfn];
        for (int j = 0; j < cfn; j++) {	        
            values_lp[i][j] = new int[2];
            values_lp[i][j][0] = 0;
            values_lp[i][j][1] = 0;
            //======================================
            values_c[i][j] = new int[2];
            values_c[i][j][0] = 0;
            values_c[i][j][1] = 0;
        }
    }
    //============================================================
    bool ft = true;
    if (ifs_p.is_open()) {
        while (ifs_p >> line) {
            //============================================================
            if (ft) {
                pl = line.length();
                cout << "Hashing (Linear Probing).\n";
                progress_bar* pb = new progress_bar(70, text.length() - pl);
                for (unsigned i = 0; i < text.length() - pl + 1; i++) {
                    for (int j = 0; j < tfn; j++) {
                        hslp[j]->insert(text.substr(i, pl));
                    }
                    pb->do_progress();
                }
               delete pb;
                //============================================================
                cout << "Hashing (Chaining).\n";
               pb = new progress_bar(70, text.length() - pl);
                for (unsigned i = 0; i < text.length() - pl + 1; i++) {
                    for (int j = 0; j < tfn; j++) {
                        hsc[j]->insert(text.substr(i, pl));
                    }
                    pb->do_progress();
                }
               delete pb;
                ft = false;
            }
            //============================================================
            for (int i = 0; i < tfn; i++) {
                pair<int, int> cont_lp = hslp[i]->contains(line);
                pair<int, int> cont_c = hsc[i]->contains(line);
                //============================================================
                values_lp[i / cfn][i % cfn][0] += cont_lp.first;
                values_lp[i / cfn][i % cfn][1] += cont_lp.second;
                //============================================================
                values_c[i / cfn][i % cfn][0] += cont_c.first;
                values_c[i / cfn][i % cfn][1] += cont_c.second;
            }
            //============================================================
            bool rehash = line.find('?') != string::npos;
            if (rehash) {
                cout << "Need to rehash since encountered a '?'.\n";
                cout << "Exiting.\n";
            }
        }
    } else {
        cout << "Could not open P.txt.";
        return 0;
    }
    ifs_p.close();
    //============================================================
    cout << "Printing.\n";
    print_values(values_lp, hcn, cfn, "Linear Probing");
    print_values(values_c, hcn, cfn, "Chaining");
    cout << "Done (Please see output folder).\n";
}
