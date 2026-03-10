#include"nn.hpp"
#include<iostream>
std::string msg;
std::string recvd;
int main(){
    //Initial setup
    int client = runClient("127.0.0.1",7878,"MY_PASSWORD");
    recvd = recvMsg(client);
    int clientID = std::stoi(recvd);
    //username selection
    std::string name;
    std::cout<<"Username: ";
    std::getline(std::cin,name);
    //Send loop (We make a thread so it works simultaniously with the rest)
    std::thread([clientID, name](){
        while(true){
            std::getline(std::cin, msg);
            std::string msgU = name + ": " + msg;
            sendMsg(msgU,clientID);
        }
    }).detach();
    //Recv loop (Again, a thread so it works simultaniously)
    std::thread([client](){
        while(true){
            recvd = recvMsg(client);
            std::cout<<recvd<<'\n';
        }
    }).detach();
    //So main() doesn't return anything and runs forever.
    //Timer for 100ms so it doesn't tank cpu usage for no reason.
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}