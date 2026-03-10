#include "nn.hpp"
#include <iostream>
#include <chrono>

int main(){
    runServer(7878, "MY_PASSWORD");
    onMessage([](int clientFD, std::string msg){
        // broadcast to all clients except sender
        for(auto& [id, ssl] : clients){
            if(id != clientFD){
                sendMsg(msg, id);
            }
        }
    });
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}