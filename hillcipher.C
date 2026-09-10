#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

int mod(int n)
{
    return (n % MOD + MOD) % MOD;
}

int main()
{
    char text[200];
    char plain[200];
    char cipher[200];
    char decrypted[200];

    int key[2][2] = {
        {3, 3},
        {2, 5}
    };

    int inv[2][2] = {
        {15, 17},
        {20, 9}
    };

    int i, j, k = 0;
    int a, b;

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    /* Remove spaces and keep only alphabets */
    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            plain[k++] = toupper(text[i]);
        }
    }

    plain[k] = '\0';

    /* Add X if message length is odd */
    if(strlen(plain) % 2 != 0)
    {
        strcat(plain, "X");
    }

    /* Encryption */
    k = 0;

    for(i = 0; plain[i] != '\0'; i += 2)
    {
        a = plain[i] - 'A';
        b = plain[i + 1] - 'A';

        cipher[k++] = mod(key[0][0] * a + key[0][1] * b) + 'A';
        cipher[k++] = mod(key[1][0] * a + key[1][1] * b) + 'A';
    }

    cipher[k] = '\0';

    printf("\nKey Matrix:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);

    printf("\nEncrypted message: %s\n", cipher);

    /* Decryption */
    k = 0;

    for(i = 0; cipher[i] != '\0'; i += 2)
    {
        a = cipher[i] - 'A';
        b = cipher[i + 1] - 'A';

        decrypted[k++] = mod(inv[0][0] * a + inv[0][1] * b) + 'A';
        decrypted[k++] = mod(inv[1][0] * a + inv[1][1] * b) + 'A';
    }

    decrypted[k] = '\0';

    printf("Decrypted message: %s\n", decrypted);

    return 0;
}