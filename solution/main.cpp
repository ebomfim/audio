#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main(int argc, char*argv[])
{
   
    if(argc < 2) {
        puts("Server: ");
        puts("Usage: app <port> (default: 1234)");
        puts("Client");
        puts("Usage: telnet <address> <port> to connect");
        puts("Example: telnet localhost 1234");
    }
   
     sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.ogg"))  
        return -1;  
   
    sf::Sound sound;
    sound.setBuffer(buffer);    
     
    // Create a server socket to accept new connections
    sf::TcpListener listener;
   
    int port = 1234;
   
    if (argc > 1)
        port = atoi(argv[1]);
   
    // Listen to the given port for incoming connections
    if (listener.listen(port) != sf::Socket::Done)
        return -1;
   
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

    // Wait for a connection
    sf::TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Done)
        return -1;
    std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;    
   
    char in[128];
    std::size_t received;
    char command = '0';

while(1)
{    
        if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
            return -1;  
   
        command = in[0];
   
        switch (command)
        {
            case 'p':
                sound.play();
                break;
            case 's':
                sound.pause();
                break;
            case 'q':
                return 0;                
        }        
}
   
    return 0;    
}


/*
audio: main.cpp
g++ -c main.cpp; g++ main.cpp -o audio -lsfml-audio -lsfml-network -lsfml-system

clean: rm -f *.o; rm -f audio
*/