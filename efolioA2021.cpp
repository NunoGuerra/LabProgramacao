//***************************************************************
//                   HEADER FILE USADA NO PROJECTO
//***************************************************************

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<iomanip>
#include "Aluno.h"
#include "UC.h"

using namespace std;

//declaracao global de objectos

fstream fp;
Aluno a;
UC uc;

void guarda_aluno()           //funcao para guardar informacao do aluno num ficheiro
{
	a.regista_aluno();

	bool NumeroJaAtribuido = a.AlunoNrExistente(a);

	while (NumeroJaAtribuido)
	{
		a.regista_NrAluno();

		NumeroJaAtribuido = a.AlunoNrExistente(a);
	}

	a.regista_UC();

	bool AdicionarRegistos = true;
	while (AdicionarRegistos)
	{
		// verificar se nome de UC inserido ja esta registado
		bool UCNaoRegistada = uc.UCExiste(a.retuc());
		if (UCNaoRegistada == false)
		{
			cout << "\n\n Erro: Nao existe registo de UC com o nome " << a.retuc() << "\n\n";
		}
		else
		{
			// Verificar se Aluno ja esta registado na mesma UC
			bool AlunoUCExistente = a.AlunoUCExistente(a);
			if (AlunoUCExistente)
			{
				a = a.ObterAluno(a);

				if (a.retnota() > 9.5)
				{
					string melhoriaDeNota;
					cout << "\n\nEste aluno ja esta aprovado nesta UC.\n\n ";
					cout << "\n\nPretende efectuar melhoria de nota? S/N.\n ";
					cin >> melhoriaDeNota;

					if (melhoriaDeNota == "s" || melhoriaDeNota == "S")
					{
						float NotaAnterior = a.retnota();

						a.registoTipoAvaliacao();

						if (NotaAnterior < a.retnota())
						{
							a.UpdateNotaAluno(a);
						}
						else
						{
							cout << "\n\nNota nao actualizada (Inferior a nota anterior).\n\n ";
						}
					}
				}
				else
				{
					a.registoTipoAvaliacao();

					float NotaAnterior = a.retnota();

					a.registoTipoAvaliacao();

					if (NotaAnterior < a.retnota())
					{
						a.UpdateNotaAluno(a);
					}
					else
					{
						cout << "\n\nNota nao actualizada (Inferior a nota anterior).\n\n ";
					}

					if (a.retnota() < 9.5)
					{
						cout << "\n\nAluno reprovado.\n\n ";
					}
					else
					{
						cout << "\n\nAluno aprovado.\n\n ";
					}
				}
			}
			else
			{
				a.registoTipoAvaliacao();

				fp.open("Alunos.txt", ios::out | ios::app);
				fp.write((char*)&a, sizeof(Aluno));
				fp.close();

				if (a.retnota() < 9.5)
				{
					cout << "\n\nAluno reprovado.\n\n ";
				}
				else
				{
					cout << "\n\nAluno aprovado.\n\n ";
				}

				cout << "\n\nO aluno foi registado com sucesso.\n\n ";
			}
		}

		string terminarRegistos;
		cout << "\n\nDeseja registar este aluno em outra UC?. S/N\n\n ";
		cin >> terminarRegistos;

		if (terminarRegistos == "s" || terminarRegistos == "S")
		{
			a.regista_UC();
		}
		else
		{
			AdicionarRegistos = false;
		}
	}
}

int get_uc_ects(char nome[])  //funcao que verifica ects da uc
{
	fstream fst;
	int flag = 0;
	int ects = 0;
	fst.open("UCS.txt", ios::in);
	while (fst.read((char*)&uc, sizeof(UC)))
	{
		if ((_strcmpi(nome, uc.retnome())) == 0)
		{
			ects = uc.retects();
			flag = 1;
		}
	}
	fst.close();
	if (flag == 0) {
		cout << "\n\nNao existe registo";
	}

	return ects;
}

