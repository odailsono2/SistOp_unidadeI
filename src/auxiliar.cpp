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
    
    
    std::ofstream Mat1arq("./output/matriz1.txt");
    
    std::ofstream Mat2arq("./output/matriz2.txt");
    
    float elemento = 0;

    if (Mat1arq.is_open()){
        Mat1arq  << n1<<" "<< m1 << std::endl;
        for (int i = 0 ; i < n1; ++i){
            for (int j = 0; j < m1; ++j)
            {
                elemento = generator() % 10;
                Mat1arq << elemento << " ";
            }
            Mat1arq << std::endl;
        }
    }

    Mat1arq.close();
    
    if (Mat2arq.is_open()){
        Mat2arq  << n2 <<" "<< m2 << std::endl;
        for (int i = 0 ; i < n2; ++i){
            for (int j = 0; j < m2; ++j)
            {
                elemento = generator() % 10;
                Mat2arq << elemento << " ";
            }
            
            Mat2arq << std::endl;
        }
    }

    Mat2arq.close();
    


    return 0;
}