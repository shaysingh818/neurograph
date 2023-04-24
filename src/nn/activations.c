#include "includes/activations.h"

// Sigmoid function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Sigmoid derivative function (sigmoid prime)
double sigmoid_prime(double x) {
    double sig = sigmoid(x);
    return sig * (1 - sig);
}
