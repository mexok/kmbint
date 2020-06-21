#include <string.h>
#include <assert.h>
#include <kmbint.h>

typedef void (*divide_fn_t)(char *rest_num, size_t len_rest_num, char **divs, size_t len_divs, char *bint_out);

void kmbint_add(char *bint, const char *to_add)
{
        size_t len_bint = strlen(bint);
        size_t len_to_add = strlen(to_add);
        if (len_to_add > len_bint) {
                size_t len_to_zero_fill = len_to_add - len_bint;
                memmove(bint + len_to_zero_fill, bint, len_bint + 1);
                memset(bint, '0', len_to_zero_fill);
                len_bint += len_to_zero_fill;
        }

        const char *p_to_add = to_add + len_to_add;
        char remainder = 0;
        char *p_bint = bint + len_bint;

        while (p_to_add != to_add) {
                --p_to_add;
                --p_bint;
                *p_bint += remainder + (*p_to_add - '0');
                if (*p_bint > '9') {
                        *p_bint -= 10;
                        remainder = 1;
                } else {
                        remainder = 0;
                }
        }
        if (remainder > 0) {
                memmove(bint + 1, bint, len_bint + 1);
                bint[0] = '1';
        }
}

void kmbint_sub(char *bint, const char *to_diff)
{
        assert(kmbint_gte(bint, to_diff));

        size_t len_bint = strlen(bint);
        size_t len_to_diff = strlen(to_diff);

        char *p_bint = bint + len_bint;
        const char *p_to_diff = to_diff + len_to_diff;
        char borrowed = 0;

        while (p_to_diff != to_diff) {
                --p_to_diff;
                --p_bint;
                if (*p_bint < *p_to_diff + borrowed) {
                        *p_bint = *p_bint + 10 - *p_to_diff - borrowed + '0';
                        borrowed = 1;
                } else {
                        *p_bint = *p_bint - *p_to_diff - borrowed + '0';
                        borrowed = 0;
                }
        }

        while (borrowed == 1) {
                --p_bint;
                if (*p_bint == '0') {
                        *p_bint = '9';
                } else {
                        --*p_bint;
                        borrowed = 0;
                }
        }

        p_bint = bint;
        size_t num_leading_zeros = 0;
        while (*p_bint == '0') {
                ++num_leading_zeros;
                ++p_bint;
        }
        if (num_leading_zeros == len_bint) {
                --num_leading_zeros;
        }
        len_bint -= num_leading_zeros;
        memmove(bint, bint + num_leading_zeros, len_bint + 1);
}

static void subtract_zero_char_value(char *bint)
{
        while (*bint != '\0') {
                *bint -= '0';
                ++bint;
        }
}

static void multiply_buffer(char *buffer, size_t len_buffer, char to_mul)
{
        char remainder = 0;
        buffer += len_buffer;
        while (true) {
                --buffer;
                *buffer = *buffer * to_mul + remainder;
                remainder = *buffer / 10;
                *buffer %= 10;
                if (len_buffer > 0) {
                        --len_buffer;
                } else {
                        break;
                }
        }
}

static void add_buffer(char *buffer, const char *to_add, size_t len_buffer)
{
        buffer += len_buffer;
        to_add += len_buffer;
        char remainder = 0;
        while (len_buffer > 0) {
                --buffer;
                --to_add;
                *buffer += *to_add + remainder;
                if (*buffer >= 10) {
                        *buffer -= 10;
                        remainder = 1;
                } else {
                        remainder = 0;
                }
                --len_buffer;
        }
}

static void sub_buffer(char *buffer, const char *to_sub, size_t len_buffer)
{
        buffer += len_buffer;
        to_sub += len_buffer;
        char borrow = 0;
        while (len_buffer-- > 0) {
                *--buffer -= *--to_sub + borrow;
                if (*buffer < 0) {
                        *buffer += 10;
                        borrow = 1;
                } else {
                        borrow = 0;
                }
        }
}

