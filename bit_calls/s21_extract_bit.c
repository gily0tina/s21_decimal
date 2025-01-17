#include "../s21_decimal.h"

bool s21_extract_bit(uint32_t value, uint32_t shift) {
  return !!(value & 0b1 << shift);
}

bool s21_extract_decimal_bit(s21_decimal value, uint32_t shift) {
  return s21_extract_bit(value.bits[shift / 32], (shift % 32));
}

bool s21_extract_big_decimal_bit(s21_big_decimal value, uint32_t shift) {
  return s21_extract_bit(value.bits[shift / 32], (shift % 32));
}