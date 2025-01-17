#include "../s21_decimal.h"

void s21_set_scale(s21_decimal *dec, int scale) {
  int sign = s21_get_sign(*dec);
  dec->bits[3] = scale << 16;
  if (sign == 0) {
    s21_set_sign(dec, 0);
  } else {
    s21_set_sign(dec, 1);
  }
}

int s21_get_scale(s21_decimal dec) {
  s21_set_sign(&dec, 0);
  return (int)dec.bits[3] >> 16;
}

int s21_get_sign(s21_decimal dec) {
  return (dec.bits[3] & ((unsigned)1 << 31)) > 0;
}

void s21_set_sign(s21_decimal *dec, int sign) {
  if (sign)
    dec->bits[3] |= (1 << 31);
  else
    dec->bits[3] &= ~(1 << 31);
}

//////////////////////////////

void s21_big_set_scale(s21_big_decimal *dec, int scale) {
  int sign = s21_big_get_sign(*dec);
  dec->bits[7] = scale << 16;
  if (sign == 0) {
    s21_big_set_sign(dec, 0);
  } else {
    s21_big_set_sign(dec, 1);
  }
}

int s21_big_get_scale(s21_big_decimal dec) {
  s21_big_set_sign(&dec, 0);
  return (int)dec.bits[7] >> 16;
}

int s21_big_get_sign(s21_big_decimal dec) {
  return (dec.bits[7] & ((unsigned)1 << 31)) > 0;
}

void s21_big_set_sign(s21_big_decimal *dec, int sign) {
  if (sign)
    dec->bits[BIG_DECIMAL_SIZE - 1] |= (1 << 31);
  else
    dec->bits[BIG_DECIMAL_SIZE - 1] &= ~(1 << 31);
}

//////////////////////////////

s21_big_decimal s21_to_big(s21_decimal dec) {
  s21_big_decimal buff;
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
    buff.bits[i] = 0;
  }
  for (int i = 0; i < 3; i++) {
    buff.bits[i] = dec.bits[i];
  }
  buff.bits[BIG_DECIMAL_SIZE - 1] = dec.bits[3];
  return buff;
}

bool s21_is_overflow(s21_big_decimal buff) {
  return buff.bits[3] || buff.bits[4] || buff.bits[5] || buff.bits[6];
}

int is_greater_or_equal(s21_big_decimal big_dec1, s21_big_decimal big_dec2) {
  for (int i = BIG_DECIMAL_SIZE - 1; i >= 0; i--) {
    if (big_dec1.bits[i] > big_dec2.bits[i]) return 1;
    if (big_dec1.bits[i] < big_dec2.bits[i]) return 0;
  }
  return 1;
}

int bank_round(s21_big_decimal *big_dec) {
  int err = 0;
  int remainder = 0;
  while ((s21_is_overflow(*big_dec) && s21_big_get_scale(*big_dec) > 0) ||
         s21_big_get_scale(*big_dec) > 28) {
    remainder = s21_big_ten_division(big_dec);
  }
  if (s21_is_overflow(*big_dec)) {
    if (s21_big_get_sign(*big_dec) == 1) {
      err = 2;
    } else if (s21_big_get_sign(*big_dec) == 0)
      err = 1;
  }
  s21_big_decimal one_number = {{0b1, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0}};
  s21_big_decimal tmp_result;
  if (remainder == 5) {
    if (((*big_dec).bits[0] & 1) == 0) {
      tmp_result = *big_dec;
    } else {
      tmp_result = s21_simple_addition(*big_dec, one_number);
    }
  } else if (remainder > 5) {
    tmp_result = s21_simple_addition(*big_dec, one_number);
  } else {
    tmp_result = *big_dec;
  }

  if (s21_is_overflow(*big_dec)) {
    if (s21_big_get_sign(*big_dec)) {
      err = 2;
    } else if (s21_big_get_sign(*big_dec) == 0)
      err = 1;
  }

  *big_dec = tmp_result;

  return err;
}

