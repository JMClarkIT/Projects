#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fibonacci.h"

// This function creates a new HugeInteger array to store the results
// of adding HugeIntegers p and q.
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    if (p == NULL || q == NULL)
        return NULL;

    int i, counter = 0;
    HugeInteger *total = malloc(sizeof(HugeInteger));
    if (total == NULL)
        return NULL;

    // The new array is made slightly larger than necessary.
    if (p->length > q->length)
        total->digits = calloc(p->length + 5, sizeof(int));
    else
        total->digits = calloc(q->length + 5, sizeof(int));
    if (total->digits == NULL)
    {
        free(total);
        return NULL;
    }

    // To add the two HugeInteger arrays, each index in each array have to be
    // added to one another. The extra space in the new array is there just in case
    // adding two numbers produces a double digit number.
    if (p->length > q->length)
    {
        for (i = 0; i < q->length; i++)
        {
            total->digits[i] = total->digits[i] + q->digits[i] + p->digits[i];
            if (total->digits[i] > 9)
            {
                total->digits[i + 1] = total->digits[i] / 10;
                total->digits[i] = total->digits[i] % 10;
            }
            if (total->digits[p->length])
                counter++;
            counter++;
            }
            for (i = q->length; i < p->length; i++)
            {
                total->digits[i] += p->digits[i];
                if (total->digits[i] > 9)
                {
                    total->digits[i + 1] = total->digits[i] / 10;
                    total->digits[i] = total->digits[i] % 10;
                }
                if (total->digits[p->length])
                    counter++;
                counter++;
            }
            total->length = counter;
        }
        else
        {
            for (i = 0; i < p->length; i++)
            {
                total->digits[i] = total->digits[i] + q->digits[i] + p->digits[i];
                if (total->digits[i] > 9)
                {
                    total->digits[i + 1] = total->digits[i] / 10;
                    total->digits[i] = total->digits[i] % 10;
                }
                if (total->digits[q->length])
                    counter++;
                counter++;
            }
            total->length = counter;
        }
        return total;
}

// Free all dynamically allocated memory associated with p.
HugeInteger *hugeDestroyer(HugeInteger *p)
{
    if (p == NULL)
        return NULL;
    else
    {
        free(p->digits);
        free(p);
        return NULL;
    }
}

// The parseString function converts a number from string format into HugeInteger format.
// Empty strings that are passed to this function are treated as "0".
HugeInteger *parseString(char *str)
{
    if (str == NULL)
        return NULL;

    int i, wlen = strlen(str);
    HugeInteger *newArray = malloc(sizeof(HugeInteger));
    if (newArray == NULL)
        return NULL;

    newArray->digits = calloc(wlen, sizeof(int));

    for (i = 0; i < wlen; i++)
    {
        newArray->digits[i] = (str[wlen - 1 - i]) - '0';
    }
    newArray->length = wlen;
    if (newArray->digits == NULL)
    {
        free(newArray);
        return NULL;
    }
    else if (newArray != NULL)
    {
        return newArray;
    }
    else
        return NULL;
}

// Convert an unsigned integer into HugeInteger format.
HugeInteger *parseInt(unsigned int n)
{
    int i, ticker = 0;
    unsigned int temp = n;
    HugeInteger *newArray = malloc(sizeof(HugeInteger));

    if (newArray == NULL)
        return NULL;

    if (temp != 0)
    {
        for (i = 0;;i++)
        {
            if (temp == 0)
            {
                break;
            }
            temp = temp / 10;
            ticker++;
        }
    } else
        ticker = 1;

    newArray->digits = calloc(ticker, sizeof(int));

    if (newArray->digits == NULL)
    {
        free(newArray);
        return NULL;
    }

    if (n != 0)
    {
        for (i = 0; i < ticker; i++)
        {
            newArray->digits[i] = n % 10;
            n /= 10;
        }
    } else
        newArray->digits[0] = 0;

    newArray->length = ticker;
    return newArray;
}

// Convert the integer p to a dynamically allocated unsigned int. If p exceeds
// the max value that an unsigned int can represent, simply return NULL.
unsigned int *toUnsignedInt(HugeInteger *p)
{
    if(p == NULL)
        return NULL;
    int i;
    unsigned int *num = NULL, t = 1;
    unsigned long long int *lnum = NULL, longt = 1;

    num = malloc(sizeof(unsigned int));
    lnum = malloc(sizeof(unsigned long long int));

    *num = 0;
    *lnum = 0;

    for(i = 0; i < p->length; i++)
    {
        *lnum += p->digits[i] * longt;
        *num += p->digits[i] * t;
        longt *= 10;
        t *= 10;
    }
    if(*lnum > UINT_MAX)
    {
        free(num);
        free(lnum);
        return NULL;
    }
    free(lnum);
    if(num != NULL)
        return num;
    else
        return NULL;
}

// This is an O(n) function to compute the Fibonacci sequence. This function only holds few numbers
// in memory at a time so that when large values of n are computed, it doesn't take up lots of memory.
HugeInteger *fib(int n)
{
    HugeInteger *a = NULL;
    HugeInteger *b = NULL;
    HugeInteger *c = NULL;
    HugeInteger *results = NULL;
    int i, ticker = -1;

    a = parseInt(1);
    b = parseInt(2);
    c = parseInt(3);

    if (n == 0)
        return parseInt(0);
    else if (n == 1 || n == 2)
        return parseInt(1);

    for (i = 0; i < n; i++)
    {
        if (i <= 2)
        {
            ticker++;
            continue;
        }
        if (i % 3 == 0)
        {
            c = hugeAdd(b, a);
            hugeDestroyer(a);
            ticker++;
        }
        if (i % 3 == 1)
        {
            a = hugeAdd(c, b);
            hugeDestroyer(b);
            ticker++;
        }
        if (i % 3 == 2)
        {
            b = hugeAdd(a, c);
            hugeDestroyer(c);
            ticker++;
        }
    }

    if (ticker % 3 == 0)
    {
        results = c;
    }
    else if (ticker % 3 == 1)
    {
        results = a;
    }
    else if (ticker % 3 == 2)
    {
        results = b;
    }
    return results;
}

double difficultyRating(void)
{
    return 3.5;
}

double hoursSpent(void)
{
    return 25.0;
}
