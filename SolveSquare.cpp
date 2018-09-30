//! @file

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define SE_INF_ROOTS -1

//-----------------------------------------------
//! Solves a linear equation ax + b = 0
//!
//! @param [in]  a  a - coefficient
//! @param [in]  b  b - coefficient
//! @param [out] x  Pointer to the root
//!
//! @return Number of roots
//!
//! @note   in case of infinity number of roots,
//!         returns SE_INF_ROOTS
//-----------------------------------------------

int SolveLinear(double a, double b, double * x) {
    assert(!isnan(a));
    assert(!isnan(b));
    
    assert(x != NULL);

    if(a == 0) {
        if(b == 0) {
            *x = NAN;
            return SE_INF_ROOTS;
        } else {
            *x = NAN;
            return 0;
        }
    }
    
    *x = b / a;
    
    return 1;
}

//-----------------------------------------------
//! Solves a linear equation ax^2 + bx + c = 0
//!
//! @param [in]  a  a - coefficient
//! @param [in]  b  b - coefficient
//! @param [in]  c  c - coefficient
//! @param [out] x1  Pointer to the 1st root
//! @param [out] x2  Pointer to the 2st root
//!
//! @return Number of roots
//!
//! @note   in case of infinity number of roots,
//!         returns SE_INF_ROOTS
//-----------------------------------------------

int SolveSquare(double a, double b, double c, double * x1, double * x2) {
    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if(a == 0) {
        *x2 = NAN;
        return SolveLinear(b, c, x1);
    }
    
    double D = b * b - 4 * a * c;

    if(D == 0.0) {
        *x1 = - b / (2 * a);
        *x2 = NAN;
        return 1; 
    }

    *x1 = (- b - sqrt(D)) / (2 * a);
    *x2 = (- b + sqrt(D)) / (2 * a);

    return 2;
}

int main() {
    printf("# Square equation solver v.0.1 (c) Pupin Schneider\n\n");
    
    printf("# Enter a b c : ");

    double a = NAN, b = NAN, c = NAN;

    while(scanf("%lg %lg %lg", &a, &b, &c) != 3) {
        scanf("%*[^\n]");
        printf("# Enter three real numbers, a b c : ");
    }

    assert(!isnan(a));
    assert(!isnan(b));
    assert(!isnan(c));

    double x1 = NAN, x2 = NAN;

    int nRoots = SolveSquare(a, b, c, &x1, &x2);

    switch(nRoots) {
        case 0:
            printf("# No real roots\n");
            break;
        case 1:
            printf("# One real root x = %lg\n", x1);
            break;
        case 2:
            printf("# Two real roots x1 = %lg, x2 = %lg\n", x1, x2);
            break;
        case SE_INF_ROOTS:
            printf("# Infinity number of roots\n");
            break;
        default:
            assert(false);
            break;
    }
    
    return 0;
}
