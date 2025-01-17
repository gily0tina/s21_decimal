#include "../s21_decimal.h"

void s21_set_bit(uint32_t *value, uint32_t shift, uint32_t bit) {
  if (bit) {
    *value |= 0b1 << shift;
  } else {
    *value &= ~(0b1 << shift);
  }
}

void s21_set_big_decimal_bit(s21_big_decimal *value, uint32_t shift,
                             uint32_t bit) {
  s21_set_bit(&value->bits[shift / 32], (shift % 32), bit);
}

void s21_set_decimal_bit(s21_decimal *value, uint32_t shift, uint32_t bit) {
  s21_set_bit(&value->bits[shift / 32], (shift % 32), bit);
}