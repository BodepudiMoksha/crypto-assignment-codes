#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char text[100], encrypted[100], decrypted[100];
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i, j;

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    /* Encryption */
    for(i = 0; text[i] != '\0'; i++)
    {
        if(isupper(text[i]))
            encrypted[i] = key[text[i] - 'A'];
        else if(islower(text[i]))
            encrypted[i] = tolower(key[text[i] - 'a']);
        else
            encrypted[i] = text[i];
    }
    encrypted[i] = '\0';

    printf("Encrypted message: %s", encrypted);

    /* Decryption */
    for(i = 0; encrypted[i] != '\0'; i++)
    {
        if(isupper(encrypted[i]))
        {
            for(j = 0; j < 26; j++)
            {
                if(key[j] == encrypted[i])
                {
                    decrypted[i] = 'A' + j;
                    break;
                }
            }
        }
        else if(islower(encrypted[i]))
        {
            for(j = 0; j < 26; j++)
            {
                if(tolower(key[j]) == encrypted[i])
                {
                    decrypted[i] = 'a' + j;
                    break;
                }
            }
        }
        else
            decrypted[i] = encrypted[i];
    }

    decrypted[i] = '\0';

    printf("Decrypted message: %s", decrypted);

    return 0;
}