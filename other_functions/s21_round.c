#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result || !s21_is_correct_decimal(value)) {
    return 1;
  }

  *result = value;
  int sign = s21_get_sign(value);
  s21_set_sign(&value, 0);

  s21_truncate(value, result);
  if (s21_truncate(value, result) != 0) return 1;

  s21_decimal fractional_part;
  if (s21_sub(value, *result, &fractional_part) != 0) return 1;

  s21_decimal half_value = {{5, 0, 0, 0X00010000}};
  s21_decimal one_unit = {{1, 0, 0, 0}};

  if (s21_is_greater_or_equal(fractional_part, half_value)) {
    s21_add(*result, one_unit, result);
  }

  s21_set_sign(result, sign);
  return 0;
}