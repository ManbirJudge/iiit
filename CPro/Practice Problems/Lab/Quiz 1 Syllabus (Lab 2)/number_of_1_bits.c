int hammingWeight(int n) {
    int c = 0;
    for (size_t i = 0, n_bits = sizeof(n) * 8; i < n_bits; i++)
        c += (n >> i) & 1;
    return c;
}