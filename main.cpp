#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include "arbol_binario.cpp"
#include "hashing_cerrado.cpp"


// Se crea el diccionario que tiene como clave los atributos del archivo csv

struct Datos { // Se creo una estructrua que tenga los atributos
    std::string University,CreatedAt,UserName, UserID;
    std::string NumTweet,FriendCount,FollowersCount;

    Datos(const std::string& univ,const std::string& uid, const std::string& uname, const std::string& nt, const std::string& f, const std::string& count, std::string& date) : University(univ), UserID(uid), UserName(uname),NumTweet(nt),FriendCount(f), FollowersCount(count), CreatedAt(date){}
};




int main(){

    /////////////////////////////////////////
    // Se importa el archivo
    std::ifstream file("universities_followers_2022.csv");
    if (!file) { // Se verifica si hubo algun error al abrir el archivo
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }


    std::vector<Datos> Atributos;
    BinaryDictionary Arbol_binario;
    OpenAddressingHashTable hashTable(10);
    hashTable.loadCSV("universities_followers_2022.csv", 1, 2);

    std::string line;
    int contador=0; // Variable contador para realizar los experimentos guardando una cantidad de datos dados
    while (std::getline(file, line) || contador < 10000) {
        std::stringstream lineStream(line);
        std::string University,CreatedAt, UserName, UserID;
        std::string UserName_str,NumTweet_str,FriendCount_str,FollowersCount_str;

        // En el if se obtiene por cada linea una division de la misma en los atributos de esta

        if (std::getline(lineStream, University, ';') && std::getline(lineStream, UserID, ';')  && std::getline(lineStream, UserName, ';')  && std::getline(lineStream, NumTweet_str, ';') && std::getline(lineStream, FriendCount_str, ';') && std::getline(lineStream, FollowersCount_str, '"') && std::getline(lineStream, CreatedAt)  ) {
            //int UserID = std::stoi(UserID_str);
            /*          
            int Num_Tweet = std::stoi(NumTweet_str);
            int FriendCount = std::stoi(FriendCount_str);
            int FollowersCount = std::stoi(FollowersCount_str); 
            */


            Datos Valores(University,UserID,UserName,NumTweet_str,FriendCount_str,FollowersCount_str,CreatedAt);
            DictionaryEntry entrada(UserID,Valores.UserID);
            // std::cout<<entrada;
            auto startTime = std::chrono::high_resolution_clock::now();
            Arbol_binario.insert(entrada);
            // hashTable.insert(entrada);           
            auto endTime = std::chrono::high_resolution_clock::now();
            Atributos.push_back(Valores);

            contador++;


        }
    }
    // Calcular la duración en segundos de forma manual por lo que en el codigo se cambia manualmente la medicion para arbol binario y tabla hash. 
    std::chrono::duration<double> duration = endTime - startTime;
    double seconds = duration.count();

    std::cout << "Tiempo de ejecución: " << seconds << " segundos" << std::endl;



    file.close();
    return 0;


}