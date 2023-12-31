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
    
    
    std::ofstream Mat1arq("./output/matriz1.bin", std::ios::binary);
    
    std::ofstream Mat2arq("./output/matriz2.bin", std::ios::binary);
    
    std::vector<std::vector<float>> elemento;

    for (int i = 0 ; i < n1; ++i){
        elemento.push_back(std::vector<float> (n1,m1));
        for (int j = 0; j < m1; ++j)
        {
            elemento[i].push_back ( generator() % 100);

        }
        
    }

    if (Mat1arq.is_open()){
        // Obtenha o tamanho do vetor
        size_t tamanho = elemento.size();

        // Escreva o tamanho do vetor no arquivo (para fins de leitura posterior)
        Mat1arq.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));

        // Escreva os dados do vetor no arquivo
        arquivo.write(reinterpret_cast<const char*>(dados.data()), sizeof(int) * tamanho);

        // Feche o arquivo
        arquivo.close();
        std::cout << "Vetor salvo com sucesso." << std::endl;
    }

    Mat1arq.close();
    
    //std::cout << "Matriz 2:" <<std::endl;
    
    if (Mat2arq.is_open()){
        Mat2arq  << n2 <<" "<< m2 << std::endl;
        for (int i = 0 ; i < n2; ++i){
            for (int j = 0; j < m2; ++j)
            {
                elemento = generator() % 100 /100.0f;
                Mat2arq << elemento << " ";
      //          std::cout <<elemento<< " ";
            }
            
            Mat2arq << std::endl;
        //    std::cout <<std::endl;
            
        }
    }

    Mat2arq.close();
    


    return 0;
}