#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

std::mutex mtx;
//float soma = 0;

void saida(const std::vector<float> v){
    
    float soma = 0;
    for (int i = 0; i < v.size(); ++i){
        soma += i;
    }

    

    

}

void produto(float peso, float entrada, float & soma){
    mtx.lock();
    
    soma += peso * entrada;
    
    mtx.unlock();
}

int main(int argc, char const *argv[])
{
    std::vector<std::thread> thr;
    std::vector<float> peso = {1 , 2 ,3 ,4 , 5};
    float entrada = 1;
    //float soma = 0;
    float soma = 0 ;

    for (int i = 0; i < 5 ; ++ i){
        thr.emplace_back( produto, peso[i],entrada,std::ref (soma));
        
        
        


    }

    for (int i = 0; i < 5 ; ++ i){std::cout<<"thread id = "<<thr[i].get_id()<<std::endl;

        std::cout<<"thread id = "<<thr[i].get_id()<<std::endl;
        
        thr[i].join();
    }

    std::cout<<soma<<std::endl;

    return 0;
}
