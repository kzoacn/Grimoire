long long multiply_mod(long long x, long long y, const long long &mod) {
    fix(x, mod);
    fix(y, mod);
    long long result = x * y - (long long)((long double)x * y / mod) * mod;
    fix(result, mod);
    return result;
}