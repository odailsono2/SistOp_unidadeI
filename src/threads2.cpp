#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <thread>
#include <algorithm>
#include "../includes/matriz.hpp"
#include "../includes/arquivos.hpp"

// comando para remover arquivos das matrizes
//rm $ dir ./output/Prod*.txt

//compilar
//g++ ./src/thread2.cpp -o ./build/thread -pthread

class ThreadsObj{

    public:
    std::thread th;
    std::vector<float> Prod;

    std::vector<int> indices;
    
    long long microseconds;

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
    int salvar = 1; // 1- salva arquivo das matrizes. 0 -não

    if (argv[4]){
        salvar = std::stoi(argv[4]);
    }

    // std::cout<<M1nomeArq<<std::endl;

    // std::cout<<M2nomeArq<<std::endl;
           
    M1=abrirArquivoMatriz(M1nomeArq);

    n1= M1.size();

    M2=abrirArquivoMatriz(M2nomeArq);



    m2 = M2[0].size();

    int Nthreads = n1*m2 / P;

    //std::cout<<"M1:"<<std::endl;
    //printMatrix(M1);
    
    //std::cout<<"M2:"<<std::endl;
    //printMatrix(M2);
    
    //auto start = std::chrono::high_resolution_clock::now();

    //std::vector<std::vector<float>> Prod(n1, std::vector <float> (n2,0));

    //std::vector<int> indices = rangeIndices(0,1,3);

    std::vector<ThreadsObj> threads(Nthreads);

    int inicio = 0;
    int passo = 1;
    int fim = P;

    for (auto &th:threads){

        th.indices.clear();

        th.setIndices(inicio, passo, fim);
        
        inicio = fim;
        
        fim = fim + P;
        
       
        
    }

    for (auto &th:threads){


        th.th = std::thread (Produtothread2,M1,M2,th.indices, std::ref(th.Prod),std::ref(th.microseconds));

                  
        
    }

    int k = 0;



    int conta_threads = 0;


    while (conta_threads <= Nthreads-1){


        if (threads[k].th.joinable()){

            threads[k].th.join();

             conta_threads ++;


           

        }

        k++;

        if (k >= Nthreads){
            k = 0;
        }
    }

    std::vector<long long> tempos;
    k = 0;

    for(auto &th:threads){

            tempos.push_back(th.microseconds);

            if (salvar == 1){
                salvaArq(th.Prod,n1,m2,th.indices, th.microseconds,std::to_string(k)+std::to_string(P));
                std::cout<<"Matriz da Thread "<< k <<" salva"<<std::endl;
                k++;
            }
    }

    auto max_element_iterator = std::max_element(tempos.begin(), tempos.end());

    int indice_do_maior_elemento = std::distance(tempos.begin(), max_element_iterator);
    std::cout<<"Thread com maior tempo: "<< indice_do_maior_elemento<<std::endl;
    std::cout<<"Maior tempo : "<< static_cast<long long> (*max_element_iterator)<<std::endl;
   // std::cout<<"Maior tempo : "<<static_cast<long long> ( * std::max_element( tempos.begin() , tempos.end() ) ) << " microssegundos."<<std::endl ;
    
    return 0;

}   
