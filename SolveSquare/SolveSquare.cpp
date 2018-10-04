//! @file

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#define SE_INF_ROOTS -2

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
    if(!isfinite(a) || !isfinite(b)) {
        return -1;
    }

    if(!x) {
        return -1;
    }

    if(a == 0) {
        if(b == 0) {
            *x = NAN;
            return SE_INF_ROOTS;
        } else {
            *x = NAN;
            return 0;
        }
    }
    
    *x = -b / a;

    if(*x == -0.0) *x = 0.0;
    
    if(!isfinite(*x)) {
        return -1;
    }

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
    if(!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return -1;
    }

    if(!x1 || !x2 || x1 == x2) {
        return -1;
    }

    if(a == 0) {
        *x2 = NAN;
        return SolveLinear(b, c, x1);
    }
    
    double D = b * b - 4 * a * c;

    if(D == 0) {
        *x1 = - b / (2 * a);
        if(*x1 == -0.0) *x1 = 0.0;
        *x2 = NAN;
        
        if(!isfinite(*x1)) {
            return -1;
        }
        
        return 1; 
    }
    
    if(D < 0) {
        *x1 = NAN;
        *x2 = NAN;
        return 0;
    }

    *x1 = (- b - sqrt(D)) / (2 * a);
    *x2 = (- b + sqrt(D)) / (2 * a);

    if(*x1 == -0.0) *x1 = 0.0;
    if(*x2 == -0.0) *x2 = 0.0;

    if(!isfinite(*x1) || !isfinite(*x2)) {
        return -1;
    }

    return 2;
}

int runTestSolveSquare(double a, double b, double c, int wnRoots, double wx1, double wx2) {
    double x1 = NAN, x2 = NAN;
    int nRoots = 0;
    
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    nRoots = SolveSquare(a, b, c, &x1, &x2);

    //printf("# a = %lg, b = %lg, c = %lg\n# Waited : nRoots = %d, x1 = %lg, x2 = %lg\n# Return : nRoots = %d, x1 = %lg, x2 = %lg\n", a, b, c, wnRoots, wx1, wx2, nRoots, x1, x2);

    if(((x1 == wx1) || (!isfinite(x2) && !isfinite(wx2))) && ((wx2 == x2) \
    || (!isfinite(x2) && !isfinite(wx2))) && nRoots == wnRoots && nRoots != -1) {
        //printf("# OK\n\n");
        return 0;
    }

    //printf("# ERROR\n\n");
    return 1;
}

int testSolveSquare() {
    if(runTestSolveSquare(0.0, 0.0, 0.0, SE_INF_ROOTS, NAN, NAN) == 1) return 1;
    if(runTestSolveSquare(0.0, 0.0, 1.0, 0, NAN, NAN) == 1) return 1;
    if(runTestSolveSquare(1.0, 2.0, 1.0, 1, -1.0, NAN) == 1) return 1;
    if(runTestSolveSquare(1.0, 3.0, 2.0, 2, -2.0, -1.0) == 1) return 1;
    if(runTestSolveSquare(0.0, 2.0, 0.0, 1, 0.0, NAN) == 1) return 1;
    if(runTestSolveSquare(1.0, 1.0, 0.0, 2, -1.0, 0.0) == 1) return 1;
    if(runTestSolveSquare(0.0, 1.0, 1.0, 1, -1.0, NAN) == 1) return 1;

    return 0;
}

int main() {

    assert(!testSolveSquare());

    printf("# Square equation solver v.0.1 (c) Pupin Schneider\n\n");
    
    printf("# Enter a b c : ");

    double a = NAN, b = NAN, c = NAN;

    while(scanf("%lg %lg %lg", &a, &b, &c) != 3 || !isfinite(a) || !isfinite(b) || !isfinite(c)) {
        scanf("%*[^\n]");
        perror("Wrong input");
        printf("# Enter three real numbers, a b c : ");
    }

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
            printf("# SolveSquareError\n");
            break;
    }
    
    return 0;
}
