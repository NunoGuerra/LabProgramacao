#include<stdio.h>
#include<stdlib.h>

typedef struct matriz
{
	int x;
	int y;
	char character;
	int boolTemforma; // 0 = false | 1 = true
}Matriz;

typedef struct forma
{
	int x;
	int y;
	int width;
	int height;

}Forma;

int compare(const void* a, const void* b)
{

	Forma* formaA = (Forma*)a;
	Forma* formaB = (Forma*)b;

	return (formaA->y - formaB->y);
}

void DesenharMatriz(int MaxHeight, int posMatriz, int MaxXYposition, int column, int MaxWidth, Matriz* Matriz_array_invertida)
{
	for (int contador = 1; contador <= MaxHeight; contador++)
	{
		//* Obter a primeira casa da ultima linha
		posMatriz = (MaxXYposition - contador) - (MaxHeight * column);

		// Fazer loop sobre o numero linhas
		for (int i = 0; i < MaxWidth; i++)
		{
			printf("%c", Matriz_array_invertida[posMatriz].character);

			// incrementar para obter a proxima casa da ultima linha
			posMatriz = posMatriz + MaxHeight;
		}

		printf("\n");
	}
}

void DesenharPecasNaMatriz(int MaxXYposition, int formaXStart, int formaXEnd, int formaYStart, int formaYEnd, Matriz* Matriz_array, int boolTemforma, char character)
{
	for (int i = 0; i < MaxXYposition; i++)
	{
		int MatrizX = Matriz_array[i].x;
		int MatrizY = Matriz_array[i].y;

		if (MatrizX >= formaXStart && MatrizX <= formaXEnd)
		{
			if (MatrizY >= formaYStart && MatrizY <= formaYEnd)
			{
				Matriz_array[i].character = character;
				Matriz_array[i].boolTemforma = boolTemforma;
			}
		}
	}
}

void CriarMatriz(int posMatriz, int MaxXYposition, int MaxWidth, int MaxHeight, Matriz* Matriz_array)
{
	while (posMatriz < MaxXYposition)
	{
		for (int posX = 0; posX < MaxWidth; posX++)
		{
			for (int posY = 0; posY < MaxHeight; posY++)
			{
				Matriz_array[posMatriz].x = posX;
				Matriz_array[posMatriz].y = posY;
				Matriz_array[posMatriz].boolTemforma = 0;
				Matriz_array[posMatriz].character = ' ';

				posMatriz++;
			}
		}
	}
}


