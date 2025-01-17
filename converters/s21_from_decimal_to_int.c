#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst || !s21_is_correct_decimal(src)) {
    return 1;
  }

  int error = 0;
  bool sign = s21_get_sign(src);
  uint32_t scale = s21_get_scale(src);

  s21_decimal temp = {{0}};
  if (scale != 0) {
    s21_truncate(src, &temp);
  } else {
    temp = src;
  }

  if (((temp.bits[1] != 0) || (temp.bits[2] != 0)) ||
      (temp.bits[0] > 2147483647)) {
    error = 1;
  }

  *dst = temp.bits[0];
  if (sign == 1) {
    *dst = -*dst;
  }

  return error;
}
