#include <stdio.h>
#include <math.h>

int find_roots(double a, double b, double c, double* x1, double* x2, int* number)
    {
    double d;

    if (a !=0)
        {
        d = b*b - 4*a*c;

        if (d>0)
            {
            *x1 = (-b + sqrt(d))/(2*a);
            *x2 = (-b - sqrt(d))/(2*a);
            *number = 2;
            }

        else if (d==0)
            {
            *x1 = -b/(2*a);
            *number = 1;
            }

        else
            *number = 0;
        }

    else
        {
        if (b !=0)
            {
            *x1 = -c/b;
            *number = 1;
            }

        else
            {
            if (c !=0)
                *number = 0;

            else
                *number = 3;
            }
        }

    return 0;
    }


int print_answer(double x1, double x2, int number)
    {
    printf("Answer: ");

    switch(number)
        {
        case 3: printf("(-inf;+inf)");
                break;

        case 2: printf("%lg and %lg", x1, x2);
                break;

        case 1: printf("%lg", x1);
                break;

        case 0: printf("No roots");
                break;

        case -1: printf("ERROR");
                break;
        }

    printf("\n");

    return 0;
    }


int main()
    {
    printf("Square equation solver\n");

    printf("Enter coefficients: ");

    double a = 0, b = 0, c = 0;
    scanf("%lg %lg %lg", &a, &b, &c);

    double x1 = 0, x2 = 0;
    int number = -1;

    find_roots(a, b, c, &x1, &x2, &number);

    print_answer(x1, x2, number);
    }






