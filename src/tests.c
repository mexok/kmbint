#include <assert.h>
#include <kmbint.h>

void test_add_normal()
{
        char i[20] = "12345";
        kmbint_add(i, "12");
        assert(kmbint_eq(i, "12357"));
}

void test_add_expand()
{
        char i[20] = "85";
        kmbint_add(i, "37");
        assert(kmbint_eq(i, "122"));
}

void test_add_bigger_number()
{
        char i[20] = "12";
        kmbint_add(i, "4321");
        assert(kmbint_eq(i, "4333"));
}

void test_sub()
{
        char i[20] = "12345";
        kmbint_sub(i, "1234");
        assert(kmbint_eq(i, "11111"));
}

void test_sub_borrow()
{
        char i[20] = "1000";
        kmbint_sub(i, "21");
        assert(kmbint_eq(i, "979"));
}

void test_sub_zero()
{
        char i1[20] = "65";
        char i2[20] = "0";
        kmbint_sub(i1, "0");
        kmbint_sub(i2, "0");
        assert(kmbint_eq(i1, "65"));
        assert(kmbint_eq(i2, "0"));
}

void test_sub_equal_nums()
{
        char i[20] = "1943";
        kmbint_sub(i, "1943");
        assert(kmbint_eq(i, "0"));
}

void test_mul()
{
        char i[30] = "123456789";
        kmbint_mul(i, "112233445566");
        assert(kmbint_eq(i, "13855980807984647574"));
}

void test_mul_zero()
{
        char i[20] = "5";
        kmbint_mul(i, "0");
        assert(kmbint_eq(i, "0"));
}

void test_div()
{
        char i[20] = "40000";
        kmbint_div(i, "123");
        assert(kmbint_eq(i, "325"));
}

void test_div_without_rest()
{
        char i[20] = "40000";
        kmbint_div(i, "123");
        assert(kmbint_eq(i, "325"));
}

void test_div_same()
{
        char i[20] = "12345";
        kmbint_div(i, "12345");
        assert(kmbint_eq(i, "1"));
}

void test_div_bigger()
{
        char i[20] = "123";
        kmbint_div(i, "124");
        assert(kmbint_eq(i, "0"));
}

void test_mod()
{
        char i[20] = "10987654";
        kmbint_mod(i, "12345");
        assert(kmbint_eq(i, "604"));
}

void test_mod_one()
{
        char i[20] = "700";
        kmbint_mod(i, "1");
        assert(kmbint_eq(i, "0"));
}

void test_mod_bigger()
{
        char i[20] = "567";
        kmbint_mod(i, "5782");
        assert(kmbint_eq(i, "567"));
}

void test_mod_same()
{
        char i[20] = "1234";
        kmbint_mod(i, "1234");
        assert(kmbint_eq(i, "0"));
}

void assert_cmp_greater(const char *bint, const char *to_cmp)
{
        assert(kmbint_eq(bint, to_cmp) == false);
        assert(kmbint_neq(bint, to_cmp));
        assert(kmbint_gt(bint, to_cmp));
        assert(kmbint_gte(bint, to_cmp));
        assert(kmbint_lt(bint, to_cmp) == false);
        assert(kmbint_lte(bint, to_cmp) == false);
}

void assert_cmp_equal(const char *bint, const char *to_cmp)
{
        assert(kmbint_eq(bint, to_cmp));
        assert(kmbint_neq(bint, to_cmp) == false);
        assert(kmbint_gt(bint, to_cmp) == false);
        assert(kmbint_gte(bint, to_cmp));
        assert(kmbint_lt(bint, to_cmp) == false);
        assert(kmbint_lte(bint, to_cmp));
}

void assert_cmp_lesser(const char *bint, const char *to_cmp)
{
        assert(kmbint_eq(bint, to_cmp) == false);
        assert(kmbint_neq(bint, to_cmp));
        assert(kmbint_gt(bint, to_cmp) == false);
        assert(kmbint_gte(bint, to_cmp) == false);
        assert(kmbint_lt(bint, to_cmp));
        assert(kmbint_lte(bint, to_cmp));
}

void test_cmp()
{
        assert_cmp_greater("543", "539");
        assert_cmp_greater("543", "9");
        assert_cmp_equal("543", "543");
        assert_cmp_equal("0", "0");
        assert_cmp_lesser("98", "543");
        assert_cmp_lesser("543", "544");
}

void test_cross_sum()
{
        char i[20] = "6789";
        kmbint_cross_sum(i);
        assert(kmbint_eq(i, "30"));
}

void test_cross_sum_zero()
{
        char i[20] = "0";
        kmbint_cross_sum(i);
        assert(kmbint_eq(i, "0"));
}

int main(void)
{
        test_add_normal();
        test_add_expand();
        test_add_bigger_number();
        test_sub();
        test_sub_borrow();
        test_sub_zero();
        test_sub_equal_nums();
        test_mul();
        test_mul_zero();
        test_div();
        test_div_without_rest();
        test_div_same();
        test_div_bigger();
        test_mod();
        test_mod_one();
        test_mod_same();
        test_mod_bigger();
        test_cmp();
        test_cross_sum();
        test_cross_sum_zero();
}
