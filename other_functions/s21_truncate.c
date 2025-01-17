#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result || !s21_is_correct_decimal(value)) {
    return 1;
  }
  while (s21_get_scale(value) > 0) {
    s21_ten_division(&value);
  }
  *result = value;

  return 0;
}