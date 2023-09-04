#include <iostream>
#include <sstream>
#include <chrono>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

std::mutex mtx;

std::vector<float> linhaMatriz(const std::vector<std::vector<float>> &M1, int indice){

    int N = M1[indice].size();

    std::vector<float>  linha(N);

    for(int i = 0; i < N; ++i){
        linha[i] = M1[indice][i];
    }

    return linha;
}

std::vector<float> colunaMatriz(const std::vector<std::vector<float>> &M1, int indice){

    int N = M1.size();

    std::vector<float>  coluna(N);

    for(int k = 0; k < N; ++k){
        coluna[k] = M1[k][indice];
      //  std::cout<<"linha "<< k <<"col "<< indice<< "Elemento: "<< M1[k][indice]<<std::endl;
        
    }
    //printVetor(coluna);
    return coluna;
}

void printVetor(const std::vector<float>  &linha){
    for (auto &i : linha)
    {
        std::cout << i <<" ";
    }
    std::cout<<std::endl;
}

void printMatrix(const std::vector<std::vector<float>>  &M){
    
    int n1 = M.size();
    int m1 = M[0].size();
    std::vector<float> linha(m1);

    for (size_t i = 0; i < n1; ++i)
    {
        linha = linhaMatriz(M,i);
        
        printVetor(linha);
    }
}

void calcElementoIJ( const std::vector<float>  &linha, const std::vector<float>  &coluna, float &produto){
    
    float elemento = 0;

    int n1=linha.size();

    produto = 0;

    for (size_t k = 0; k < n1; ++k){

        elemento =  linha[k] * coluna[k];

   
        produto += elemento;
    }



}

void salvaArq(const std::vector<std::vector<float>> &M, const long long & microseconds, int indice){

    int n1 = M.size();
    
    int m1 = M[0].size();

    std::string Arq;

    Arq  = std::to_string(indice);
    Arq.append(".txt");
    
    std::ofstream Mat1arq(Arq);

    if (Mat1arq.is_open()){
        Mat1arq << indice<<std::endl;
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

void Produto(const std::vector<std::vector<float>> &M1, 
            const std::vector<std::vector<float>> &M2, 
            int indice_inicial, 
            int qtdElementos, 
            std::vector<std::vector<float>>& Resultado, int indice){
    
    auto start = std::chrono::high_resolution_clock::now();
    
    int n1 = M1.size();
    
    int m2 = M2[0].size();
    
    int contaThread=0, cont= -1;
    
    float elemento;
    
    std::vector<std::vector<float>> Prod(n1, std::vector<float> (m2,0));

    std::vector<float> linha;
    std::vector<float> coluna;

    //int Coord_i = (int) (indice_inicial/m2);
    //int Coord_j = indice_inicial%m2;

    //std::cout << Coord_i <<", "<<Coord_j<< std::endl;

    for (size_t i = 0 ; i < n1; ++i){

        linha = linhaMatriz(M1,i);

        //std::cout<<"Linha:"<<std::endl;
        //printVetor(linha);

        for (size_t j = 0; j < m2; ++j)
        {
            
            cont ++;

            if (cont < indice_inicial)
            {
            
                continue;
                contaThread = 0;
            
             
            }
            
            if (contaThread >= qtdElementos){
            
                 break;
            
            }

            coluna = colunaMatriz(M2,j);
            
            //std::cout<<"Coluna:"<<std::endl;
            //printVetor(coluna);

            calcElementoIJ(linha,coluna,elemento);
           
            Prod[i][j] = elemento;

            contaThread++;

            

        }
        
        if (contaThread > qtdElementos){
            break;
        }

    }


    auto end = std::chrono::high_resolution_clock::now();

    // Calcula a diferença de tempo
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Converte a duração para um valor numérico (microsegundos)
    long long microseconds = duration.count();
    mtx.lock();
    std::cout<<"Matriz dentro da funcao Produto"<<std::endl;
    std::cout<<"ID: "<<std::this_thread::get_id()<<std::endl;
    printMatrix(Prod);
    Resultado = Prod;
    std::cout<<"-------------------------------"<<std::endl;
    salvaArq(Prod,microseconds, indice );
    mtx.unlock();
}

int main(int argc, char const *argv[])
{
    int n1, m1, n2, m2;
    std::string M1nomeArq, M2nomeArq;

    std::vector<float> linha;

    std::vector<std::vector<float>> M1;
    std::vector<std::vector<float>> M2;
    


    if (argc < 4 ){
        std::cout << "Não foram passados parâmetros suficiente na chamada da função main"<<std::endl;
        return 0;
    }
 
    M1nomeArq = argv[1];
    M2nomeArq = argv[2];
    int P = std::stoi(argv[3]);
    
        
           
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
                //std::cout <<elemento<< " ";
                linha[j] = elemento;
            }

            M2[i]=linha;

           // std::cout <<std::endl;
            
        }
    }


    Mat2arq.close();

    //testes do produto M1 xM2
/*
    std::vector<std::vector<float>> Mt1 = {{1 , 2 ,3},{ 4 , 5 , 6},{7 , 8 ,9}};
    std::vector<std::vector<float>> Mt2 = {{1,1,1},{1,1,1},{1,1,1}};

    int nt1 = Mt1.size();

    int mt2 = Mt2[0].size();

    int iniciot = 0 , qtdt = 2;

    std::vector<std::vector<float>> resultado(nt1,std::vector<float>(mt2,0));
    
    std::cout<<"Matriz1 teste:"<<std::endl;

    printMatrix(Mt1);

    std::cout<<"Matriz2 teste:"<<std::endl;
    printMatrix(Mt2);

    std::cout<<"Produto M1 x M2:"<<std::endl;
    Produto(Mt1,Mt2,0,nt1*mt2,resultado);
    printMatrix(resultado);


    for (size_t i = 0 ; i <= nt1*mt2/qtdt ; ++i){
        std::cout<<"Resultado para inicio = "<<i<< "qtdelementos = "<<qtdt<<std::endl;
        Produto(Mt1,Mt2,i,qtdt,std::ref(resultado));
        
        printMatrix(resultado);
    }
//*/
  //  auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<float>> Prod(n1, std::vector <float> (m2,0));
    
    std::vector<std::thread> threads;

    int inicio = 0, qtdElem = P, Nthreads = n1 * m2 / P;

    for (int i = 0 ; i < Nthreads; ++i){

    
        threads.emplace_back(Produto,M1,M2, inicio,qtdElem, std::ref(Prod),i);

        // std::cout<<"thread i = "<< i<<" Id =" << threads[i].get_id()<< std::endl;
        // std::cout<<"inicio:"<<inicio<< " qtd de elementos: "<< qtdElem<<std::endl;
        // std::cout<<"Matriz:"<<std::endl;
        // printMatrix(Prod);

        inicio += qtdElem;
        
    }

//---------para terminar
    for (int i = 0 ; i < Nthreads ; ++i){
        threads[i].join();
    }


    
    


    return 0;
}