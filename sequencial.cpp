#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

std::vector<std::vector<float>> Produto(const std::vector<std::vector<float>> &M1, 
                                const std::vector<std::vector<float>> &M2){

    int n1 = M1.size();
    int m2 = M2.size();
    float elemento;
    std::vector<std::vector<float>> Prod(n1, std::vector<float> (m2,0));

    for (size_t i = 0 ; i < n1; ++i){
        for (size_t j = 0; j < m2; ++j)
        {
            for (size_t k = 0; k < n1; ++k){

                elemento =  M1[i][k] * M2[k][j];

                //std::cout <<elemento<< " ";

                Prod[i][j] += elemento;
            }
        }
//        std::cout <<std::endl;

    }

    return Prod;

}

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
    
        
           
    std::ifstream Mat1arq(M1nomeArq);
       
    std::ifstream Mat2arq(M2nomeArq);

    
    float elemento = 0;

   // std::cout << "Lendo Matriz 1 do arquivo:" << M1nomeArq <<std::endl;
    
    if (Mat1arq.is_open()){
        Mat1arq  >> n1 >> m1;
  //      std::cout  << " n x m "<<n1<<" x "<< m1 << std::endl;

        linha.resize(m1);

        M1.resize(n1);

        for (size_t i = 0 ; i < n1; ++i){

            M1[i].resize(m1);

            for (size_t j = 0; j < m1; ++j)
            {
                Mat1arq >> elemento ;
   //             std::cout <<elemento<< " ";
                linha[j] = elemento;
            }

            M1[i]=linha;

   //         std::cout <<std::endl;
            
        }
    }

    Mat1arq.close();
    
  //  std::cout << "Lendo Matriz 2 do arquivo:" << M2nomeArq <<std::endl;

     if (Mat2arq.is_open()){
        Mat2arq >> n2 >> m2;
    //    std::cout  << " n x m "<<n2<<" x "<< m2 << std::endl;

        linha.resize(0);

        linha.resize(m2);
        M2.resize(n2);

        for (size_t i = 0 ; i < n2; ++i){

            M2[i].resize(m2);

            for (size_t j = 0; j < m2; ++j)
            {
                Mat2arq >> elemento ;
       //         std::cout <<elemento<< " ";
                linha[j] = elemento;
            }

            M2[i]=linha;

       //     std::cout <<std::endl;
            
        }
    }


    Mat2arq.close();

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<float>> Prod(n1, std::vector <float> (n2,0));
    
    Prod = Produto(M1,M2);

    auto end = std::chrono::high_resolution_clock::now();

    // Calcula a diferença de tempo
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Converte a duração para um valor numérico (microsegundos)
    long long microseconds = duration.count();
    
    std::cout << "Tempo de execução: " << microseconds << " microssegundos" << std::endl;
    
    std::ofstream Produto("ProdutoM1M2.txt");
    
    elemento = 0;

 //   std::cout << "Porduto M1 x M2:" <<std::endl;
    if (Produto.is_open()){
        Produto  <<n1<<" "<< m1 << std::endl;
     //   std::cout  <<n1<<" "<< m1 << std::endl;
        for (size_t i = 0 ; i < n1; ++i){
            for (size_t j = 0; j < m1; ++j)
            {
                elemento = Prod[i][j];
                Produto << elemento << " ";
//                std::cout <<elemento<< " ";
            }
            Produto << std::endl;
 //           std::cout <<std::endl;
            
        }
    }

    Produto.close();


    
    


    return 0;
}