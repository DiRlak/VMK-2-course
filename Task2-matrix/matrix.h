
typedef struct {
    double **mtrx;
    int n, m;
} matrix;


int init_mtrx(matrix *mtrx, const int n, const int m);

int outp_mtrx(const matrix *mtrx);

void del_mtrx(matrix *mtrx);


int add_mtrx(matrix *mtrx1, const matrix *mtrx2);

int mul_num_mtrx(matrix *mtrx, const double a);

matrix mul_mtrx(const matrix *mtrx1, const matrix *mtrx2);

double det_mtrx(const matrix *mtrx);
