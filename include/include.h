#include <math.h>
#include <string>

#define abs(x) ((x>0)?x:-x)

int integer_casting(std::string);
int component_sum(std::string);
int polynomial_sum(std::string);
int cyclic_sum(std::string);

int division(int);
int mad(int);
int multiplication(int);

void print_values(int***, int, int);

static const int _N = (1 << 17) - 1;
static const int _A = 3;
static const int _B = 5;
static const double A = (sqrt(5.0) - 1.0) / 2.0;

typedef int (*hash_code_fxn_ptr)(std::string);
typedef int (*compression_fxn_ptr)(int);
