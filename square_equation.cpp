#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define INF_ROOTS 3


//-----------------------------------------------------------------------------
//! Prints a greeting for the user
//-----------------------------------------------------------------------------


int print_intro()
    {
    printf("Square equation solver\n");

    printf("Enter coefficients: ");

    return 0;
    }


//-----------------------------------------------------------------------------
//! Solves a linear equation ex + f = 0
//! @param [in]      e             first coefficient
//! @param [in]      f             second coefficient
//! @param [out]     x1            root value
//! @param [out]     number_roots  number of roots
//-----------------------------------------------------------------------------


int lin_eq(double e, double f, double* x1, int* number_roots)
    {
    assert(x1 != NULL);
    assert(number_roots != NULL);

    assert(isfinite(e));
    assert(isfinite(f));

    if (e != 0)
        {
        *x1 = -f / e;
        *number_roots = 1;
        }

    else
        {
        if (f != 0)
            *number_roots = 0;

        else
            *number_roots = INF_ROOTS;
        }
    return 0;
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

int find_roots(double a, double b, double c, double* x1, double* x2, int* number_roots)
    {
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(number_roots != NULL);

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double d;

    if (a != 0)
        {
        d = b*b - 4*a*c;

        if (d > 0)
            {
            *x1 = (-b + sqrt(d)) / (2*a);
            *x2 = (-b - sqrt(d)) / (2*a);
            *number_roots = 2;
            }

        else if (d == 0)
            {
            *x1 = -b / (2*a);
            *number_roots = 1;
            }

        else
            *number_roots = 0;
        }

    else
        lin_eq(b, c, x1, number_roots);

    return 0;
    }


//-----------------------------------------------------------------------------
//! Prints an answer
//-----------------------------------------------------------------------------


int print_answer(double x1, double x2, int number_roots)
    {
    printf("Answer: ");

    switch(number_roots)
        {
        case 3:  printf("(-inf;+inf)");
                 break;

        case 2:  printf("%lg and %lg", x1, x2);
                 break;

        case 1:  printf("%lg", x1);
                 break;

        case 0:  printf("No roots");
                 break;

        case -1: printf("ERROR");
                 return 1;
        }

    printf("\n");

    return 0;
    }



int main()
    {
    print_intro();

    double a = 0, b = 0, c = 0;
    int check_input;

    if ((check_input = scanf("%lg %lg %lg", &a, &b, &c)) != 3)
        {
        printf("Error. a, b and c must be numbers");
        return 1;
        }

    double x1 = 0, x2 = 0;
    int number_roots = -1;

    find_roots(a, b, c, &x1, &x2, &number_roots);

    print_answer(x1, x2, number_roots);

    return 0;
    }


