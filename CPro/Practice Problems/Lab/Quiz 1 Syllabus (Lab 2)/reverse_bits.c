int reverseBits(int n) {
    int rev = 0;

    for (size_t i = 0, n_bits = sizeof(n) * 8; i < n_bits; i++)
        rev |= ((n >> i) & 1) << (n_bits - i - 1);

    return rev;
}