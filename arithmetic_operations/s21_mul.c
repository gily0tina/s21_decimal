#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  s21_big_decimal big_dec1 = s21_to_big(value_1);
  s21_big_decimal big_dec2 = s21_to_big(value_2);
  s21_big_decimal res_buf = {{0}};
  if ((s21_get_sign(value_1)) == 0 && (s21_get_sign(value_2)) == 0) {
    res_buf = s21_simple_multiplication(big_dec1, big_dec2);
    s21_big_set_sign(&res_buf, 0);
  }
  if (((s21_get_sign(value_1)) == 1 && (s21_get_sign(value_2)) == 0) ||
      ((s21_get_sign(value_1)) == 0 && (s21_get_sign(value_2)) == 1)) {
    res_buf = s21_simple_multiplication(big_dec1, big_dec2);
    s21_big_set_sign(&res_buf, 1);
  } else if ((s21_get_sign(value_1)) == 1 && (s21_get_sign(value_2)) == 1) {
    res_buf = s21_simple_multiplication(big_dec1, big_dec2);
    s21_big_set_sign(&res_buf, 0);
  }
  code = s21_to_normal(res_buf, result);
  return code;
}

s21_big_decimal s21_simple_multiplication(s21_big_decimal big_dec1,
                                          s21_big_decimal big_dec2) {
  s21_big_decimal res = {0};
  int scale_sum = s21_big_get_scale(big_dec1) + s21_big_get_scale(big_dec2);
  for (int i = 0; i < (BIG_DECIMAL_SIZE - 1) * 32; i++) {
    if (s21_extract_big_decimal_bit(big_dec2, i)) {
      s21_big_decimal tmp = {0};
      for (int k = 0; k < BIG_DECIMAL_SIZE - 1; k++) {
        tmp.bits[k] = big_dec1.bits[k];
      }
      tmp = s21_big_left_shift(tmp, i);
      res = s21_simple_addition(res, tmp);
    }
  }
  s21_big_set_scale(&res, scale_sum);
  return res;
}