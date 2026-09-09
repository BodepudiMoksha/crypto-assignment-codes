#include <stdio.h>
#include <string.h>

void encrypt(char text[], char key[], char result[])
{
    int len = strlen(text);
    int n = strlen(key);
    int rows, i, j, k = 0;
    char matrix[100][20];

    rows = (len + n - 1) / n;

    k = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(k < len)
                matrix[i][j] = text[k++];
            else
                matrix[i][j] = 'X';
        }
    }

    k = 0;

    for(int num = 1; num <= n; num++)
    {
        for(j = 0; j < n; j++)
        {
            if(key[j] == '0' + num)
            {
                for(i = 0; i < rows; i++)
                    result[k++] = matrix[i][j];

                break;
            }
        }
    }

    result[k] = '\0';
}

void decrypt(char text[], char key[], char result[])
{
    int len = strlen(text);
    int n = strlen(key);
    int rows = len / n;
    int i, j, k = 0;
    char matrix[100][20];

    for(int num = 1; num <= n; num++)
    {
        for(j = 0; j < n; j++)
        {
            if(key[j] == '0' + num)
            {
                for(i = 0; i < rows; i++)
                    matrix[i][j] = text[k++];

                break;
            }
        }
    }


    k = 0;

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < n; j++)
            result[k++] = matrix[i][j];
    }

    result[k] = '\0';
}

int main()
{
    char text[100];
    char key1[20], key2[20];
    char temp[100], encrypted[100];
    char decrypted1[100], decrypted[100];

    printf("Enter message: ");
    scanf(" %[^\n]", text);

    printf("Enter first key (numeric order, e.g. 3142): ");
    scanf("%s", key1);

    printf("Enter second key (numeric order, e.g. 2413): ");
    scanf("%s", key2);

    encrypt(text, key1, temp);

    encrypt(temp, key2, encrypted);

    printf("\nEncrypted message: %s", encrypted);

    decrypt(encrypted, key2, decrypted1);

    decrypt(decrypted1, key1, decrypted);

    printf("\nDecrypted message: %s", decrypted);

    return 0;
}