#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include <vector>


/*
n = 3 m = 4
A = 
a0,0 a0,1 a0,2 a0,3
a0,0 a1,1 a1,2 a1,3
a0,0 a2,1 a2,2 a2,3


n = 4 m = 3
B = 
b0,0 b0,1 b0,2
b0,0 b1,1 b1,2 
b0,0 b2,1 b2,2 
b0,0 b3,1 b3,2 

n = 4 m = 4
C = 
c0,0 c0,1 c0,2 c0,3
c1,0 c1,1 c1,2 c1,3
c2,0 c2,1 c2,2 c2,3
c3,0 c3,1 c3,2 c3,3

C = A*B

c i,j = sum a[i][k]*b[k][j] k = [1,...,n]
*/

// @brief retorna o indice de 0 ... ( lin_max * col_max - 1)
// @param lin linha da matriz
// @param col coluna da matriz

int LinCol_To_Indice(int lin, int col, int lin_max, int col_max){
    /*
    C = 
        c0,0 c0,1 c0,2 c0,3
        c1,0 c1,1 c1,2 c1,3
        c2,0 c2,1 c2,2 c2,3
        c3,0 c3,1 c3,2 c3,3

    C =
        c0  c1  c2  c3
        c4  c5  c6  c7
        c8  c9  c10 c11
        c12 c13 c14 c15     

    c i , j = c indice
    */

    int indice= 0;

    indice = lin * col_max + col;

    return indice;

}

std::pair<int,int> indice_TO_linCol(int indice, int lin_max, int col_max){
    /*
    C = 
        c0,0 c0,1 c0,2 c0,3
        c1,0 c1,1 c1,2 c1,3
        c2,0 c2,1 c2,2 c2,3
        c3,0 c3,1 c3,2 c3,3

    C =
        c0  c1  c2  c3
        c4  c5  c6  c7
        c8  c9  c10 c11
        c12 c13 c14 c15     

    c i , j = c indice
    */

    std::pair <int, int> coord_ij;
    int col = 0;
    int lin = 0;

    col = indice % col_max;
    lin = indice / col_max;

    coord_ij = std::pair <int,int> (lin,col);
    

    return coord_ij;

}


void calcElementoIJ( const std::vector<int>  &linha, const std::vector<int>  &coluna, int &produto){
    
    int elemento = 0;

    int n1=linha.size();

    produto = 0;

    for (size_t k = 0; k < n1; ++k){

        elemento =  linha[k] * coluna[k];

   
        produto += elemento;
    }



}


std::vector<int> linhaMatriz(const std::vector<std::vector<int>> &M1, int indice){

    int N = M1[indice].size();

    std::vector<int>  linha(N);

    for(int i = 0; i < N; ++i){
        linha[i] = M1[indice][i];
    }

    return linha;
}


std::vector<int> colunaMatriz(const std::vector<std::vector<int>> &M1, int indice){

    int N = M1.size();

    std::vector<int>  coluna(N);

    for(int k = 0; k < N; ++k){
        coluna[k] = M1[k][indice];
      //  std::cout<<"linha "<< k <<"col "<< indice<< "Elemento: "<< M1[k][indice]<<std::endl;
        
    }
    //printVetor(coluna);
    return coluna;
}


std::vector<std::vector<int>> Produtothread(const std::vector<std::vector<int>> &M1, 
            const std::vector<std::vector<int>> &M2, std::vector<int> indices ){
    
       
    int n1 = M1.size();
    
    int m2 = M2[0].size();
    
    int elemento;
    
    std::vector<std::vector<int>> Prod(n1, std::vector<int> (m2,0));

    std::vector<int> linha;
    std::vector<int> coluna;

    int i, j;

    for (auto coord_ij:indices){

        i = indice_TO_linCol(coord_ij,n1,m2).first;
        j = indice_TO_linCol(coord_ij,n1,m2).second;
        
        linha = linhaMatriz(M1,i);

        //std::cout<<"Linha:"<<std::endl;
        //printVetor(linha);

      
        coluna = colunaMatriz(M2,j);
            
        //std::cout<<"Coluna:"<<std::endl;
        //printVetor(coluna);

        calcElementoIJ(linha,coluna,elemento);
        
        Prod[i][j] = elemento;


    }

    return Prod;
}

std::vector<int> ProdutothreadVector(const std::vector<std::vector<int>> &M1, 
            const std::vector<std::vector<int>> &M2, const std::vector<int> &indices ){
    
       
    int n1 = M1.size();
    
    int m2 = M2[0].size();
    
    int elemento;
    
    std::vector<int> Prod;

    std::vector<int> linha;
    std::vector<int> coluna;

    int i, j;

    for (auto coord_ij:indices){

        i = indice_TO_linCol(coord_ij,n1,m2).first;
        j = indice_TO_linCol(coord_ij,n1,m2).second;
        
        linha = linhaMatriz(M1,i);
    
        coluna = colunaMatriz(M2,j);            

        calcElementoIJ(linha,coluna,elemento);
        
        Prod.push_back( elemento);


    }

    return Prod;
}

void Produtothread2(const std::vector<std::vector<int>> &M1, 
            const std::vector<std::vector<int>> &M2, 
            const std::vector<int> &indices , 
            std::vector<int> &Prod, 
            long long &microsecond){

    auto start = std::chrono::high_resolution_clock::now();

    Prod = ProdutothreadVector(M1,M2,indices);

    auto end = std::chrono::high_resolution_clock::now();

    // Calcula a diferença de tempo
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Converte a duração para um valor numérico (microsegundos)
    microsecond = duration.count();
    
    std::cout<<"-------Thread "<<std::this_thread::get_id()<< " concluida. Tempo: "<<microsecond<<" us"<<std::endl;
            
}


void printVetor(const std::vector<float>  &linha){
    for (auto &i : linha)
    {
        std::cout << i <<" ";
    }
    std::cout<<std::endl;
}
void printVetor(const std::vector<int>  &linha){
    for (auto &i : linha)
    {
        std::cout << i <<" ";
    }
    std::cout<<std::endl;
}
void printMatrix(const std::vector<std::vector<int>>  &M){
    
    int n1 = M.size();
    int m1 = M[0].size();
    std::vector<int> linha(m1);

    for (size_t i = 0; i < n1; ++i)
    {
        linha = linhaMatriz(M,i);
        
        printVetor(linha);
    }
}

std::vector<int> rangeIndices(int inicio, int passo, int fim){
    std::vector<int> indices;

    for (int i = inicio; i < fim ; ++i){
        indices.push_back(i);
    }

    return indices;

}


#endif