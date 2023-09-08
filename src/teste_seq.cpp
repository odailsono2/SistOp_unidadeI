#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>


int main(int argc, char const *argv[]){


    // Comando a ser executado
    std::string diretorio = "./build/sequencial";

    std::string output = "./output/matriz1.txt ./output/matriz1.txt";

    std::string comando;

    comando.append(diretorio + " " + output);

    std::cout<<comando<<std::endl;

    // comando.append(programa);

    // comando.append(argumento_1);

    // comando.append(argumento_2);

    
    const char* exe_comando = comando.c_str();

    int status;
    for (int i = 0; i<10;++i)
         status = std::system(exe_comando);

    // Verificar o status de saída do comando
    if (status == 0) {
        std::cout << "Comando executado com sucesso." << std::endl;
    } else {
        std::cerr << "Erro ao executar o comando." << std::endl;
    }

    return 0;
}

