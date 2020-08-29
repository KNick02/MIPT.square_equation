#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define INF_ROOTS 3
#define ZERO 1.0E-20

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
    if ((y > ZERO) || (y < -ZERO))
        return 0;

    else
        return 1;
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

    if (isZero(e) == 0)
        {
        *x1 = -f / e;
        *number_roots = 1;
        }

    else
        {
        if (isZero(f) == 0)
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

    if (isZero(a) == 0)
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


int main()
    {
    print_intro();

    double a = 0, b = 0, c = 0;

    while ((scanf("%lg %lg %lg", &a, &b, &c)) != 3)
        {
        printf("Try again (a, b and c must be numbers): ");
        fflush(stdin);
        }

    double x1 = 0, x2 = 0;
    int number_roots = -1;

    find_roots(a, b, c, &x1, &x2, &number_roots);

    print_answer(x1, x2, number_roots);

    return 0;
    }



