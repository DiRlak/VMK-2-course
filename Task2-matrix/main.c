#include <stdio.h>
#include "matrix.h"

#define N 2
#define M 2

int main() {
    matrix a;
//    matrix b;
    init_mtrx(&a, 4, 4);
//    init_mtrx(&b, 3, 3);

//    add_mtrx(&a, &b);
//    mul_num_mtrx(&a, -10);
//    matrix c = mul_mtrx(&a, &b);
//    outp_mtrx(&c);

    double det = det_mtrx(&a);

    printf("%lf\n", det);

    del_mtrx(&a);
//    del_mtrx(&b);
//    del_mtrx(&c);

    return 0;
}
