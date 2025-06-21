#include "UC.h"

using namespace std;

fstream fpU;

void UC::regista_uc()                          //FUNCAO REGISTAR UCS
{
	fflush(stdin);                                  //Usado para limpar buffer
	cout << "\n\nPor favor inserir nome da Unidade Curricular: ";
	getchar();
	fgets(nome, 50, stdin);
	cout << "\nPor favor inserir o numero de ects: ";
	cin >> ects;
	cout << "\nPor favor inserir ano: ";
	cin >> ano;
	cout << "\nPor favor inserir semestre: ";
	cin >> semestre;
}

void UC::mostra_uc()              //FUNCAO PARA MOSTRAR UC
{
	cout << "\nNome UC: "; puts(nome);
	cout << "ECTS: " << ects;
	cout << "\n\nAno: " << ano;
	cout << "\n\nSemestre: " << semestre;
}

void UC::mostra_info_uc(string ucnome, double avg, int aprov)        //Funcao mostrar detalhes uc
{
	cout << "\n\nUNIDADE CURRICULAR: " << ucnome;
	cout << "\n\nTotal de alunos aprovados: " << aprov;
	cout << "\n\nMedia: " << setprecision(5) << avg;
}

char* UC::retnome()
{
	return nome;
}

int UC::retects()
{
	return ects;
}

bool UC::UCExiste(char* NomeUC)
{
	bool ExisteUC = false;
	UC u;

	fpU.open("UCS.txt", ios::in);
	while (fpU.read((char*)&u, sizeof(UC)))
	{
		int op = 0;

		// Verificar se nome de UC ja existe
		if (_strcmpi(NomeUC, u.retnome()) == 0)
		{
			ExisteUC = true;
			break;
		}
	}

	fpU.close();

	return ExisteUC;
}
;