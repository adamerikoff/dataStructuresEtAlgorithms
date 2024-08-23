#include <math.h>

#include "helper_prime.h"


int is_prime(int x) {
    if (x < 2) {
        return -1; // Undefined (i.e., x < 2)
    }
    if (x == 2) {
        return 1; // 2 is a prime number
    }
    if (x % 2 == 0) {
        return 0; // Even number greater than 2 is not prime
    }
    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            return 0; // Not prime
        }
    }
    return 1; // Prime number
}

int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}
