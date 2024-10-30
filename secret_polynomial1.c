#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Convert a number from a given base to decimal
long long convertToDecimal(const char *value, int base) {
    long long result = 0;
    int length = strlen(value);
    for (int i = 0; i < length; i++) {
        int digit;
        if (value[i] >= '0' && value[i] <= '9') {
            digit = value[i] - '0';
        } else {
            digit = value[i] - 'a' + 10;
        }
        result = result * base + digit;
    }
    return result;
}

// Function for Lagrange interpolation to find the constant term (c)
long long lagrangeInterpolation(int x[], long long y[], int k) {
    long long result = 0;
    for (int i = 0; i < k; i++) {
        long long term = y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term = term * (0 - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

// Parse the JSON file and find the constant term
void findConstantTerm(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    int n, k;
    fscanf(file, "{\"keys\":{\"n\":%d,\"k\":%d}", &n, &k);
    int x[2];
    long long y[7];

    for (int i = 0; i < n; i++) {
        int index, base;
        char value[256];
        fscanf(file, ",\"%d\":{\"base\":\"%d\",\"value\":\"%[^\"]\"}", &index, &base, value);

        x[i] = index;
        y[i] = convertToDecimal(value, base);
    }

    fclose(file);

    // Calculate the constant term (c) using Lagrange Interpolation
    long long constantTerm = lagrangeInterpolation(x, y, k);
    printf("The constant term (c) is: %lld\n", constantTerm);
}

int main() {
    findConstantTerm("testcase.json"); // Change this to the actual filename
    return 0;
}
