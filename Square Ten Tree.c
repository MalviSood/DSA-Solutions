#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define DIGIT(a) ((a) - '0')
#define  CHAR(a) ((a) + '0')

char L[1000002];
char R[1000002];
char amount[1000002];

int main()
{
    int    lvls[42];
    char * amts[42] = {0};
    int    lenL, lenR, diff1, left, right, pos, groupsz, level, max, rmd, carry, i, n = 0;

    scanf("%s", L);
    scanf("%s", R);

    lenL = strlen(L);
    lenR = strlen(R);

    if (lenL < lenR)
    {
        memmove(L + lenR - lenL, L, lenL + 1);
        memset(L, '0', lenR - lenL);
        lenL = lenR;
    }

    for (i = 0; i < lenL; ++i)
        if (L[i] != R[i]) break;
    diff1 = i;

    if (diff1 >= lenL-1)
    {
        printf("1n0 %dn", 1 + R[lenR-1] - L[lenL-1]);
        return 0;
    }

    level = 0;

    if (L[lenL-1] == '0')
    {
        L[lenL-1] = '1';
        lvls[n] = level;
        amts[n] = malloc(1 + 1);
        if (amts[n] == NULL)
            return 1;
        strcpy(amts[n], "1");
        n++;
    }
    else if (L[lenL-1] != '1')
    {
        lvls[n] = level;
        amts[n] = malloc(1 + 1);
        if (amts[n] == NULL)
            return 1;
        amts[n][0] = CHAR(11 - DIGIT(L[lenL-1]));
        amts[n][1] = '';
        n++;
        for (pos = lenL-2; L[pos] == '9'; --pos)
            ;
        L[pos] += 1;
        for (i = pos+1; i < lenL; ++i)
            L[i] = '0';
    }

    groupsz = 1;
    left = right = lenL-2;

    while (diff1 < left)
    {
        level += 1;
        rmd = 0;
        max = '0';
        for (i = right; i >= left; --i)
        {
            if (L[i] > max) max = L[i];
            rmd -= DIGIT(L[i]);
            if (rmd < 0)
            {
                amount[i] = CHAR(rmd + 10);
                rmd = -1;
            }
            else
            {
                amount[i] = CHAR(rmd);
                rmd = 0;
            }
        }

        if (max > '0')
        {
            for (pos = left-1; L[pos] == '9'; --pos)
                ;
            L[pos] += 1;
            for (i = pos+1; i <= right; ++i)
                L[i] = '0';

            lvls[n] = level;
            amts[n] = malloc(groupsz + 1);
            if (amts[n] == NULL)
                return 1;
            memcpy(amts[n], &amount[left], groupsz);
            amts[n][groupsz] = '';
            n++;
        }

        right -= groupsz;
        groupsz *= 2;
        left = MAX(0, right - groupsz + 1);
    }

    /* take truncated/diff group */
    level += 1;
    rmd = 0;
    max = '0';
    for (i = right; i >= left; --i)
    {
        rmd += R[i] - L[i];
        if (rmd < 0)
        {
            amount[i] = CHAR(rmd + 10);
            rmd = -1;
        }
        else
        {
            amount[i] = CHAR(rmd);
            rmd = 0;
        }

        if (amount[i] > max) max = amount[i];
    }

    if (max > '0')
    {
        lvls[n] = level;
        amts[n] = malloc(right + 1 - left + 1);
        if (amts[n] == NULL)
            return 1;
        memcpy(amts[n], &amount[left], right + 1 - left);
        amts[n][right+1-left] = '';
        n++;
    }

    left = right + 1;
    groupsz /= 2;
    right = left + groupsz - 1;

    while (left < lenR-1)
    {
        level -= 1;
        max = '0';
        for (i = left; i <= right; ++i)
            if (R[i] > '0') max = R[i];

        if (max > '0')
        {
            if (lvls[n-1] == level)
            {
                /* add amount to amts[n-1] */
                carry = 0;
                for (i = right; i >= left; --i)
                {
                    carry += DIGIT(R[i]) + DIGIT(amts[n-1][i-left]);
                    if (carry >= 10)
                    {
                        amount[i] = CHAR(carry - 10);
                        carry = 1;
                    }
                    else
                    {
                        amount[i] = CHAR(carry);
                        carry = 0;
                    }
                }
                if (carry)
                {
                    amount[i] = '1';
                    free(amts[n-1]);
                    amts[n-1] = malloc(1 + groupsz + 1);
                    if (amts[n-1] == NULL)
                        return 1;
                    memcpy(amts[n-1], &amount[i], 1 + groupsz);
                    amts[n-1][1+groupsz] = '';
                }
                else
                {
                    memcpy(amts[n-1], &amount[left], groupsz);
                }
            }
            else
            {
                lvls[n] = level;
                amts[n] = malloc(groupsz + 1);
                if (amts[n] == NULL)
                    return 1;
                memcpy(amts[n], &R[left], groupsz);
                amts[n][groupsz] = '';
                n++;
            }
        }

        left = right + 1;
        groupsz /= 2;
        right = left + groupsz - 1;
    }

    if (R[lenR-1] > '0')
    {
        level = 0;
        if (lvls[n-1] == level)
        {
            /* add amount to amts[n-1] */
            carry = DIGIT(R[lenR-1]) + DIGIT(amts[n-1][0]);
            if (carry >= 10)
            {
                free(amts[n-1]);
                amts[n-1] = malloc(2 + 1);
                if (amts[n-1] == NULL)
                    return 1;
                sprintf(amts[n-1], "%d", carry);
            }
            else
            {
                amts[n-1][0] = CHAR(carry);
            }
        }
        else
        {
            lvls[n] = level;
            amts[n] = malloc(1 + 1);
            if (amts[n] == NULL)
                return 1;
            amts[n][0] = R[lenR-1];
            amts[n][1] = '';
            n++;
        }
    }

    printf("%dn", n);
    for (i = 0; i < n; ++i)
    {
        for (left = 0; amts[i][left] == '0'; ++left)
            ;
        printf("%d %sn", lvls[i], &amts[i][left]);
    }

    return 0;
}