#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>


int main(int argc, char const *argv[]){

    


    // Comando a ser executado
    std::string diretorio = "./build/thread2";

    std::string flag1 = "./output/matriz1_";

    flag1.append(argv[1]);


    std::string flag2 = "./output/matriz2_";
    
    flag2.append(argv[1]);


    std::string comando1;

    comando1.append(diretorio + " " + flag1 + " " + flag2 + " " + argv[2] );

    std::string comando2;

    comando2.append(diretorio + " " + flag1 + " " + flag2 + " " + argv[2] );
    comando2.append(" 0");
    std::cout<<comando1<<std::endl;

    // comando.append(programa);

    // comando.append(argumento_1);

    // comando.append(argumento_2);

    
    const char* exe_comando;

    int status;
    int Nvezes = 10;
    for (int i = 0; i<Nvezes;++i)
        if (i == Nvezes-1){
            exe_comando = comando1.c_str(); 
            status = std::system(exe_comando);
        }
        else{

            exe_comando = comando2.c_str();
            status = std::system(exe_comando);
        }
    // Verificar o status de saída do comando
    if (status == 0) {
        std::cout << "Comando executado com sucesso." << std::endl;
    } else {
        std::cerr << "Erro ao executar o comando." << std::endl;
    }

    return 0;
}

