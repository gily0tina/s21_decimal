#include "../s21_decimal.h"

s21_big_decimal s21_invert_bigdec_bits(s21_big_decimal big_dec1) {
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
    big_dec1.bits[i] = ~(big_dec1.bits[i]);
  }
  return big_dec1;
}