void kmbint_mul(char *bint, const char *to_mul)
{
        size_t len_bint = strlen(bint);
        size_t len_to_mul = strlen(to_mul);
        size_t len_buffer = len_bint + len_to_mul;

        subtract_zero_char_value(bint);

        char result_buffer[len_buffer];
        memset(result_buffer, 0, len_buffer);

        const char *p_to_mul = to_mul + len_to_mul;

        char to_add_buffer[len_buffer];
        char *p_to_insert_num = to_add_buffer + len_to_mul + 1;
        char mul;

        while (to_mul != p_to_mul) {
                --p_to_mul;
                --p_to_insert_num;
                mul = *p_to_mul - '0';
                if (mul > 0) {
                        memset(to_add_buffer, 0, len_buffer);
                        memcpy(p_to_insert_num, bint, len_bint);
                        if (mul > 1) {
                                multiply_buffer(to_add_buffer, len_buffer, mul);
                        }
                        add_buffer(result_buffer, to_add_buffer, len_buffer);
                }
        }

        char *p_result = result_buffer;
        while (len_buffer > 0) {
                if (*p_result == 0) {
                        ++p_result;
                        --len_buffer;
                } else {
                        break;
                }
        }
        if (len_buffer == 0) {
                bint[0] = '0';
                bint[1] = '\0';
        } else {
                while (len_buffer > 0) {
                        *bint = *p_result + '0';
                        bint++;
                        ++p_result;
                        --len_buffer;
                }
                *bint = '\0';
        }
}

static bool check_divider(char *num, size_t num_len, char *div)
{
        while (num_len > 0) {
                if (*num > *div) {
                        return true;
                } else if (*num < *div) {
                        return false;
                }
                ++num;
                ++div;
                --num_len;
        }
        return true;
}

static char find_divider_mul(char *num, size_t num_len, char **divs)
{
        if (check_divider(num, num_len, divs[4])) {
                if (check_divider(num, num_len, divs[6])) {
                        if (check_divider(num, num_len, divs[7])) {
                                if (check_divider(num, num_len, divs[8])) {
                                        return 9;
                                } else {
                                        return 8;
                                }
                        } else {
                                return 7;
                        }
                } else {
                        if (check_divider(num, num_len, divs[5])) {
                                return 6;
                        } else {
                                return 5;
                        }
                }
        } else {
                if (check_divider(num, num_len, divs[2])) {
                        if (check_divider(num, num_len, divs[3])) {
                                return 4;
                        } else {
                                return 3;
                        }
                } else {
                        if (check_divider(num, num_len, divs[0])) {
                                if (check_divider(num, num_len, divs[1])) {
                                        return 2;
                                } else {
                                        return 1;
                                }
                        } else {
                                return 0;
                        }
                }

        }
}

static void setup_buffer_from_num(char *buffer, const char *num, size_t len_num)
{
        while (len_num > 0) {
                *buffer++ = *num++ - '0';
                --len_num;
        }
}

static void divide_fn_impl_default(char *rest_num, size_t len_rest_num, char **divs, size_t len_divs, char *bint_out)
{
        bool is_bint_started = false;
        while (len_rest_num > len_divs) {
                char mul = find_divider_mul(rest_num, len_divs, divs);

                if (mul > 0) {
                        is_bint_started = true;
                        *bint_out++ = mul + '0';
                        sub_buffer(rest_num, divs[mul - 1], len_divs);
                } else if (is_bint_started) {
                        *bint_out++ = '0';
                }
                ++rest_num;
                --len_rest_num;
        }
        if (len_rest_num < len_divs) {
                *bint_out++ = '0';
        } else {
                char mul = find_divider_mul(rest_num, len_divs, divs);
                *bint_out++ = '0' + mul;
        }
        *bint_out = '\0';
}

