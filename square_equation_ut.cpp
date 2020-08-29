#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define INF_ROOTS 3
#define ZERO 1.0E-20
#define DEFAULT -1


void print_intro();
void print_answer(double x1, double x2, int number_roots);
int isZero(double y);
void lin_eq(double e, double f, double* x1, int* number_roots);
void find_roots(double a, double b, double c, double* x1, double* x2, int* number_roots);
void test_isZero();
void test_lin_eq();
void test_find_roots();


int main()
    {
    test_isZero();
    test_lin_eq();
    test_find_roots();

    print_intro();

    double a = 0, b = 0, c = 0;

    while ((scanf("%lg %lg %lg", &a, &b, &c)) != 3)
        {
        printf("Try again (a, b and c must be numbers): ");
        fflush(stdin);
        }

    double x1 = 0, x2 = 0;
    int number_roots = DEFAULT;

    find_roots(a, b, c, &x1, &x2, &number_roots);

    print_answer(x1, x2, number_roots);

    return 0;
    }


//-----------------------------------------------------------------------------
//! Prints a greeting for the user
//-----------------------------------------------------------------------------


void print_intro()
    {
    printf("Square equation solver\n");

    printf("Enter coefficients: ");
    }


//-----------------------------------------------------------------------------
//! Prints an answer
//-----------------------------------------------------------------------------


void print_answer(double x1, double x2, int number_roots)
    {
    printf("Answer: ");

    switch(number_roots)
        {
        case INF_ROOTS:  printf("(-inf;+inf)");
                         break;

        case 2:          printf("%lg and %lg", x1, x2);
                         break;

        case 1:          printf("%lg", x1);
                         break;

        case 0:          printf("No roots");
                         break;

        default:         printf("ERROR");
        }

    printf("\n");
    }


//-----------------------------------------------------------------------------
//! Checks if a number is equal to zero with less precision
//!
//! @param [in]   y   number value
//!
//! @return  Returns 1 if the number is equal to zero and 0 if it is not
//-----------------------------------------------------------------------------


int isZero(double y)
    {
    return (fabs(y) <= ZERO);
    }


//-----------------------------------------------------------------------------
//! Solves a linear equation ex + f = 0
//! @param [in]      e             first coefficient
//! @param [in]      f             second coefficient
//! @param [out]     x1            root value
//! @param [out]     number_roots  number of roots
//-----------------------------------------------------------------------------


void lin_eq(double e, double f, double* x1, int* number_roots)
    {
    assert(x1 != NULL);
    assert(number_roots != NULL);

    assert(isfinite(e));
    assert(isfinite(f));

    if (!isZero(e))
        {
        *x1 = -f / e;
        *number_roots = 1;
        }

    else
        {
        if (!isZero(f))
            *number_roots = 0;

        else
            *number_roots = INF_ROOTS;
        }
    }


//-----------------------------------------------------------------------------
//! Solves a square equation ax**2 + bx + c = 0
//!
//! @param [in]      a             a-coefficient
//! @param [in]      b             b-coefficient
//! @param [in]      c             c-coefficient
//! @param [out]     x1            first root value
//! @param [out]     x2            second root value
//! @param [out]     number_roots  number of roots
//-----------------------------------------------------------------------------


void find_roots(double a, double b, double c, double* x1, double* x2, int* number_roots)
    {
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(number_roots != NULL);

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double d = 0;

    if (!isZero(a))
        {
        d = b*b - 4*a*c;

        if (d > ZERO)
            {
            *x1 = (-b + sqrt(d)) / (2*a);
            *x2 = (-b - sqrt(d)) / (2*a);
            *number_roots = 2;
            }

        else if (d < -ZERO)
            *number_roots = 0;

        else
            {
            *x1 = -b / (2*a);
            *number_roots = 1;
            }
        }

    else
        lin_eq(b, c, x1, number_roots);
    }


void test_isZero()
    {
    double enter[4] = {-1, 1e-21, 1e-20, 1};
    int must_return[4] = {0, 1, 1, 0};
    int i = 0;

    for (i = 0; i < 4; i++)
        {
        if (isZero(enter[i]) == must_return[i])
            printf("Testing isZero #%d PASSED\n", i + 1);

        else
            printf("Testing isZero #%d FAILED. isZero(%g) returned %d, should be %d", i + 1, enter[i], isZero(enter[i]), must_return[i]);
        }
    }


void test_lin_eq()
    {
    double enter_e[3] = {-1, 0, 0};
    double enter_f[3] = {2, 3, 0};

    double must_x1[3] = {2, DEFAULT, DEFAULT};
    int must_n_roots[3] = {1, 0, INF_ROOTS};

    int number_roots, i; double x1;

    for (i = 0; i < 3; i++)
        {
        x1 = number_roots = DEFAULT;

        lin_eq(enter_e[i], enter_f[i], &x1, &number_roots);

        if ((x1 == must_x1[i]) && (number_roots == must_n_roots[i]))
            printf("Testing lin_eq #%d PASSED\n", i + 1);

        else
            printf("Testing lin_eq #%d FAILED. x1 and number_roots are %g and %d, should be %g and %d\n", i + 1, x1, number_roots, must_x1[i], must_n_roots[i]);
        }
    }


void test_find_roots()
    {
    double enter_a[6] = {1, 3, 2, 0, 0, 0};
    double enter_b[6] = {3, -12, 1, 2, 0, 0};
    double enter_c[6] = {2, 12, 4, -6, 7, 0};

    double must_x1[6] = {-1, 2, DEFAULT, 3, DEFAULT, DEFAULT};
    double must_x2[6] = {-2, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT};
    int must_n_roots[6] = {2, 1, 0, 1, 0, INF_ROOTS};

    int number_roots, i; double x1, x2;

    for (i = 0; i < 6; i++)
        {
        x1 = x2 = number_roots = DEFAULT;

        find_roots(enter_a[i], enter_b[i], enter_c[i], &x1, &x2, &number_roots);

        if ((x1 == must_x1[i]) && (x2 == must_x2[i]) && (number_roots == must_n_roots[i]))
            printf("Testing find_roots #%d PASSED\n", i + 1);

        else
            printf("Testing find_roots #%d FAILED. x1, x2 and number_roots are %g, %g and %d, should be %g, %g and %d\n", i + 1, x1, x2, number_roots, must_x1[i], must_x2[i], must_n_roots[i]);
        }
    }
