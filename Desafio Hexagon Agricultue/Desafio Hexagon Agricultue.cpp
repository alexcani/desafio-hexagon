#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
	ifstream arquivo("attitude_exam.log");
	if (arquivo.is_open())
	{
		string linha;
		size_t pos;
		float Gpx, Gpy, Gpz;
		float roll, pitch;

		cout << "Arquivo aberto com sucesso. Iniciando calculos" << endl << endl;

		while (getline(arquivo, linha))
		{
			/* Etapas:
				1 - O timestamp parece não ser relevante (se utilizar as eqs 37 e 38 do AN3461)
				2 - Parse na string para adquirir as medidas.
				3 - O acelerômetro em 8g tem 1024 counts/g. Então deve-se dividir os números por 1024.
				4 - Aplicar as fórmulas e escrever no arquivo.
			*/

			pos = linha.find("; "); // Os dados de interesse são separados por '; '
			linha = linha.substr(pos + 2); // Despreza o timestamp

			pos = linha.find("; ");
			Gpx = stof(linha, &pos); // Pega Gpx

			linha = linha.substr(pos + 2);
			Gpy = stof(linha, &pos); // Pega Gpy

			linha = linha.substr(pos + 2);
			Gpz = stof(linha); // Pega Gpy

			// Divide por 1024 (8g scale = 1024 counts/g)
			Gpx /= 1024.0;
			Gpy /= 1024.0;
			Gpz /= 1024.0;
		}

		cout << "Final do arquivo" << endl;

		arquivo.close();
	} 
	else
	{
		cout << "Não foi possível abrir o arquivo de log! Verifique se ele se encontra na pasta correta.";
	}
    return 0;
}

