#include "../s21_decimal.h"

void s21_big_xor(s21_big_decimal big_dec1, s21_big_decimal big_dec2,
                 s21_big_decimal *res) {
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++)
    res->bits[i] = big_dec1.bits[i] ^ big_dec2.bits[i];
}