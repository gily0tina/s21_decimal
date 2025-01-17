#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result || !s21_is_correct_decimal(value)) {
    return 1;
  }
  s21_set_sign(result, 0);

  int sign = s21_get_sign(value);
  s21_set_sign(&value, 0);

  s21_decimal truncated_decimal;
  s21_truncate(value, &truncated_decimal);

  s21_decimal fraction;
  s21_sub(value, truncated_decimal, &fraction);

  s21_decimal empty_unit = {{0, 0, 0, 0}};
  s21_decimal one_unit = {{1, 0, 0, 0}};

  if (sign && s21_is_greater(fraction, empty_unit)) {
    s21_add(truncated_decimal, one_unit, &truncated_decimal);
  }

  *result = truncated_decimal;
  if (sign) {
    s21_set_sign(result, 1);
  }

  return 0;
}
