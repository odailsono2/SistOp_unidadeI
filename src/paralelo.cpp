#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <thread>
#include <sys/wait.h>
#include "../includes/matriz.hpp"
#include "../includes/arquivos.hpp"



int main(int argc, char const *argv[])
{
    int n1, m1, n2, m2;
    std::string M1nomeArq, M2nomeArq;

    std::vector<int> linha;


    if (argc != 4 ){
        std::cout << "Não foram passados parâmetros suficiente na chamada da função main"<< std::endl;
        return 0;
    }
 
    int P = std::stoi(argv[3]); //quantidade por processo
           
    std::vector<std::vector<int>> M1 = abrirArquivoMatriz(argv[1]);
    n1 = M1.size();
    std::cout << n1 << std::endl;
    
    std::vector<std::vector<int>> M2 = abrirArquivoMatriz(argv[2]);
    m2 = M2.size();
    std::cout << m2 << std::endl;

    std::cout << "P: " << P << std::endl;
    int indiceStart = 0;
    int indiceStop = 0;
    int qtdProcessos = 0;
    for(int i = P;i < (n1*m2)+P;i+=P){
        indiceStart = indiceStop;
        indiceStop = (i >= n1*m2) ? n1*m2 : i;
        pid_t pid = fork();
        
        
        if(pid == -1){
            i-=P;
            continue;
        }        

        if(pid == 0){
            std::vector<int> indices = rangeIndices(indiceStart, 1, indiceStop);        
            auto startTime = std::chrono::high_resolution_clock::now();
            std::vector<int> produto = ProdutothreadVector(M1,M2,indices);
            auto stopTime = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count();
            std::cout << "[" << pid << "] start: " << indiceStart << " ; stop: " << indiceStop << " - Tempo gasto = " << duration << " micro segundos" << std::endl;

            qtdProcessos += 1;
            return 0;
        }

    }

    
    for(int i = 0;i <= qtdProcessos;i++){
        wait(NULL); // Espera todos os processos terminarem, antes de encerrar o processo pai
    }

    return 0;

}   