int main()
{

	// LER FICHEIRO
	FILE* infile;

	int x, y, width, height;
	int counter = 0;
	int nrFormas;

	// Abrir ficheiro para leitura
	infile = fopen("rectangulos.txt", "r");

	// Verificar se ficheiro foi aberto com successo
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n"); // Erro ao abrir ficheiro e sair de seguida
		exit(1);
	}

	// Ler até ao fim do ficheiro para obter o nr de pecas a criar
	while (fscanf(infile, "%d;%d;%d;%d", &x, &y, &width, &height) != EOF) {
		counter++; //incrementar o counter
	}
	nrFormas = counter; //Assignar o valor do counter ao nr de formas
	// fechar ficheiro
	fclose(infile);

	// Abrir ficheiro para leitura
	infile = fopen("rectangulos.txt", "r");

	// Verificar se ficheiro foi aberto com successo
	if (infile == NULL)
	{
		fprintf(stderr, "\nError opening file\n"); // Erro ao abrir ficheiro e sair de seguida
		exit(1);
	}

	Forma* forma_array = (Forma*)calloc(nrFormas, sizeof(Forma));

	if (forma_array == NULL)
	{
		printf("Cannot allocate initial memory for forma\n");
		exit(1);
	}

	counter = 0;
	// Ler até ao fim do ficheiro
	while (fscanf(infile, "%d;%d;%d;%d", &x, &y, &width, &height) != EOF) {

		//assignar valores das variaveis locais á struct
		forma_array[counter].x = x;
		forma_array[counter].y = y;
		forma_array[counter].width = width;
		forma_array[counter].height = height;
		counter++;
	}
	// fechar ficheiro
	fclose(infile);

	int MaxWidth, MaxHeight, MaxXYposition;

	MaxWidth = 80;
	MaxHeight = 25;

	MaxXYposition = MaxWidth * MaxHeight;

	Matriz* Matriz_array = (Matriz*)calloc(MaxXYposition, sizeof(Matriz));

	if (Matriz_array == NULL)
	{
		printf("Cannot allocate initial memory for Matriz\n");
		exit(1);
	}

	// criar matriz vazia
	int posMatriz = 0;

	CriarMatriz(posMatriz, MaxXYposition, MaxWidth, MaxHeight, Matriz_array);

	// Inserir formas na matriz

	for (int forma = 0; forma < nrFormas; forma++)
	{
		int formaXStart = forma_array[forma].x;
		int formaYStart = forma_array[forma].y;
		int formaXEnd = forma_array[forma].x + (forma_array[forma].width - 1);
		int formaYEnd = forma_array[forma].y + (forma_array[forma].height - 1);

		DesenharPecasNaMatriz(MaxXYposition, formaXStart, formaXEnd, formaYStart, formaYEnd, Matriz_array, 1, '-');
	}

	// Desenhar matriz
	posMatriz = MaxXYposition;
	int column = (MaxWidth - 1);

	//DesenharMatriz(MaxHeight, posMatriz, MaxXYposition, column, MaxWidth, Matriz_array);

	// inverter a matriz

	width = MaxWidth;
	height = MaxHeight;
	MaxWidth = height;
	MaxHeight = width;

	Matriz* Matriz_array_invertida = (Matriz*)calloc(MaxXYposition, sizeof(Matriz));

	// criar matriz invertida vazia
	posMatriz = 0;
	CriarMatriz(posMatriz, MaxXYposition, MaxWidth, MaxHeight, Matriz_array_invertida);

	// criar formas invertidas

	Forma* forma_invertida_array = (Forma*)calloc(nrFormas, sizeof(Forma));

	if (forma_invertida_array == NULL)
	{
		printf("Cannot allocate initial memory for forma\n");
		exit(1);
	}

	for (int forma = 0; forma < nrFormas; forma++)
	{
		int formaX = forma_array[forma].x;
		int formaY = forma_array[forma].y;
		int formaWidth = forma_array[forma].width;
		int formaHeight = forma_array[forma].height;

		int forma_invertidaX = formaY;
		int forma_invertidaY = (((MaxHeight - 1) - formaX) - (formaWidth - 1));
		int forma_invertidaWidth = formaHeight;
		int forma_invertidaHeight = formaWidth;

		forma_invertida_array[forma].x = forma_invertidaX;
		forma_invertida_array[forma].y = forma_invertidaY;
		forma_invertida_array[forma].width = forma_invertidaWidth;
		forma_invertida_array[forma].height = forma_invertidaHeight;
	}

	// inserir formas invertidas em matriz invertida
	for (int forma = 0; forma < nrFormas; forma++)
	{
		int formaXStart = forma_invertida_array[forma].x;
		int formaYStart = forma_invertida_array[forma].y;
		int formaXEnd = forma_invertida_array[forma].x + (forma_invertida_array[forma].width - 1);
		int formaYEnd = forma_invertida_array[forma].y + (forma_invertida_array[forma].height - 1);

		DesenharPecasNaMatriz(MaxXYposition, formaXStart, formaXEnd, formaYStart, formaYEnd, Matriz_array_invertida, 1, '|');
	}

	printf("\n");
	// Desenhar matriz invertida
	posMatriz = MaxXYposition;
	column = (MaxWidth - 1);

	//DesenharMatriz(MaxHeight, posMatriz, MaxXYposition, column, MaxWidth, Matriz_array_invertida);

	// Fazer sort das formas pela casa y
	qsort(forma_invertida_array, nrFormas, sizeof(Forma), compare);


	//Aplicar gravidade

	Forma* forma_invertida_gravidade_array = (Forma*)calloc(nrFormas, sizeof(Forma));

	if (forma_invertida_gravidade_array == NULL)
	{
		printf("Cannot allocate initial memory for forma\n");
		exit(1);
	}


	// Loop sobre cada peca
	for (int forma = 0; forma < nrFormas; forma++)
	{
		// adicionar nova peca com gravidade(nesste momento ainda nao se aplica a gravidade)
		forma_invertida_gravidade_array[forma].x = forma_invertida_array[forma].x;
		forma_invertida_gravidade_array[forma].y = forma_invertida_array[forma].y;
		forma_invertida_gravidade_array[forma].width = forma_invertida_array[forma].width;
		forma_invertida_gravidade_array[forma].height = forma_invertida_array[forma].height;

		// obter parametros da peca
		int formaXStart = forma_invertida_array[forma].x;
		int formaYStart = forma_invertida_array[forma].y;
		int formaXEnd = forma_invertida_array[forma].x + (forma_invertida_array[forma].width - 1);
		int formaYEnd = forma_invertida_array[forma].y + (forma_invertida_array[forma].height - 1);

		// Redesenhar peca na matriz invertida (para o caso de ter sido removido algum caracter da pecas anteriomente mexidas, isto acontece se algumas pecas partilharem o mesmo Xn,Yn)
		printf("\n");
		DesenharPecasNaMatriz(MaxXYposition, formaXStart, formaXEnd, formaYStart, formaYEnd, Matriz_array_invertida, 1, '|');

		//printf("\n Matriz com gravidade por peca \n");

		// Desenhar matriz invertida com gravidade
		posMatriz = MaxXYposition;
		column = (MaxWidth - 1);

		//DesenharMatriz(MaxHeight, posMatriz, MaxXYposition, column, MaxWidth, Matriz_array_invertida);

		if (formaYStart != 0) // se for posicao y = 0 nao pode descer mais
		{
			// Obter parametros de Xn,Yn a verificar
			int posXverificar = formaXStart;
			int posYVerificar = formaYStart - 1;

			// Variaveis que vao determinar se a peca pode ser movida e para onde pode ser movida(Apenas Y visto que se trata apenas de gravidade)
			int pecaPodeSermovida = 0;
			int pecaMovidaParaY = 0;
			int nrDeCasasMovidasY = 0;

			// enquanto o y for superior ou igual a zero
			while (posYVerificar >= 0)
			{
				// Definir que peca pode ser movida inicialmente
				int pecaMovida = 1;

				// enquanto nao se percorrer todas as casas do x da peca, ou seja enquanto o X inicial for inferior ou igual ao X final
				while (posXverificar < formaXEnd)
				{
					// Rodar por todos as casas do array da matriz
					for (int i = 0; i < MaxXYposition; i++)
					{
						// Verificar se o valor de x da matriz e igual ao valor da posicao x a verificar
						if (Matriz_array_invertida[i].x == posXverificar)
						{
							// Verificar se o valor de y da matriz e igual ao valor da posicao y a verificar
							if (Matriz_array_invertida[i].y == posYVerificar)
							{
								// Verificar se ja existe peca na posicao x,y a verificar
								if (Matriz_array_invertida[i].boolTemforma == 1)
								{
									// Definir que a peca nao pode ser movida para a posicao x,y a verificar
									pecaMovida = 0;
								}

								break;
							}
						}
					}

					// Sai do ciclo caso peca nao possa ser mais movida
					if (pecaMovida == 0)
					{
						break;
					}

					posXverificar++;
				}

				// Se a peca pode ser movida entao definir o valor de Y a mover
				if (pecaMovida == 1)
				{
					pecaPodeSermovida = 1;
					pecaMovidaParaY = posYVerificar;
				}
				else
				{
					// caso peca nao possa ser movida sair do ciclo
					break;
				}

				// Fazer reset a posX
				posXverificar = formaXStart;

				// Reduzir a posYVerificar para menos 1 casa
				posYVerificar--;

				// Incrementar o nr de casas que a peca desceu
				nrDeCasasMovidasY++;
			}

			// Alterar peca na matriz
			if (pecaPodeSermovida == 1)
			{
				// Remover antiga peca da matriz
				DesenharPecasNaMatriz(MaxXYposition, formaXStart, formaXEnd, formaYStart, formaYEnd, Matriz_array_invertida, 0, ' ');

				int formaYendAterada = formaYEnd - nrDeCasasMovidasY;

				// Permitir que limite da peca ocupe mesmo espaco que outra
				if (pecaMovidaParaY != 0)
				{
					pecaMovidaParaY--;
					formaYendAterada--;
				}

				// alterar info da peca
				forma_invertida_gravidade_array[forma].x = forma_invertida_array[forma].x;
				forma_invertida_gravidade_array[forma].y = pecaMovidaParaY;


				// adicionar nova peca na matriz
				DesenharPecasNaMatriz(MaxXYposition, formaXStart, formaXEnd, pecaMovidaParaY, formaYendAterada, Matriz_array_invertida, 1, '|');
			}
		}
	}

	//printf("\n Matriz com gravidade final \n");

	// Desenhar matriz invertida com gravidade
	posMatriz = MaxXYposition;
	column = (MaxWidth - 1);

	//DesenharMatriz(MaxHeight, posMatriz, MaxXYposition, column, MaxWidth, Matriz_array_invertida);

	// Desenhar caracteres de peca final (inclusao de + e -) e remover caracteres intermedios
	for (int forma = 0; forma < nrFormas; forma++)
	{
		// obter parametros da peca
		int formaXStart = forma_invertida_gravidade_array[forma].x;
		int formaYStart = forma_invertida_gravidade_array[forma].y;
		int formaXEnd = forma_invertida_gravidade_array[forma].x + (forma_invertida_gravidade_array[forma].width - 1);
		int formaYEnd = forma_invertida_gravidade_array[forma].y + (forma_invertida_gravidade_array[forma].height - 1);


		// inserir character de vertice (+)
		for (int i = 0; i < MaxXYposition; i++)
		{
			int MatrizX = Matriz_array_invertida[i].x;
			int MatrizY = Matriz_array_invertida[i].y;

			// Caso o caracter actual nao seja (+)
			if (Matriz_array_invertida[i].character != '+')
			{
				if (MatrizY == formaYStart && (MatrizX >= formaXStart && MatrizX <= formaXEnd))
				{
					Matriz_array_invertida[i].character = '-';
				}

				if (MatrizY == formaYEnd && (MatrizX >= formaXStart && MatrizX <= formaXEnd))
				{
					Matriz_array_invertida[i].character = '-';
				}

				if ((MatrizY > formaYStart&& MatrizY < formaYEnd) && (MatrizX > formaXStart&& MatrizX < formaXEnd))
				{
					Matriz_array_invertida[i].character = ' ';
				}

				if (MatrizX == formaXStart && MatrizY == formaYStart)
				{
					Matriz_array_invertida[i].character = '+';
				}
				else if (MatrizX == formaXStart && MatrizY == formaYEnd)
				{
					Matriz_array_invertida[i].character = '+';
				}
				else if (MatrizX == formaXEnd && MatrizY == formaYStart)
				{
					Matriz_array_invertida[i].character = '+';
				}
				else if (MatrizX == formaXEnd && MatrizY == formaYEnd)
				{
					Matriz_array_invertida[i].character = '+';
				}
			}

		}
	}


	DesenharMatriz(MaxHeight, posMatriz, MaxXYposition, column, MaxWidth, Matriz_array_invertida);


	return 0;
}
