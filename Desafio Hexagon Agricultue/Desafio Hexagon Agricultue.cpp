#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <locale>

using namespace std;

float sinal(float x);

#define RAD_2_DEG 57.29577951307854999853275233034

int main()
{
	setlocale(LC_ALL, "Portuguese"); // Para usar acentos no console

	ifstream arquivo("attitude_exam.log");
	if (arquivo.is_open())
	{
		ofstream saida("pitch_roll.txt");
		if (!saida.is_open())
		{
			arquivo.close();
			cout << "Não foi possível criar o arquivo de saída. Verifique suas permissões." << endl;
		}

		string linha;
		size_t pos;
		float Gpx, Gpy, Gpz;
		float roll, pitch;
		const float u = 0.001;

		cout << "Arquivo aberto com sucesso. Iniciando calculos" << endl << endl;


		while (getline(arquivo, linha))
		{
			/* Etapas:
				1 - O timestamp parece não ser relevante (se utilizar as eqs 37 e 38 do AN3461)
				2 - Parse na string para adquirir as medidas.
				3 - O acelerômetro em 8g tem 1024 counts/g. Então deve-se dividir os números por 1024.
				4 - Por convenção, segundo o AN3461, negar a entrada do acelerometro para que eixo alinhado com a gravidade resulte em +1g.
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

			// Divide por 1024 (8g scale = 1024 counts/g) e nega a entrada.
			Gpx /= -1024.0;
			Gpy /= -1024.0;
			Gpz /= -1024.0;

			// Calcula os valores
			pitch = atan2(-Gpx, sqrt(Gpy*Gpy + Gpz*Gpz)); // Eq 37 utilizando atan2 para evitar duplicidade de soluções
			roll = atan2(Gpy, sinal(Gpz)*sqrt(Gpz*Gpz + u*Gpx*Gpx)); // Eq 38 com artificio para previnir instabilidade

			// Escreve os valores de Roll e Pitch, nesta ordem, em graus.
			saida << roll*RAD_2_DEG << "; " << pitch*RAD_2_DEG << endl;
		}

		cout << "Final do arquivo." << endl << endl;

		arquivo.close();

		cout << "O arquivo de saída gerado é \'pitch_roll.txt\'." << endl;
		cout << "O formato da saída é, em graus: roll; pitch" << endl;
	} 
	else
	{
		cout << "Não foi possível abrir o arquivo de log! Verifique se ele se encontra na pasta correta.";
	}

	getchar();

    return 0;
}

float sinal(float x)
{
	if (x < 0) return -1;
	if (x == 0) return 0;
	return 1;
}
