#ifndef ARQUIVOS_HPP
#define ARQUIVOS_HPP


#include <vector>
#include <fstream>


void salvaArq(const std::vector<std::vector<float>> &M, const long long & microseconds, const std::string &nome){

    int n1 = M.size();
    
    int m1 = M[0].size();

    std::string Arq = "./output/Prod_th";


    Arq.append(nome);
    
    Arq.append(".txt");

    std::ofstream Mat1arq(Arq);

    if (Mat1arq.is_open()){
        Mat1arq << nome <<std::endl;
        Mat1arq  << n1<<" "<< m1 << std::endl;
        for (size_t i = 0 ; i < n1; ++i){
            for (size_t j = 0; j < m1; ++j)
            {
                Mat1arq << M[i][j] << " ";
            }
            Mat1arq << std::endl;
            
        }
        Mat1arq << microseconds<<std::endl;
    }

    Mat1arq.close();
}

void salvaArq(const std::vector<float> &dados, int n1, int m1, const std::vector<int> &indices, const long long & microseconds, const std::string &nome){
    
    //formato de arquivo de saida
    // n1 m1
    // indice[0] dados[0] 
    // indice[1] dados[1] 
    // ... 
    // indice[end]  dados[end]
    // microseconds

    std::string Arq = "./output/Prod_th";


    Arq.append(nome);
    Arq.append("_");
    
    std::ofstream Mat1arq(Arq);

    if (Mat1arq.is_open()){
        Mat1arq << nome <<std::endl;
        Mat1arq  << n1<<" "<< m1 << std::endl;
        
        int tam = indices.size();
        
        for (size_t i = 0 ; i < tam; ++i){
           Mat1arq << indices[i] << " " << dados[i] << std::endl;
        }
        

        Mat1arq << microseconds<<std::endl;
    }

    Mat1arq.close();
}


std::vector<std::vector<float>> abrirArquivoMatriz(std::string M1nomeArq){

    std::ifstream Mat1arq(M1nomeArq);

    int n1, m1;

    float elemento = 0;

    std::vector<float> linha;

    std::vector<std::vector<float>> M1;

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

    return M1;
 }

#endif