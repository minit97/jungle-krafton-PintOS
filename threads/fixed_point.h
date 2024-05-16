//
// Created by HYEONMIN PARK on 2024. 5. 16..
//
/*
 * n : integer / x, y : fixed-point numbers / f : 1 in 17.14 format
 */


#define F (1 << 14)                     /* fixed point 1 */
#define INT_MAX ((1 << 31) - 1)
#define INT_MIN (-(1 << 31))

int convert_n_to_fp(int n);
int convert_x_to_int_zero(int x);
int convert_x_to_int_nearest(int x);
int add(int x, int y);
int subtract(int x, int y);
int add_with_fp(int x, int n);
int substract_with_fp(int x, int n);
int multiply(int x, int y);
int multiply_with_fp(int x, int n);
int divide(int x, int y);
int divide_with_fp(int x, int n);

int convert_n_to_fp(int n) {
    return n * F;
}

int convert_x_to_int_zero(int x) {
    return x / F;
}

int convert_x_to_int_nearest(int x) {
    return x >= 0 ? x + F / 2 : x - F / 2;
}

int add(int x, int y) {
    return x + y;
}

int subtract(int x, int y) {
    return x - y;
}

int add_with_fp(int x, int n) {
    return x + n * F;
}

int substract_with_fp(int x, int n) {
    return x - n * F;
}

int multiply(int x, int y) {
    return ((int64_t) x) * y / F;
}

int multiply_with_fp(int x, int n) {
    return x * n;
}

int divide(int x, int y) {
    return ((int64_t) x) * F / y;
}

int divide_with_fp(int x, int n) {
    return x / n;
}