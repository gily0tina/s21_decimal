#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst || !s21_is_correct_decimal(src)) {
    return 1;
  }

  double tmp = 0.0;
  for (int i = 0; i < 96; i++) {
    if (s21_extract_decimal_bit(src, i) == 1) {
      tmp += pow(2.0, i);
    }
  }
  tmp /= pow(10, s21_get_scale(src));

  if (s21_get_sign(src)) {
    tmp = -tmp;
  }

  *dst = (float)tmp;
  return 0;
}
