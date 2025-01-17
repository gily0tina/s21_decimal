#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result || !s21_is_correct_decimal(value)) {
    return 1;
  }
  s21_set_sign(&value, !s21_get_sign(value));
  *result = value;
  return 0;
}
