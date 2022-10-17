#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>


// Crear un archivo con una lista de TAM números de 0 a MAXNUM
void generadorNumRandom(std::string nameFile, int TAM, int MAXNUM)
{
    std::ofstream numbersFile;
    numbersFile.open(nameFile);

    int num;
    for (int i = 0; i < TAM; i++)
    {
        // num = 1 + rand() % (MAXNUM);
        numbersFile << i+1 << "\n";
    }
    numbersFile.close();
}


// Guardar en archivo TIMEFILE la DURATION de ejecución en milisec de un INPUT (entrada)
void timesFile(std::string TIMEFILE ,int input, std::chrono::nanoseconds duration)
{
    // Crear archivo
    std::ofstream outfile;
    outfile.open(TIMEFILE, std::ios::app);
    int _duration = duration.count();
    outfile << input << ", " << _duration << "\n";
    outfile.close();
}
