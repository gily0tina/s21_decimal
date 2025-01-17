#include "../s21_decimal.h"

int s21_big_is_less(s21_big_decimal big_dec1, s21_big_decimal big_dec2) {
  int flag = 1;
  if (s21_big_is_equal(big_dec1, big_dec2)) {
    flag = 0;
  } else if (s21_big_get_sign(big_dec1) == 0 &&
             s21_big_get_sign(big_dec2) == 1) {
    flag = 0;
  } else if (s21_big_get_sign(big_dec1) == 1 &&
             s21_big_get_sign(big_dec2) == 0) {
    flag = 1;
  } else {
    if (s21_big_get_sign(big_dec1) == 0 && s21_big_get_sign(big_dec2) == 0) {
      for (int i = BIG_DECIMAL_SIZE - 2; i >= 0; i--) {
        if (big_dec1.bits[i] < big_dec2.bits[i]) {
          flag = 1;
          break;
        } else if (big_dec1.bits[i] > big_dec2.bits[i]) {
          flag = 0;
          break;
        }
      }
    }

    else if (s21_big_get_sign(big_dec1) == 1 &&
             s21_big_get_sign(big_dec2) == 1) {
      for (int i = BIG_DECIMAL_SIZE - 2; i >= 0; i--) {
        if (big_dec1.bits[i] > big_dec2.bits[i]) {
          flag = 1;
          break;
        } else if (big_dec1.bits[i] < big_dec2.bits[i]) {
          flag = 0;
          break;
        }
      }
    }
  }

  return flag;
}

int s21_big_is_less_or_equal(s21_big_decimal big_dec1,
                             s21_big_decimal big_dec2) {
  return s21_big_is_less(big_dec1, big_dec2) ||
         s21_big_is_equal(big_dec1, big_dec2);
}

int s21_big_is_greater(s21_big_decimal big_dec1, s21_big_decimal big_dec2) {
  int flag = 1;
  if (s21_big_is_equal(big_dec1, big_dec2)) {
    flag = 0;
  } else {
    flag = !s21_big_is_less(big_dec1, big_dec2);
  }
  return flag;
}

int s21_big_is_greater_or_equal(s21_big_decimal big_dec1,
                                s21_big_decimal big_dec2) {
  return s21_big_is_greater(big_dec1, big_dec2) ||
         s21_big_is_equal(big_dec1, big_dec2);
}

int s21_big_is_equal(s21_big_decimal big_dec1, s21_big_decimal big_dec2) {
  int flag = 1;
  if (s21_is_big_dec_equal_zero(big_dec1) &&
      s21_is_big_dec_equal_zero(big_dec2)) {
    flag = 1;
  } else if (s21_big_get_sign(big_dec1) != s21_big_get_sign(big_dec2)) {
    flag = 0;
  } else {
    int not_equal = 1;
    for (int i = 0; i < BIG_DECIMAL_SIZE - 1 && not_equal; i++) {
      if (big_dec1.bits[i] != big_dec2.bits[i]) {
        not_equal = 0;
        flag = 0;
      }
    }
  }

  return flag;
}

int s21_big_is_not_equal(s21_big_decimal big_dec1, s21_big_decimal big_dec2) {
  return !s21_big_is_equal(big_dec1, big_dec2);
}