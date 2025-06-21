#ifndef UC_H_
#define UC_H_
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<iomanip>

using namespace std;

class UC
{
private:
    
	int ects, ano, semestre;                 
	char nome[50];

public:

    void regista_uc();                      
	void mostra_uc();
	void mostra_info_uc(string ucnome, double avg, int aprov);
	char* retnome();
	int retects();
	bool UCExiste(char* NomeUC);
};         
#endif