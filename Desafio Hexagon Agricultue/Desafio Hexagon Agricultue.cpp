#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;
int main()
{
	ifstream arquivo("attitude_exam.log");
	if (arquivo.is_open())
	{
		cout << "Arquivo aberto com sucesso";
	} 
	else
	{
		cout << "Não foi possível abrir o arquivo de log! Verifique se ele se encontra na pasta correta.";
	}
    return 0;
}

