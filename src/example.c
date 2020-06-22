#include <stdio.h>
#include <kmbint.h>


int main(void)
{
        char i[20] = "20";

        kmbint_add(i, "50");
        printf("20 + 50 = %s\n", i);

        kmbint_sub(i, "15");
        printf("70 - 15 = %s\n", i);

        kmbint_mul(i, "20");
        printf("55 * 20 = %s\n", i);

        kmbint_div(i, "100");
        printf("1100 / 100 = %s\n", i);

        return 0;
}
