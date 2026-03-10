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
    //Send loop
    std::thread([clientID, name](){
        while(true){
            std::getline(std::cin, msg);
            std::string msgU = name + ": " + msg;
            sendMsg(msgU,clientID);
        }
    }).detach();
    //Recv loop
    std::thread([client](){
        while(true){
            recvd = recvMsg(client);
            std::cout<<recvd<<'\n';
        }
    }).detach();
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}