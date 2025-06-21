#include "Aluno.h"
#include <limits>

using namespace std;

fstream fpA;

void Aluno::regista_aluno()                          //FUNCAO PARA REGISTAR ALUNOS
{
	fflush(stdin);                                   //Usado para limpar buffer
	cout << "\n\nPor favor inserir nome do aluno: ";
	(void)getchar();
	fgets(nome, 50, stdin);
	cout << "\nPor favor inserir numero de aluno: ";
	cin >> nrAluno;
	fflush(stdin);
}

void Aluno::regista_NrAluno()                          //FUNCAO PARA REGISTAR ALUNOS
{
	cout << "\nNumero de Aluno inserido ja atribuido.";
	cout << "\nPor favor insira outro numero de aluno: ";
	(void)getchar();
	cin >> nrAluno;
}

void Aluno::regista_UC()                          //FUNCAO PARA REGISTAR ALUNOS
{
	cout << "\n\nPor favor inserir UC a inscrever: ";
	(void)getchar();
	fgets(uc, 50, stdin);
}

void Aluno::registoTipoAvaliacao()
{
	char ch;
	int nrEfolios;
	cin.clear();

	cout << "\n\n====================================\n";
	cout << "\n Escolher Metodo de Avaliacao : ";
	cout << "\n\n\t01. Avaliacao Continua";
	cout << "\n\t02. Exame Final";
	cout << "\n\tPor favor escolha uma destas opcoes (1-2) ";

	cin >> ch;

	switch (ch)
	{
	case '1':
	{
		//0,1,2
		nrEfolios = 2;
		float NotaEfolios = 0;
		string efolio;
		char sEfolios[] = { 'A', 'B', 'C' };
		bool somaEfoliosValid = false;

		while (somaEfoliosValid == false)
		{
			for (int i = 0; i <= nrEfolios; i++)
			{
				bool validInput = false;

				while (validInput == false)
				{
					float NotaEfolio = 0;

					cout << "\n\nInserir nota de efolio" << sEfolios[i] << ": ";

					cin >> NotaEfolio;

					if (NotaEfolio >= 0 && NotaEfolio <= 5 && !cin.fail() && cin.good())
					{
						NotaEfolios = (NotaEfolios + NotaEfolio);
						validInput = true;
					}
					else
					{
						cout << "\n\nValor inserido invalido:";
					}

					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}

			if (NotaEfolios >= 0 && NotaEfolios <= 8)
			{
				somaEfoliosValid = true;
			}
			else
			{
				cout << "\n\nA soma dos efolios não pode ser superior a 8:";
				NotaEfolios = 0;
			}
		}

		if (NotaEfolios >= 3.5)
		{
			bool pfolioValid = false;
			double NotaPFolio = 0;

			while (pfolioValid == false)
			{
				cout << "\n\nInserir nota de pfolio (0 a 12) :";
				cin >> NotaPFolio;

				if (NotaPFolio >= 0 && NotaPFolio <= 12 && !cin.fail() && cin.good())
				{
					pfolioValid = true;
				}
				else
				{
					cout << "\n\nValor inserido invalido:";
				}

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			if ((NotaPFolio >= 5.5 && NotaEfolios >= 3.5) && ((NotaPFolio + NotaEfolios) >= 9.5))
			{
				double NotaFinal = (NotaPFolio + NotaEfolios);
				nota = NotaFinal;
			}
			else
			{
				bool pfolioRecValid = false;
				double NotaPfolioRecurso = 0;

				while (pfolioRecValid == false)
				{
					cout << "\n\nInserir nota de pfolio de recurso (0 a 12) :";
					cin >> NotaPfolioRecurso;

					if (NotaPfolioRecurso >= 0 && NotaPfolioRecurso <= 12 && !cin.fail() && cin.good())
					{
						pfolioRecValid = true;
					}
					else
					{
						cout << "\n\nValor inserido invalido:";
					}

					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				double NotaFinal = (NotaPfolioRecurso + NotaEfolios);
				nota = NotaFinal;
			}
		}
		else
		{
			bool inpExValid = false;
			double NotaExameRecurso = 0;

			while (inpExValid == false)
			{
				cout << "\n\nInserir nota de exame de recurso (0 a 20) :";
				cin >> NotaExameRecurso;

				if (NotaExameRecurso >= 0 && NotaExameRecurso <= 20 && !cin.fail() && cin.good())
				{
					inpExValid = true;
				}
				else
				{
					cout << "\n\nValor inserido invalido:";
				}

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			nota = NotaExameRecurso;
		}
		break;
	}
	case '2':
	{
		double NotaExame = 0;
		double NotaExameRecurso = 0;
		bool inpExamevalid = false;

		while (inpExamevalid == false)
		{
			cout << "\n\nInserir nota de exame (0 a 20) : ";
			cin >> NotaExame;

			if (NotaExame >= 0 && NotaExame <= 20 && !cin.fail() && cin.good())
			{
				inpExamevalid = true;
			}
			else
			{
				cout << "\n\nValor inserido invalido:";
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		
		nota = NotaExame;

		if (NotaExame < 9.5)
		{
			inpExamevalid = false;

			while (inpExamevalid == false)
			{
				cout << "\n\nInserir nota de exame de recurso (0 a 20): ";
				cin >> NotaExameRecurso;

				if (NotaExameRecurso >= 0 && NotaExameRecurso <= 20 && !cin.fail() && cin.good())
				{
					inpExamevalid = true;
				}
				else
				{
					cout << "\n\nValor inserido invalido:";
				}

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			
			nota = NotaExameRecurso;
		}
		break;
	}
	default:
	{
		cout << "\n\tO input inserido nao e valido, tente novamente" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		break;
	};
	}
}

void Aluno::mostra_info_aluno()                         //Mostrar info do aluno
{
	cout << "\nALUNO: " << nome << "\n" << endl;
	cout << "Unidades Curriculares onde obteve aprovacao\n" << endl;
	cout << left << setw(25) << "UC" << setw(25) << "ECTS" << setw(25) << "Nota\n" << endl;
}

void Aluno::mostra_notas_aluno(int ects)                         //Mostrar notas do aluno
{
	string sUC = uc;

	cout << left << setw(25) << sUC.erase(sUC.length() - 1) << setw(25) << ects << setw(25) << nota << endl;
}

void Aluno::mostra_detalhes_uc_aluno(int uctotal, int ectstotal, double avg)  // Mostrar os detalhes das ucs do aluno
{
	cout << "\n\nTotal de UC: " << uctotal << "\n" << endl;
	cout << "Total de ECTS: " << ectstotal << "\n" << endl;
	cout << "Media: " << setprecision(3) << avg << "\n" << endl;

	if (ectstotal >= 180)
	{
		cout << "\n\nParabens pela conclusao do curso, senhor engenheiro! :)" << endl;
	}
}
char* Aluno::retnome()
{
	return nome;
}
char* Aluno::retuc()
{
	return uc;
}
double Aluno::retnota()
{
	return nota;
}

char* Aluno::retnrAluno()
{
	return nrAluno;
}

bool Aluno::AlunoUCExistente(Aluno aluno)
{
	bool ExisteAlunoUC = false;
	Aluno a;

	fpA.open("Alunos.txt", ios::in);
	while (fpA.read((char*)&a, sizeof(Aluno)))
	{
		int op = 0;

		// Verificar se aluno corrente tem o mesmo nr
		if (_strcmpi(aluno.nrAluno, a.retnrAluno()) == 0)
		{
			// Verificar se aluno corrente ja tem nota na mesma UC
			if (_strcmpi(aluno.uc, a.retuc()) == 0)
			{
				// definir resultado como ja existente
				ExisteAlunoUC = true;
				break;
			}
		}
	}

	fpA.close();

	return ExisteAlunoUC;
}

Aluno Aluno::ObterAluno(Aluno aluno)
{
	Aluno a;

	fpA.open("Alunos.txt", ios::in);
	while (fpA.read((char*)&a, sizeof(Aluno)))
	{
		// Verificar se aluno corrente tem o mesmo nr
		if (_strcmpi(aluno.nrAluno, a.retnrAluno()) == 0)
		{
			// Verificar se aluno corrente ja tem nota na mesma UC
			if (_strcmpi(aluno.uc, a.retuc()) == 0)
			{
				break;
			}
		}
	}

	fpA.close();

	return a;
}

void Aluno::UpdateNotaAluno(Aluno aluno)
{
	Aluno a;

	fstream fpTemp;

	fpA.open("Alunos.txt", ios::in);
	while (fpA.read((char*)&a, sizeof(Aluno)))
	{
		// Verificar se aluno corrente tem o mesmo nr
		if (_strcmpi(aluno.nrAluno, a.retnrAluno()) == 0)
		{
			// Verificar se aluno corrente ja tem nota na mesma UC
			if (_strcmpi(aluno.uc, a.retuc()) == 0)
			{
				a.nota = aluno.nota;
			}
		}

		fpTemp.open("Alunos_Temp.txt", ios::out | ios::app);
		fpTemp.write((char*)&a, sizeof(Aluno));
		fpTemp.close();
	}
	fpA.close();

	// remover ficheiro de dados
	int result = remove("Alunos.txt");
	if (result != 0)
	{
		cout << "\n\nErro ao actualizar a nota.Pff tente novamente.\n\n ";
	}
	else
	{
		// Alterar ficheiro de dados temporario para ficheiro de dados efectivo 
		int result = rename("Alunos_Temp.txt", "Alunos.txt");

		cout << "\n\nNota actualizada com sucesso.\n\n ";
	}
}

bool Aluno::AlunoNrExistente(Aluno aluno)
{
	bool ExisteAlunoNr = false;
	Aluno a;

	fpA.open("Alunos.txt", ios::in);
	while (fpA.read((char*)&a, sizeof(Aluno)))
	{
		int op = 0;

		// Verificar se aluno corrente tem o mesmo nr
		if (_strcmpi(aluno.nrAluno, a.retnrAluno()) == 0)
		{
			if (_strcmpi(aluno.nome, a.retnome()) != 0)
			{
				// definir resultado como ja existente
				ExisteAlunoNr = true;
				break;
			}
		}
	}

	fpA.close();

	return ExisteAlunoNr;
}