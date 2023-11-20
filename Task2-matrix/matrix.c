#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int init_mtrx(matrix *mtrx, const int n, const int m) {
    mtrx->n = n; mtrx->m = m;

    mtrx->mtrx = (double **) malloc(sizeof(double *)*n);
    for (int i = 0; i < n; ++i)
        mtrx->mtrx[i] = (double *) malloc(sizeof(double)*m);

    printf("Enter a matrix with %d rows and %d columns\n", n, m);
    for (int i  = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (scanf("%lf", &(mtrx->mtrx[i][j])) != 1) {
                printf("Invalid input\n");
                del_mtrx(mtrx);
                return -1;
            }
    return 0;
}

int outp_mtrx(const matrix *mtrx) {
    if (mtrx->mtrx == NULL) {
       printf("Unexisting matrix can not be printed\n");
       return -2;
    }

    for (int i = 0; i < mtrx->n; ++i) {
        for (int j = 0; j < mtrx->m; ++j)
            printf("%lf ", mtrx->mtrx[i][j]);
        printf("\n");
    }
    return 0;
}

void del_mtrx(matrix *mtrx) {
    if (mtrx->mtrx == NULL) {
       mtrx->n = mtrx->m = 0;
       return;
    }

    for (int i = 0; i < mtrx->n; ++i) free(mtrx->mtrx[i]);
    free(mtrx->mtrx); mtrx->mtrx = NULL;
    mtrx->n = mtrx->m = 0;
    return;
}


int add_mtrx(matrix *mtrx1, const matrix *mtrx2) {
    if ((mtrx1->n != mtrx2->n) || (mtrx1->m != mtrx2->m)) {
        printf("Addition can not be calculated: inappropriate size of matrices\n");
        return -1;
    }

    if ((mtrx1->mtrx == NULL) || (mtrx2->mtrx == NULL)) {
        printf("Addition can not be calculated: one of matrices is not existed\n");
        return -2;
    }


    for (int i = 0; i < mtrx1->n; ++i)
        for (int j = 0; j < mtrx1->m; ++j)
            mtrx1->mtrx[i][j] += mtrx2->mtrx[i][j];
    return 0;
}

int mul_num_mtrx(matrix *mtrx, const double a) {
    if (mtrx->mtrx == NULL) {
        printf("Unexisting matrix can not be multiplied with any number\n");
        return -2;
    }

    for (int i = 0; i < mtrx->n; ++i)
        for (int j = 0; j < mtrx->m; ++j)
            mtrx->mtrx[i][j] *= a;
    return 0;
}

matrix mul_mtrx(const matrix *mtrx1, const matrix *mtrx2) {
    matrix tmp;
    tmp.n = 0; tmp.m = 0;
    tmp.mtrx = NULL;

    if (mtrx1->m != mtrx2->n) {
        printf("Matrices %dx%d and %dx%d can not be multiplied\n", mtrx1->n, mtrx1->m, mtrx2->n, mtrx2->m);
        return tmp;
    }

    if ((mtrx1->mtrx == NULL) || (mtrx2->mtrx == NULL)) {
        printf("Multipling can not be calculated: one of matrices is not existed\n");
        return tmp;
    }

    tmp.n = mtrx1->n; tmp.m = mtrx2->m;
    tmp.mtrx = (double **) malloc(sizeof(double *)*tmp.n);
    for (int i = 0; i < tmp.n; ++i)
        tmp.mtrx[i] = (double *) malloc(sizeof(double)*tmp.m);

    for (int i = 0; i < mtrx1->n; ++i)
        for (int k = 0; k < mtrx2->m; ++k) {
            tmp.mtrx[i][k] = 0;
            for (int j = 0; j < mtrx1->m; ++j) {
                tmp.mtrx[i][k] += mtrx1->mtrx[i][j]*mtrx2->mtrx[j][k];
            }
        }

    return tmp;
}

double det_mtrx(const matrix *mtrx) {
    if (mtrx->n != mtrx->m) {
        printf("Determinant of %dx%d matrix can not be calculated\n", mtrx->n, mtrx->m);
        return 0;
    }

    if (mtrx->mtrx == NULL) {
       printf("Determinant of 0x0 matrix can not be calculated\n");
       return 0;
    }

    if (mtrx->n == 1) return mtrx->mtrx[0][0];

    if (mtrx->n == 2)
       return mtrx->mtrx[0][0]*mtrx->mtrx[1][1]-mtrx->mtrx[0][1]*mtrx->mtrx[1][0];

    matrix tmp;
    tmp.n = tmp.m = mtrx->n-1;
    tmp.mtrx = (double **) malloc(sizeof(double *)*tmp.n);
    for (int i = 0; i < tmp.n; ++i)
        tmp.mtrx[i] = (double *) malloc(sizeof(double)*tmp.m);

    double s = 0;
    int p = 0;
    for (int i = 0; i < mtrx->n; ++i) {
        p = p%tmp.n;
        for (int k = 0; k < mtrx->n; ++k) {
            if (k == i) continue;
            for (int j = 1; j < mtrx->m; ++j)
                tmp.mtrx[p][j-1] = mtrx->mtrx[k][j];
            ++p;
        }

        s += i%2 == 0 ? mtrx->mtrx[i][0]*det_mtrx(&tmp) : -(mtrx->mtrx[i][0]*det_mtrx(&tmp));
    }

    del_mtrx(&tmp);
    return s;
}

