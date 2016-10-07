#include <iomanip>
#include <string>
#include <sstream>

static const int P_W = 60;

void print_values(int*** values, int hcn, int cfn, string title) {
    std::ofstream ofs;
    ofs << title << ".\n";
    string fn = "../output/2015csb1003Output" + title + ".txt";
    ofs.open(fn.c_str());
    ofs << std::string((1 + cfn) * (P_W + 2), '=') << "\n";
    ofs << "|" << std::setw(P_W) << "" << "||" << std::setw(P_W) << "Division" << "||" << std::setw(P_W) << "MAD"
            << "||" << std::setw(P_W) << "Multiplication" << "|\n";
    ofs << std::string((1 + cfn) * (P_W + 2), '=') << "\n";
    for (int i = 0; i < hcn; i++) {
        std::string hash_code_type;
        switch (i) {
            case 0:
                hash_code_type = "Integer Casting";
                break;
            case 1:
                hash_code_type = "Component Sum";
                break;
            case 2:
                hash_code_type = "Polynomial Sum";
                break;
            case 3:
                hash_code_type = "Cyclic Sum";
                break;
        }
        ofs << "|" << std::setw(P_W) << hash_code_type << "|";
        for (int j = 0; j < cfn; j++) {
            std::stringstream ss;
            ss << "False Positive(s) = " << values[i][j][0] << ", String Compare(s) = " << values[i][j][1];
            ofs << "|" << std::setw(P_W) << ss.str() << "|";
        }
        ofs << "\n";
    }
    ofs << std::string((1 + cfn) * (P_W + 2), '=') << "\n";
    ofs.close();
}
