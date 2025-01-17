#include "../s21_decimal.h"

s21_big_decimal s21_big_left_shift(s21_big_decimal big_dec1, uint32_t shift) {
  while (shift != 0) {
    uint32_t carry_bit = 0;
    uint32_t upper_bit = 0;
    for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
      upper_bit = s21_extract_bit(big_dec1.bits[i], 31);
      big_dec1.bits[i] <<= 0b1;
      if (carry_bit) s21_set_bit(&big_dec1.bits[i], 0, 1);
      carry_bit = upper_bit;
    }
    shift--;
  }
  return big_dec1;
}

s21_big_decimal s21_big_right_shift(s21_big_decimal big_dec1, uint32_t shift) {
  while (shift != 0) {
    uint32_t carry_bit = 0;
    uint32_t lower_bit = 0;
    for (int i = (BIG_DECIMAL_SIZE - 1); i >= 0; i--) {
      lower_bit = s21_extract_bit(big_dec1.bits[i], 0);
      big_dec1.bits[i] >>= 0b1;
      if (carry_bit) s21_set_bit(&big_dec1.bits[i], 31, 1);
      carry_bit = lower_bit;
    }
    shift--;
  }
  return big_dec1;
}