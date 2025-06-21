
#ifndef ALUNO_H_
#define ALUNO_H_

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<iomanip>

using namespace std;

class Aluno
{
private :

	char nome[50], uc[50], nrAluno[10];
	double nota;

public:

	void regista_aluno();
	void regista_NrAluno();
	void regista_UC();
	void registoTipoAvaliacao();
	void mostra_info_aluno();                       
	void mostra_notas_aluno(int ects);               
	void mostra_detalhes_uc_aluno(int uctotal, int ectstotal, double avg);
	char* retnome();
	char* retuc();
	double retnota();
	char* retnrAluno();
	bool AlunoUCExistente(Aluno);
	bool AlunoNrExistente(Aluno);
	Aluno ObterAluno(Aluno);
	void UpdateNotaAluno(Aluno aluno);
};
#endif
