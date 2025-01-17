#include "../s21_decimal.h"

s21_big_decimal s21_simple_subtraction(s21_big_decimal big_dec1,
                                       s21_big_decimal big_dec2) {
  int bigger_scale = (s21_big_get_scale(big_dec1) > s21_big_get_scale(big_dec2))
                         ? s21_big_get_scale(big_dec1)
                         : s21_big_get_scale(big_dec2);
  s21_big_decimal tmp = {0};
  s21_big_decimal res = {0};
  while (is_mantissa_nonzero(big_dec2)) {
    s21_big_and(s21_invert_bigdec_bits(big_dec1), big_dec2, &tmp);
    s21_big_xor(big_dec1, big_dec2, &big_dec1);
    tmp = s21_big_left_shift(tmp, 1);
    big_dec2 = tmp;
  }
  res = big_dec1;
  s21_big_set_scale(&res, bigger_scale);
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  s21_big_decimal res_buf = {{0}};
  s21_big_decimal big_dec1 = s21_to_big(value_1);
  s21_big_decimal big_dec2 = s21_to_big(value_2);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  s21_big_set_sign(&big_dec1, 0);
  s21_big_set_sign(&big_dec2, 0);
  normalization(&big_dec1, &big_dec2);
  if (sign1 == 0 && sign2 == 0) {
    if (s21_big_is_greater_or_equal(big_dec1, big_dec2)) {
      res_buf = s21_simple_subtraction(big_dec1, big_dec2);
      s21_big_set_sign(&res_buf, 0);
    } else if (s21_big_is_less(big_dec1, big_dec2)) {
      res_buf = s21_simple_subtraction(big_dec2, big_dec1);
      s21_big_set_sign(&res_buf, 1);
    }
  } else if (sign1 == 0 && sign2 == 1) {
    res_buf = s21_simple_addition(big_dec1, big_dec2);
    s21_big_set_sign(&res_buf, 0);
  } else if (sign1 == 1 && sign2 == 0) {
    res_buf = s21_simple_addition(big_dec1, big_dec2);
    s21_big_set_sign(&res_buf, 1);
  } else if (sign1 == 1 && sign2 == 1) {
    if (s21_big_is_greater(big_dec1, big_dec2)) {
      res_buf = s21_simple_subtraction(big_dec1, big_dec2);
      s21_big_set_sign(&res_buf, 1);
    } else if (s21_big_is_less_or_equal(big_dec1, big_dec2)) {
      res_buf = s21_simple_subtraction(big_dec2, big_dec1);
      s21_big_set_sign(&res_buf, 0);
    }
  }

  code = s21_to_normal(res_buf, result);

  return code;
}