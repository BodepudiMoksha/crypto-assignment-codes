#include <stdio.h>
#include <string.h>

#define MAX_COLS 20
#define MAX_ROWS 20

int main()
{
    char text[400];
    int key[MAX_COLS];
    int cols;

    printf("Enter number of columns (key length): ");
    scanf("%d", &cols);

    if (cols < 2 || cols > MAX_COLS)
    {
        printf("Invalid number of columns!\n");
        return 1;
    }

    printf("Enter key order (%d integers): ", cols);

    for (int i = 0; i < cols; i++)
        scanf("%d", &key[i]);

    getchar();

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    int len = strlen(text);
    int rows = (len + cols - 1) / cols;

    if (rows > MAX_ROWS)
    {
        printf("Plaintext is too long!\n");
        return 1;
    }

    char grid[MAX_ROWS][MAX_COLS];
    int idx = 0;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (idx < len)
                grid[r][c] = text[idx++];
            else
                grid[r][c] = 'X';
        }
    }

    char cipher[400];
    int cidx = 0;

    for (int k = 1; k <= cols; k++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (key[c] == k)
            {
                for (int r = 0; r < rows; r++)
                    cipher[cidx++] = grid[r][c];
            }
        }
    }

    cipher[cidx] = '\0';

    printf("Ciphertext: %s\n", cipher);

    char dgrid[MAX_ROWS][MAX_COLS];
    int pos = 0;

    for (int k = 1; k <= cols; k++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (key[c] == k)
            {
                for (int r = 0; r < rows; r++)
                    dgrid[r][c] = cipher[pos++];
            }
        }
    }

    char plain[400];
    int pidx = 0;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
            plain[pidx++] = dgrid[r][c];
    }

    plain[pidx] = '\0';

    printf("Decrypted : %s\n", plain);

    return 0;
}