static void divide(char *bint, const char *to_div, divide_fn_t divide_fn)
{
        size_t len_bint = strlen(bint);
        size_t len_to_div = strlen(to_div);

        // The len of the dividers can be at max 1 digit bigger then the original number
        size_t len_divs = len_to_div + 1;
        char div_data[9 * len_divs];
        char *divs[9];
        divs[0] = div_data;
        setup_buffer_from_num(divs[0] + 1, to_div, len_to_div);
        divs[0][0] = 0;

        for (int i = 1; i < 9; ++i) {
                divs[i] = &div_data[i * len_divs];
                memcpy(divs[i], divs[i - 1], len_divs);
                add_buffer(divs[i], divs[0], len_divs);
        }

        // rest_num must always start with zero to work correctly
        char rest_num[len_bint + 1];
        rest_num[0] = 0;
        setup_buffer_from_num(rest_num + 1, bint, len_bint);
        divide_fn(rest_num, len_bint + 1, divs, len_divs, bint);
}

void kmbint_div(char *bint, const char *to_div)
{
        assert(kmbint_gt(to_div, "0"));
        divide(bint, to_div, divide_fn_impl_default);
}

static void divide_fn_impl_mod(char *rest_num, size_t len_rest_num, char **divs, size_t len_divs, char *bint_out)
{
        while (len_rest_num >= len_divs) {
                char mul = find_divider_mul(rest_num, len_divs, divs);
                if (mul > 0) {
                        sub_buffer(rest_num, divs[mul - 1], len_divs);
                }
                ++rest_num;
                --len_rest_num;
        }
        bool is_bint_started = false;
        while (len_rest_num > 0) {
                if (*rest_num > 0) {
                        is_bint_started = true;
                        *bint_out++ = *rest_num + '0';
                } else if (is_bint_started) {
                        *bint_out++ = '0';
                }

                ++rest_num;
                --len_rest_num;
        }
        if (is_bint_started == false) {
                *bint_out++ = '0';
        }
        *bint_out = '\0';
}

void kmbint_mod(char *bint, const char *to_mod)
{
        assert(kmbint_gt(to_mod, "0"));
        divide(bint, to_mod, divide_fn_impl_mod);
}

bool kmbint_eq(const char *bint, const char *to_cmp)
{
        return strcmp(bint, to_cmp) == 0;
}

bool kmbint_neq(const char *bint, const char *to_cmp)
{
        return strcmp(bint, to_cmp) != 0;
}

bool kmbint_gt(const char *bint, const char *to_cmp)
{
        size_t len_bint = strlen(bint);
        size_t len_to_cmp = strlen(to_cmp);
        if (len_bint > len_to_cmp)
                return true;
        else if (len_bint == len_to_cmp)
                return strcmp(bint, to_cmp) > 0;
        else
                return false;
}

bool kmbint_gte(const char *bint, const char *to_cmp)
{
        size_t len_bint = strlen(bint);
        size_t len_to_cmp = strlen(to_cmp);
        if (len_bint > len_to_cmp)
                return true;
        else if (len_bint == len_to_cmp)
                return strcmp(bint, to_cmp) >= 0;
        else
                return false;
}

bool kmbint_lt(const char *bint, const char *to_cmp)
{
        size_t len_bint = strlen(bint);
        size_t len_to_cmp = strlen(to_cmp);
        if (len_bint < len_to_cmp)
                return true;
        else if (len_bint == len_to_cmp)
                return strcmp(bint, to_cmp) < 0;
        else
                return false;
}

bool kmbint_lte(const char *bint, const char *to_cmp)
{
        size_t len_bint = strlen(bint);
        size_t len_to_cmp = strlen(to_cmp);
        if (len_bint < len_to_cmp)
                return true;
        else if (len_bint == len_to_cmp)
                return strcmp(bint, to_cmp) <= 0;
        else
                return false;
}

void kmbint_cross_sum(char *bint)
{
        size_t len_bint = strlen(bint);
        char *end = bint + len_bint;
        char *current = end;
        while (current != bint) {
                --current;
                char c = *current - '0';
                *current = '0';
                char *temp = end - 1;
                while (c > 0) {
                        *temp += c;
                        if (*temp > '9'){
                                *temp -= 10;
                                c = 1;
                        } else {
                                c = 0;
                        }
                        --temp;
                }
        }
        size_t to_shift = 0;
        while (*current == '0') {
                ++current;
                ++to_shift;
        }
        if (to_shift == len_bint) {
                --current;
                --to_shift;
        }
        memmove(bint, current, len_bint - to_shift + 1);
}
