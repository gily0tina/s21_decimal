#include "s21_test.h"
START_TEST(test_greater_zero_and_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_positive_and_negative) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater_negative_and_positive) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_with_scale) {
  s21_decimal a = {{1000000, 0, 0, 0x00060000}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_negative_values) {
  s21_decimal a = {{2, 0, 0, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_same_values) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_large_numbers) {
  s21_decimal a = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal b = {{UINT32_MAX - 1, UINT32_MAX, UINT32_MAX, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater_with_different_scales) {
  s21_decimal a = {{10, 0, 0, 0x00010000}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_max_negative_and_min_positive) {
  s21_decimal a = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_min_negative_and_max_positive) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  s21_decimal b = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_with_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_with_negative_zero) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(s21_greater_1) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 2;
  // src2 = 2;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_2) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 457;
  // src2 = 2.00;
  src1.bits[0] = 0b00000000000000000000000111001001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000011001000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_3) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 2;
  // src2 = 54;
  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000110110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_4) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 0.000000000000000000000000000;
  // src2 = 0;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000110110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_5) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -3;
  // src2 = 3;
  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_6) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 2.222212;
  // src2 = 2.222212;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  src2.bits[0] = 0b00000000001000011110100010000100;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000001100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_7) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 2.22221200000001000;
  // src2 = 2.222212;
  src1.bits[0] = 0b00000111100011111010001111101000;
  src1.bits[1] = 0b00000011000101010111110100000001;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000100010000000000000000;
  src2.bits[0] = 0b00000000001000011110100010000100;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000001100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_8) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 3.745754741;
  // src2 = 3.222212;
  src1.bits[0] = 0b11011111010000111010111001110101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000010010000000000000000;
  src2.bits[0] = 0b00000000001100010010101011000100;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000001100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_9) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 2.222212;
  // src2 = -2.2222120002;
  src1.bits[0] = 0b00000000001000011110100010000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001100000000000000000;
  src2.bits[0] = 0b00101100100010101010010001000010;
  src2.bits[1] = 0b00000000000000000000000000000101;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000010100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_10) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -364748;
  // src2 = 1;
  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_11) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 987456543210.0;
  // src2 = 98745654321.0;
  src1.bits[0] = 0b00011001111101110000001100100100;
  src1.bits[1] = 0b00000000000000000000100011111011;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b11101000111111110001100111101010;
  src2.bits[1] = 0b00000000000000000000000011100101;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000010000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_12) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -9878798789.5867800;
  // src2 = -9878798789.58678;
  src1.bits[0] = 0b11001110100110111101100110011000;
  src1.bits[1] = 0b00000001010111101111011100100110;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001110000000000000000;
  src2.bits[0] = 0b10110101010001000001111001010110;
  src2.bits[1] = 0b00000000000000111000001001111000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001010000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_13) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 9999999999999999999;
  // src2 = 1;
  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_14) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 18446744073709551615;
  // src2 = 434345343551615.00000000000;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b01000110001111010001100000000000;
  src2.bits[1] = 0b11010011010011111110100110011101;
  src2.bits[2] = 0b00000000001000111110110110011110;
  src2.bits[3] = 0b00000000000010110000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_15) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;
  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_16) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -796214545.3526545454564545456;
  // src2 = -545454512454545.35265454545645;
  src1.bits[0] = 0b10111111111111101001001110110000;
  src1.bits[1] = 0b11101010111111101111100111101000;
  src1.bits[2] = 0b00011001101110100010000111100001;
  src1.bits[3] = 0b10000000000100110000000000000000;
  src2.bits[0] = 0b10000010111000100101101011101101;
  src2.bits[1] = 0b11111001111010000010010110101101;
  src2.bits[2] = 0b10110000001111101111000010010100;
  src2.bits[3] = 0b10000000000011100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_17) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -545454512454545.35265454545645;
  // src2 = -5.352654545456454545645464;
  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b01001000000110110001111110011000;
  src2.bits[1] = 0b11111011111111011000100101101101;
  src2.bits[2] = 0b00000000000001000110110101110111;
  src2.bits[3] = 0b10000000000110000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_18) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -7961327845421.843434341378545;
  // src2 = 7961327.845421879754123131254;
  src1.bits[0] = 0b11110011001100111010100111110001;
  src1.bits[1] = 0b01001011001101011000000011010000;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b10000000000011110000000000000000;
  src2.bits[0] = 0b01001110111001000011100101110110;
  src2.bits[1] = 0b01001011001101011010000111011001;
  src2.bits[2] = 0b00011001101110010111010010111111;
  src2.bits[3] = 0b00000000000101010000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_19) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 12345677.987654345678987654346;
  // src2 = 12345677.987654000000000000000;
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b11100111110001110000000000000000;
  src2.bits[1] = 0b11000000010001001001101110001101;
  src2.bits[2] = 0b00100111111001000001101100000000;
  src2.bits[3] = 0b00000000000101010000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_20) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 12345677.987654345678987654346;
  // src2 = 145752736456.9876545678987653;
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b10001101100101011101000110000101;
  src2.bits[1] = 0b11000001100101010111000111101011;
  src2.bits[2] = 0b00000100101101011010001101101100;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_21) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 87654323456.98765456789876530;
  // src2 = -87654323456.98765456789876531;
  src1.bits[0] = 0b10110010000010100010111100110010;
  src1.bits[1] = 0b10011001010111000101110110000000;
  src1.bits[2] = 0b00011100010100101001100001111111;
  src1.bits[3] = 0b00000000000100010000000000000000;
  src2.bits[0] = 0b10110010000010100010111100110011;
  src2.bits[1] = 0b10011001010111000101110110000000;
  src2.bits[2] = 0b00011100010100101001100001111111;
  src2.bits[3] = 0b10000000000100010000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_22) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -854764561465456456.9876545679;
  // src2 = -87654323456.98765456789876530;
  src1.bits[0] = 0b11000100000001000100000010001111;
  src1.bits[1] = 0b01000000100100100110001100010101;
  src1.bits[2] = 0b00011011100111100111001001011101;
  src1.bits[3] = 0b10000000000010100000000000000000;
  src2.bits[0] = 0b10110010000010100010111100110010;
  src2.bits[1] = 0b10011001010111000101110110000000;
  src2.bits[2] = 0b00011100010100101001100001111111;
  src2.bits[3] = 0b10000000000100010000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_23) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 0.0;
  // src2 = 0.69;
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00000000000000000000000001000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_24) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -69.1234567;
  // src2 = -69.12345670000000;
  src1.bits[0] = 0b00101001001100110110011100000111;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001110000000000000000;
  src2.bits[0] = 0b11100100001110011001110110000000;
  src2.bits[1] = 0b00000000000110001000111010111101;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000011100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_25) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 13436577854.000000000000;
  // src2 = 13436577854;
  src1.bits[0] = 0b00100110011110011110000000000000;
  src1.bits[1] = 0b01100101111110011111000000101100;
  src1.bits[2] = 0b00000000000000000000001011011000;
  src1.bits[3] = 0b00000000000011000000000000000000;
  src2.bits[0] = 0b00100000111000011110100000111110;
  src2.bits[1] = 0b00000000000000000000000000000011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_26) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 79228162514264337593543950335;
  // src2 = 79228162514264337593543950335;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_27) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 79228162514264337593543950335;
  // src2 = -79228162514264337593543950335;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 1;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_28) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;
  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_29) {
  s21_decimal src1, src2;
  int origin;
  // src1 = 2.7986531268974139743;
  // src2 = 2.7986531268974139743;
  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  src2.bits[0] = 0b11111110100100001101100101011111;
  src2.bits[1] = 0b10000100011001000010000111101000;
  src2.bits[2] = 0b00000000000000000000000000000001;
  src2.bits[3] = 0b00000000000100110000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

START_TEST(s21_greater_30) {
  s21_decimal src1, src2;
  int origin;
  // src1 = -2156878451.8547640000000000;
  // src2 = -2156878451.854764;
  src1.bits[0] = 0b10010011100100010011000000000000;
  src1.bits[1] = 0b00100110110100100010010100001001;
  src1.bits[2] = 0b00000000000100011101011101011110;
  src1.bits[3] = 0b10000000000100000000000000000000;
  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  int result = s21_is_greater(src1, src2);
  origin = 0;
  ck_assert_int_eq(origin, result);
}
END_TEST

Suite *suite_s21_is_greater_test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_is_greater");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_greater_zero_and_zero);
  tcase_add_test(tc_core, test_greater_positive_and_negative);
  tcase_add_test(tc_core, test_greater_negative_and_positive);
  tcase_add_test(tc_core, test_greater_with_scale);
  tcase_add_test(tc_core, test_greater_negative_values);
  tcase_add_test(tc_core, test_greater_same_values);
  tcase_add_test(tc_core, test_greater_large_numbers);
  tcase_add_test(tc_core, test_greater_with_different_scales);
  tcase_add_test(tc_core, test_greater_max_negative_and_min_positive);
  tcase_add_test(tc_core, test_greater_min_negative_and_max_positive);
  tcase_add_test(tc_core, test_greater_with_zero);
  tcase_add_test(tc_core, test_greater_with_negative_zero);
  tcase_add_test(tc_core, s21_greater_1);
  tcase_add_test(tc_core, s21_greater_2);
  tcase_add_test(tc_core, s21_greater_3);
  tcase_add_test(tc_core, s21_greater_4);
  tcase_add_test(tc_core, s21_greater_5);
  tcase_add_test(tc_core, s21_greater_6);
  tcase_add_test(tc_core, s21_greater_7);
  tcase_add_test(tc_core, s21_greater_8);
  tcase_add_test(tc_core, s21_greater_9);
  tcase_add_test(tc_core, s21_greater_10);
  tcase_add_test(tc_core, s21_greater_11);
  tcase_add_test(tc_core, s21_greater_12);
  tcase_add_test(tc_core, s21_greater_13);
  tcase_add_test(tc_core, s21_greater_14);
  tcase_add_test(tc_core, s21_greater_15);
  tcase_add_test(tc_core, s21_greater_16);
  tcase_add_test(tc_core, s21_greater_17);
  tcase_add_test(tc_core, s21_greater_18);
  tcase_add_test(tc_core, s21_greater_19);
  tcase_add_test(tc_core, s21_greater_20);
  tcase_add_test(tc_core, s21_greater_21);
  tcase_add_test(tc_core, s21_greater_22);
  tcase_add_test(tc_core, s21_greater_23);
  tcase_add_test(tc_core, s21_greater_24);
  tcase_add_test(tc_core, s21_greater_25);
  tcase_add_test(tc_core, s21_greater_26);
  tcase_add_test(tc_core, s21_greater_27);
  tcase_add_test(tc_core, s21_greater_28);
  tcase_add_test(tc_core, s21_greater_29);
  tcase_add_test(tc_core, s21_greater_30);
  suite_add_tcase(s, tc_core);

  return s;
}
