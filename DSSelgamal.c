#include <stdio.h>

long long power(long long a, long long b, long long p)
{
    long long res = 1;
    a %= p;

    while (b > 0)
    {
        if (b % 2)
            res = (res * a) % p;

        a = (a * a) % p;
        b /= 2;
    }

    return res;
}

long long inverse(long long a, long long m)
{
    long long i;

    for (i = 1; i < m; i++)
        if ((a * i) % m == 1)
            return i;

    return -1;
}

int isPrime(long long n)
{
    long long i;

    if (n < 2)
        return 0;

    for (i = 2; i <= n / i; i++)
        if (n % i == 0)
            return 0;

    return 1;
}

int isPrimitiveRoot(long long g, long long p)
{
    long long i;

    for (i = 1; i < p - 1; i++)
        if (power(g, i, p) == 1)
            return 0;

    return power(g, p - 1, p) == 1;
}

int main()
{
    long long p, g, x, k, m;
    long long y, r, s, inv, m2, r2, s2;

    printf("Enter prime number p: ");
    scanf("%lld", &p);

    if (!isPrime(p))
    {
        printf("Error: p must be prime.\n");
        return 0;
    }

    printf("Enter primitive root g: ");
    scanf("%lld", &g);

    if (g < 2 || g >= p || !isPrimitiveRoot(g, p))
    {
        printf("Error: g must be a primitive root modulo p.\n");
        return 0;
    }

    printf("Enter private key x (1 to p-2): ");
    scanf("%lld", &x);

    if (x < 1 || x >= p - 1)
    {
        printf("Invalid private key.\n");
        return 0;
    }

    printf("Enter message hash m (non-negative): ");
    scanf("%lld", &m);

    if (m < 0)
    {
        printf("Invalid message hash.\n");
        return 0;
    }

    printf("Enter random number k (coprime to p-1): ");
    scanf("%lld", &k);

    if (k < 1 || k >= p - 1 ||
        inverse(k, p - 1) == -1)
    {
        printf("Invalid k. Choose a number coprime to p-1.\n");
        return 0;
    }

    y = power(g, x, p);
    r = power(g, k, p);
    inv = inverse(k, p - 1);
    m2 = m % (p - 1);

    s = ((m2 - (x * r) % (p - 1) + (p - 1))
         * inv) % (p - 1);

    printf("\nPublic key y = %lld\n", y);
    printf("Signature (r, s) = (%lld, %lld)\n", r, s);

    printf("\nEnter received message hash: ");
    scanf("%lld", &m2);

    printf("Enter received r: ");
    scanf("%lld", &r2);

    printf("Enter received s: ");
    scanf("%lld", &s2);

    if (m2 < 0 || r2 < 1 || r2 >= p ||
        s2 < 0 || s2 >= p - 1)
    {
        printf("INVALID SIGNATURE\n");
        return 0;
    }

    if (s2 == 0)
    {
        printf("INVALID SIGNATURE\n");
        return 0;
    }

    if (power(g, m2 % (p - 1), p) ==
        (power(y, r2, p) * power(r2, s2, p)) % p)
        printf("Signature is VALID\n");
    else
        printf("Signature is INVALID\n");

    return 0;
}
