#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cstdio>
#include <sys/stat.h>


int main(int argc, char const *argv[]){

    // Comando a ser executado
    std::string diretorio = "./build/paralelo";
    std::string output = "./output/matriz1.txt ./output/matriz2.txt";
    std::string P = argv[1];

    int Nvezes = 10;
    std::string diretorio_p = "./output/paralelo/";

    for (int i = 0; i< Nvezes ;++i){
        auto nome_arq = "P" + P + "_" + std::to_string(i) + ".txt";        
        std::string comando = diretorio + " " + output + " " + P + " >> " + diretorio_p + nome_arq;
        std::cout << comando << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        int status = std::system(comando.c_str());
        auto stopTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count();

        // Verificar o status de saída do comando
        if (status == 0) {
            std::cout << "Comando executado com sucesso em " << duration << " micro segundos." << std::endl;
        } else {
            std::cerr << "Erro ao executar o comando." << std::endl;
        }
    }

    return 0;
}

