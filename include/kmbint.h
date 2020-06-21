#ifndef kmbint_h
#define kmbint_h

#include <stdbool.h>

void kmbint_add(char *bint, const char *to_add);
void kmbint_sub(char *bint, const char *to_diff);
void kmbint_mul(char *bint, const char *to_mul);
void kmbint_div(char *bint, const char *to_div);
void kmbint_mod(char *bint, const char *to_mod);

bool kmbint_eq(const char *bint, const char *to_cmp);
bool kmbint_neq(const char *bint, const char *to_cmp);
bool kmbint_gt(const char *bint, const char *to_cmp);
bool kmbint_gte(const char *bint, const char *to_cmp);
bool kmbint_lt(const char *bint, const char *to_cmp);
bool kmbint_lte(const char *bint, const char *to_cmp);

void kmbint_cross_sum(char *bint);

#endif
