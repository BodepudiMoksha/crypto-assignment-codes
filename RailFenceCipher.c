#include <stdio.h>
#include <string.h>

int main()
{
    char text[100], encrypted[100], decrypted[100];
    char rail[20][100];
    int rails, len, i, j, row, col, k;

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    len = strlen(text);

    if(text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
        len--;
    }

    printf("Enter number of rails: ");
    scanf("%d", &rails);

    /* Initialize rail matrix */
    for(i = 0; i < rails; i++)
        for(j = 0; j < len; j++)
            rail[i][j] = '\n';

    /* Encryption */
    row = 0;
    col = 0;
    k = 0;
    int direction = 1;

    while(k < len)
    {
        rail[row][col++] = text[k++];

        if(row == rails - 1)
            direction = -1;
        else if(row == 0)
            direction = 1;

        row += direction;
    }

    k = 0;

    for(i = 0; i < rails; i++)
    {
        for(j = 0; j < len; j++)
        {
            if(rail[i][j] != '\n')
                encrypted[k++] = rail[i][j];
        }
    }

    encrypted[k] = '\0';

    printf("Encrypted message: %s\n", encrypted);

    /* Clear matrix */
    for(i = 0; i < rails; i++)
        for(j = 0; j < len; j++)
            rail[i][j] = '\n';

    /* Mark zig-zag positions */
    row = 0;
    col = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        rail[row][col++] = '*';

        if(row == rails - 1)
            direction = -1;
        else if(row == 0)
            direction = 1;

        row += direction;
    }

    /* Fill marked positions with encrypted text */
    k = 0;

    for(i = 0; i < rails; i++)
    {
        for(j = 0; j < len; j++)
        {
            if(rail[i][j] == '*')
                rail[i][j] = encrypted[k++];
        }
    }

    /* Decryption */
    row = 0;
    col = 0;
    direction = 1;

    for(i = 0; i < len; i++)
    {
        decrypted[i] = rail[row][col++];

        if(row == rails - 1)
            direction = -1;
        else if(row == 0)
            direction = 1;

        row += direction;
    }

    decrypted[len] = '\0';

    printf("Decrypted message: %s\n", decrypted);

    return 0;
}