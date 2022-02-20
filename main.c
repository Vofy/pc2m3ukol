#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

	int matrix [3][3], sarrusMatrix [5][3];
	int determinant, primDiagSubProduct, secDiagSubProduct;
	int *matrixPtr = matrix[0];

	// Generování matice
	printf("Vygenerovaná matice:\n\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrix[i][j] = rand() % 199 - 99;
			printf("%5d", matrix[i][j]);
		}
		printf("\n");
	}
    printf("\n");

    // Determinant matice (rozložený vztah)
	determinant =
        + matrix[0][0] * matrix[1][1] * matrix[2][2]
        + matrix[1][0] * matrix[2][1] * matrix[0][2]
        + matrix[2][0] * matrix[0][1] * matrix[1][2]
        - matrix[0][2] * matrix[1][1] * matrix[2][0]
        - matrix[1][2] * matrix[2][1] * matrix[0][0]
        - matrix[2][2] * matrix[0][1] * matrix[1][0];

    printf("Determinant matice (rozlozeny vztah): %d\n\n", determinant);

    // Rozšíření matice
    printf("Rozsirena matice:\n\n");
    for (int i = 0; i < 3 + 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i < 3) // Pokud vleze do velikosti původní matice
            {
                sarrusMatrix[i][j] = matrix[i][j];
            }
            else
            {
                sarrusMatrix[i][j] = sarrusMatrix[i - 3][j];
            }
            printf("%5d", sarrusMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Determinant matice (pomocí Sarrusova pravidla)
    primDiagSubProduct = 1, secDiagSubProduct = 1, determinant = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            primDiagSubProduct *= sarrusMatrix[j + i][j];
            secDiagSubProduct *= sarrusMatrix[j + i][3 - 1 - j];
        }

        // Přičtení součinů diagonál
        determinant += primDiagSubProduct - secDiagSubProduct;

        // Vyresetování proměnné pro součin
        primDiagSubProduct = 1;
        secDiagSubProduct = 1;
    }

    printf("Determinant matice (pomoci Sarrusova pravidla): %d\n\n", determinant);

    // Determinant matice (pomocí Sarrusova pravidla, bez rozšíření)
    primDiagSubProduct = 1, secDiagSubProduct = 1, determinant = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Výpočet dílčích součinů pro obě diagonály
            primDiagSubProduct *= matrix[(j + i) % 3][j];
            secDiagSubProduct *= matrix[(j + i) % 3][2 - j];
        }

        // Přičtení součinů diagonál
        determinant += primDiagSubProduct - secDiagSubProduct;

        // Vyresetování proměnné pro součin
        primDiagSubProduct = 1;
        secDiagSubProduct = 1;
    }

    printf("Determinant matice (pomoci Sarrusova pravidla, bez rozsireni): %d\n\n", determinant);

    // Determinant matice (pomocí Sarrusova pravidla, bez rozšíření, pomocí ukazatele)
    primDiagSubProduct = 1, secDiagSubProduct = 1, determinant = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Výpočet dílčích součinů pro obě diagonály
            // (navíc musím vynásobit řádek počtem sloupců, protože potřebujeme pořadí prvku v matici)
            primDiagSubProduct *= *(matrixPtr + (((j + i) % 3) * 3) + j);
            secDiagSubProduct *= *(matrixPtr + (((j + i) % 3) * 3) + (2 - j));
        }

        // Přičtení součinů diagonál
        determinant += primDiagSubProduct - secDiagSubProduct;

        // Vyresetování proměnné pro součin
        primDiagSubProduct = 1;
        secDiagSubProduct = 1;
    }

    printf("Determinant matice (pomoci Sarrusova pravidla, bez rozsireni, pomoci ukazatele): %d\n\n", determinant);

    char c;
	scanf("%c", &c);

	return 0;
}
