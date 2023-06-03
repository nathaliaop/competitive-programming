vector<bool> is_prime(MAX, true);
vector<int> primes;

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (is_prime[i]) {
            primes.push_back(i);

            for (int j = i + i; j < MAX; j += i)
                is_prime[j] = false;
        }
    }
}
