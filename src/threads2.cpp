#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <thread>
#include "../includes/matriz.hpp"
#include "../includes/arquivos.hpp"

// comando para remover arquivos das matrizes
//rm $ dir ./output/Prod*.txt

//compilar
//g++ ./src/thread2.cpp -o ./build/thread -pthread

class ThreadsObj{

    public:
    std::thread th;
    std::vector<std::vector<float>> Prod;
    std::vector<int> indices;
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;

    void start(){
       this->t1 = std::chrono::high_resolution_clock::now();

    }
    void stop(){
       this->t2 = std::chrono::high_resolution_clock::now();


    }
    void setIndices(int inicio, int passo, int fim){
        this->indices = rangeIndices(inicio, passo, fim);
    }
};


int main(int argc, char const *argv[])
{
    int n1, m1, n2, m2;
    std::string M1nomeArq, M2nomeArq;

    std::vector<float> linha;

    std::vector<std::vector<float>> M1;
    std::vector<std::vector<float>> M2;
    


    if (argc < 3 ){
        std::cout << "Não foram passados parâmetros suficiente na chamada da função main"<<std::endl;
        return 0;
    }
 
    M1nomeArq = argv[1];
    M2nomeArq = argv[2];
    int P = std::stoi(argv[3]);

           
    M1=abrirArquivoMatriz(M1nomeArq);

    n1= M1.size();

    M2=abrirArquivoMatriz(M2nomeArq);

    m2 = M2[0].size();

    int Nthreads = n1*m2 / P;

    //std::cout<<"M1:"<<std::endl;
    //printMatrix(M1);
    
    //std::cout<<"M2:"<<std::endl;
    //printMatrix(M2);
    
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<float>> Prod(n1, std::vector <float> (n2,0));

    std::vector<int> indices = rangeIndices(0,1,3);

    std::vector<ThreadsObj> threads(Nthreads);

    int inicio = 0;
    int passo = 1;
    int fim = P;
    for (auto &th:threads){

        th.indices.clear();

        th.setIndices(inicio, passo, fim);
        
        inicio = fim;
        
        fim = fim + P;
        
        th.start();
        
        th.th = std::thread (Produtothread2,M1,M2,th.indices, std::ref(th.Prod));
        
        th.stop();

    }

    int k = 0;
    
    for (auto &th:threads){
        
        //if(threads[i].th.joinable()){
        th.th.join();
        th.stop();
        
        // Calcula a diferença de tempo

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(th.t2 - th.t1);
        
        // Converte a duração para um valor numérico (microsegundos)
        
        long long microseconds = duration.count();

        salvaArq(th.Prod,microseconds,std::to_string(k));
        k++;
    }
    
   return 0;

}