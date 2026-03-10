#include "nn.hpp"
#include <iostream>
#include <chrono>

int main(){
    runServer(7878, "MY_PASSWORD");
    //Triggered everytime a message is received
    onMessage([](int clientFD, std::string msg){
        // broadcast to all clients except sender
        for(auto& [id, ssl] : clients){
            if(id != clientFD){
                sendMsg(msg, id);
            }
        }
    });
    //So main() doesn't return anything and runs forever.
    //Timer for 100ms so it doesn't tank cpu usage for no reason.
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}