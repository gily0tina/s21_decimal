#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_UINT32 0xFFFFFFFF

#define BIG_DECIMAL_SIZE 8

typedef struct {
  uint32_t bits[4];
} s21_decimal;

typedef struct {
  uint32_t bits[BIG_DECIMAL_SIZE];
} s21_big_decimal;

// bit_calls
bool s21_extract_bit(uint32_t value, uint32_t shift);
bool s21_extract_decimal_bit(s21_decimal value, uint32_t shift);
bool s21_extract_big_decimal_bit(s21_big_decimal value, uint32_t shift);
void s21_set_bit(uint32_t *value, uint32_t shift, uint32_t bit);
void s21_set_big_decimal_bit(s21_big_decimal *value, uint32_t shift,
                             uint32_t bit);
void s21_set_decimal_bit(s21_decimal *value, uint32_t shift, uint32_t bit);

// bitwise_operations
void s21_big_and(s21_big_decimal big_dec1, s21_big_decimal big_dec2,
                 s21_big_decimal *res);
void s21_big_xor(s21_big_decimal big_dec1, s21_big_decimal big_dec2,
                 s21_big_decimal *res);
s21_big_decimal s21_invert_bigdec_bits(s21_big_decimal big_dec1);
s21_big_decimal s21_big_left_shift(s21_big_decimal big_dec1, uint32_t shift);
s21_big_decimal s21_big_right_shift(s21_big_decimal big_dec1, uint32_t shift);

// subsidiary_functions
s21_big_decimal s21_to_big(s21_decimal dec);
int s21_to_normal(s21_big_decimal big_dec, s21_decimal *res);
void s21_set_scale(s21_decimal *dec, int scale);
int s21_get_scale(s21_decimal dec);
int s21_get_sign(s21_decimal dec);
void s21_set_sign(s21_decimal *dec, int sign);
void s21_big_set_scale(s21_big_decimal *dec, int scale);
int s21_big_get_scale(s21_big_decimal dec);
int s21_big_get_sign(s21_big_decimal dec);
void s21_big_set_sign(s21_big_decimal *dec, int sign);
bool s21_is_overflow(s21_big_decimal buff);
bool is_mantissa_nonzero(s21_big_decimal big_dec);
void up_scale(s21_big_decimal *dec, uint32_t scale);
uint32_t normalization(s21_big_decimal *big_dec1, s21_big_decimal *big_dec2);
int s21_is_correct_decimal(s21_decimal decimal);
int s21_is_dec_equal_zero(s21_decimal dec);
int s21_is_big_dec_equal_zero(s21_big_decimal big_dec);
int s21_ten_division(s21_decimal *dec);
int s21_big_ten_division(s21_big_decimal *big_dec);
int bank_round(s21_big_decimal *big_dec);

// arithmetics
s21_big_decimal s21_simple_addition(s21_big_decimal big_dec1,
                                    s21_big_decimal big_dec2);
s21_big_decimal s21_simple_subtraction(s21_big_decimal big_dec1,
                                       s21_big_decimal big_dec2);
s21_big_decimal s21_simple_multiplication(s21_big_decimal big_dec1,
                                          s21_big_decimal big_dec2);
s21_big_decimal div_int(s21_big_decimal dividend, s21_big_decimal divisor,
                        s21_big_decimal *quotient);
int s21_add(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);
void fractional_div(s21_big_decimal *remainder, s21_big_decimal divisor,
                    s21_big_decimal *qoutient);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// comparison operations
int s21_is_less(s21_decimal dec1, s21_decimal dec2);
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);

// comparison operations for big decimal
int is_greater_or_equal(s21_big_decimal big_dec1, s21_big_decimal big_dec2);
int s21_big_is_less(s21_big_decimal big_dec1, s21_big_decimal big_dec2);
int s21_big_is_less_or_equal(s21_big_decimal big_dec1,
                             s21_big_decimal big_dec2);
int s21_big_is_greater(s21_big_decimal big_dec1, s21_big_decimal big_dec2);
int s21_big_is_greater_or_equal(s21_big_decimal big_dec1,
                                s21_big_decimal big_dec2);
int s21_big_is_equal(s21_big_decimal big_dec1, s21_big_decimal big_dec2);
int s21_big_is_not_equal(s21_big_decimal big_dec1, s21_big_decimal big_dec2);

// other_functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

// converters
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

#endif