int s21_ten_division(s21_decimal *dec) {
  uint64_t remainder = 0;
  for (int i = 2; i >= 0; --i) {
    uint64_t temp = (remainder << 32) | dec->bits[i];
    dec->bits[i] = temp / 10;
    remainder = temp % 10;
  }
  if (s21_get_scale(*dec) > 0) s21_set_scale(dec, s21_get_scale(*dec) - 1);
  return remainder;
}

int s21_big_ten_division(s21_big_decimal *big_dec) {
  uint64_t remainder = 0;
  for (int i = (BIG_DECIMAL_SIZE - 2); i >= 0; --i) {
    uint64_t current = (remainder << 32) | big_dec->bits[i];
    big_dec->bits[i] = current / 10;
    remainder = current % 10;
  }
  if (s21_big_get_scale(*big_dec) > 0)
    s21_big_set_scale(big_dec, s21_big_get_scale(*big_dec) - 1);
  return remainder;
}

int s21_to_normal(s21_big_decimal big_dec, s21_decimal *res) {
  int result_code = 0;
  if ((result_code = s21_is_overflow(big_dec)) ||
      s21_big_get_scale(big_dec) > 0) {
    result_code = bank_round(&big_dec);
  }
  // s21_decimal res;
  if (result_code == 0) {
    res->bits[0] = big_dec.bits[0];
    res->bits[1] = big_dec.bits[1];
    res->bits[2] = big_dec.bits[2];
    res->bits[3] = big_dec.bits[7];
    s21_set_scale(res, s21_big_get_scale(big_dec));
  }
  return result_code;
}

bool is_mantissa_nonzero(s21_big_decimal big_dec) {
  for (int i = 0; i <= (BIG_DECIMAL_SIZE - 1); i++) {
    if (big_dec.bits[i]) {
      return true;
    }
  }
  return false;
}

void up_scale(s21_big_decimal *dec, uint32_t scale) {
  s21_big_decimal ten_number = {{0b1010, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0}};
  for (uint32_t i = 0; i < scale; i++) {
    *dec = s21_simple_multiplication(*dec, ten_number);
  }
}

uint32_t normalization(s21_big_decimal *big_dec1, s21_big_decimal *big_dec2) {
  uint32_t bigger_scale =
      (s21_big_get_scale(*big_dec1) > s21_big_get_scale(*big_dec2))
          ? s21_big_get_scale(*big_dec1)
          : s21_big_get_scale(*big_dec2);
  uint32_t min_scale =
      (s21_big_get_scale(*big_dec1) < s21_big_get_scale(*big_dec2))
          ? s21_big_get_scale(*big_dec1)
          : s21_big_get_scale(*big_dec2);
  uint32_t dif_scale = bigger_scale - min_scale;
  if (s21_big_get_scale(*big_dec1) > s21_big_get_scale(*big_dec2)) {
    up_scale(big_dec2, dif_scale);
    s21_big_set_scale(big_dec2, bigger_scale);
  } else if (s21_big_get_scale(*big_dec2) > s21_big_get_scale(*big_dec1)) {
    up_scale(big_dec1, dif_scale);
    s21_big_set_scale(big_dec1, bigger_scale);
  }
  return dif_scale;
}

int s21_is_correct_decimal(s21_decimal decimal) {
  int result = 1;
  s21_set_sign(&decimal, 0);
  if (s21_get_scale(decimal) > 28) {
    result = 0;
  }
  int mask = 0b01111111000000001111111111111111;
  if (decimal.bits[3] & mask) {
    result = 0;
  }
  return result;
}

int s21_is_dec_equal_zero(s21_decimal dec) {
  int flag = 0;
  if (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) {
    flag = 1;
  }
  return flag;
}

int s21_is_big_dec_equal_zero(s21_big_decimal big_dec) {
  int flag = 0;
  if (big_dec.bits[0] == 0 && big_dec.bits[1] == 0 && big_dec.bits[2] == 0 &&
      big_dec.bits[3] == 0 && big_dec.bits[4] == 0 && big_dec.bits[5] == 0 &&
      big_dec.bits[6] == 0 && big_dec.bits[7] == 0) {
    flag = 1;
  }
  return flag;
}