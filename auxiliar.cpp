#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

int main(int argc, char const *argv[])
{
    int n1, m1, n2, m2;



    if (argc < 5 ){
        std::cout << "Não foram passados parâmetros suficiente na chamada da função main"<<std::endl;
        return 0;
    }
 
    n1 = std::stoi(argv[1]);
    m1 = std::stoi(argv[2]);
    n2 = std::stoi(argv[3]);
    m2 = std::stoi(argv[4]);

    if (m1 != n2){
        std::cout << "O número de colunas da matriz n1 x m1 deve ser igual ao de linhas da matriz n2 x m2, isto é m1 = n2" << std::endl;
        return 0;
    }

    
    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::minstd_rand0 generator (seed);  // minstd_rand0 is a standard linear_congruential_engine
    
    
    std::ofstream Mat1arq("matriz1.txt");
    
    std::ofstream Mat2arq("matriz2.txt");
    
    float elemento = 0;

    std::cout << "Matriz 1:" <<std::endl;
    if (Mat1arq.is_open()){
        Mat1arq  << " n x m "<<n1<<" "<< m1 << std::endl;
        for (size_t i = 0 ; i < n1; ++i){
            for (size_t j = 0; j < m1; ++j)
            {
                elemento = generator() % 100 /10.0f;
                Mat1arq << elemento << " ";
                std::cout <<elemento<< " ";
            }
            Mat1arq << std::endl;
            std::cout <<std::endl;
            
        }
    }

    Mat1arq.close();
    
    std::cout << "Matriz 2:" <<std::endl;
    
    if (Mat2arq.is_open()){
        Mat2arq  << " n x m "<< n2 <<" "<< m2 << std::endl;
        for (size_t i = 0 ; i < n1; ++i){
            for (size_t j = 0; j < m1; ++j)
            {
                elemento = generator() % 100 /10.0f;
                Mat2arq << elemento << " ";
                std::cout <<elemento<< " ";
            }
            
            Mat2arq << std::endl;
            std::cout <<std::endl;
            
        }
    }

    Mat2arq.close();
    


    return 0;
}