void mostra_info_aluno(char nrAluno[])    //funcao para procurar info de um estudante em especifico
{
	int flag = 0;
	int hctrl = 0;
	int ects = 0;
	int ects_total = 0;
	int count_ucs = 0;
	int calc_nota = 0;
	int nota = 0;
	double avg = 0;
	fp.open("Alunos.txt", ios::in);
	while (fp.read((char*)&a, sizeof(Aluno)))
	{
		if ((_strcmpi(nrAluno, a.retnrAluno())) == 0)
		{
			nota = a.retnota();

			if (hctrl == 0)
			{
				a.mostra_info_aluno();
				hctrl = 1;
			}

			if (nota >= 10)
			{
				ects_total += ects = get_uc_ects(a.retuc());
				a.mostra_notas_aluno(ects);

				calc_nota += nota * ects;

				++count_ucs;
			}

			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) {
		cout << "\n\nNao existe registo";
	}
	else
	{
		if (ects_total > 0)
		{
			avg = calc_nota / (double)ects_total;
		}

		a.mostra_detalhes_uc_aluno(count_ucs, ects_total, avg);
	}
}

void mostra_alunos_aprovados(char ucs[])     //funcao que verifica o numero total de estudantes aprovados na uc
{
	int flag = 0;
	int nota = 0;
	int count_aprov = 0;
	int count_nota = 0;
	double avg = 0;

	fp.open("Alunos.txt", ios::in);
	while (fp.read((char*)&a, sizeof(Aluno)))
	{
		if ((_strcmpi(ucs, a.retuc())) == 0)
		{
			nota = a.retnota();

			if (nota >= 10)
			{
				++count_aprov;
				count_nota += nota;
			}

			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) {
		cout << "\n\nAinda Nao existem alunos aprovados em " << ucs;
	}
	else
	{
		avg = (double)count_nota / count_aprov;
		uc.mostra_info_uc(ucs, avg, count_aprov);
	}
}

void guarda_uc()                      //funcao para guardar info da uc num ficheiro
{
	bool ucExist = false;
	
	uc.regista_uc();
	ucExist = uc.UCExiste(uc.retnome());
	if (ucExist == false)
	{
		fp.open("UCS.txt", ios::out | ios::app);
		fp.write((char*)&uc, sizeof(UC));
		fp.close();
		cout << "\n\nA Unidade Curricular foi registada com sucesso.\n\n ";
	}
	else
	{
		cout << "\n\nA Unidade Curricular inserida ja existe.\n\n ";
	}
}

void mostra_u_uc(char nome[])            //funcao que mostrar uma uc em especifico do ficheiro
{
	int flag = 0;
	fp.open("UCS.txt", ios::in);
	while (fp.read((char*)&uc, sizeof(UC)))
	{
		if ((_strcmpi(nome, uc.retnome())) == 0)
		{
			/*Verifica se UC existe*/
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) {
		cout << "\n\nNao existe registo";
	}
	else
	{
		/*Mostra todos os alunos aprovados nesta UC em especifico*/
		mostra_alunos_aprovados(nome);
	}
}

//Funcao Main Menu do registo de dados do curso LEI

void main_menu()
{
	char ch;
	char type;
	do
	{
		cout << "\n\tMenu Principal do curso LEI";
		cout << "\n\n\t01. Aluno";
		cout << "\n\t02. Unidade Curricular";
		cout << "\n\t03. Sair";
		cout << "\n\tPor favor escolha uma destas opcoes (1-3) ";
		cin.clear();
		cin >> ch;

		switch (ch)
		{
		case '1':
		{
			do {
				cout << "\n\n====================================\n";
				cout << "\n\tMenu Aluno";
				cout << "\n\n\t01. Registar Aluno";
				cout << "\n\t02. Verificar Informacao do aluno";
				cout << "\n\t03. Voltar ao menu principal";
				cout << "\n\tPor favor escolha uma destas opcoes (1-3) ";
				cin.clear();
				cin >> ch;
				switch (ch)
				{
				case '1':
				{
					guarda_aluno();
					break;
				}
				case '2':
				{
					char nrAluno[20];
					fflush(stdin);                                   //Usado para limpar o buffer
					cout << "\n\nPor favor insira o numero do aluno: ";
					(void)getchar();
					cin >> nrAluno;
					mostra_info_aluno(nrAluno);
					break;
				}
				case '3':
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					main_menu();
					
					break;
				}
				default:
				{
					cout << "\n\tO input inserido nao e valido, tente novamente" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				};
				}
			} while (ch != '3' && !cin.fail() && cin.good());
			break;
		}
		case '2':
		{
			do {
				cout << "\n\n====================================\n";
				cout << "\n\tMenu Unidade Curricular";
				cout << "\n\n\t01. Registar UC";
				cout << "\n\t02. Verificar info da UC";
				cout << "\n\t03. Voltar ao menu principal";
				cout << "\n\tPor favor escolha uma destas opcoes (1-3) ";
				cin.clear();
				cin >> ch;
				switch (ch)
				{
				case '1':
				{
					guarda_uc();
					break;
				}
				case '2':
				{
					char nome[50];
					fflush(stdin);
					cout << "\n\nPor favor insira a Unidade Curricular: ";
					(void)getchar();
					fgets(nome, 50, stdin);
					mostra_u_uc(nome);
					break;
				}
				case '3':
				{
					main_menu();
					break;
				}
				default:
				{
					cout << "\n\tO input inserido nao e valido, tente novamente" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				};
				}
			} while (ch != '3' && !cin.fail() && cin.good());
			break;
		}
		case '3':exit(0);
		default:
		{
			cout << "\n\tO input inserido nao e valido, tente novamente" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		};
		}
	} while (ch != '3' && !cin.fail() && cin.good());
}

//      Funcao main do programa

int main()
{
	main_menu();
}