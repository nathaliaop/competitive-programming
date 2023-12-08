// Description:
// Euler's totient function.
// phi(n) is the amount of numbers in the range (1, n) that are coprime with n

// Complexity:
// phi(n) - sqrt(n)
// phi of all numbers from 1 to n - O (n log log n)

// Properties:
// phi(p ^ k) = p ^ k - p ^ (k - 1)
// phi(p) = p - 1
// phi(ab) = phi(a) * phi(b) * d / phi(d) being d = gcd(a, b)

int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
