//
// Created by dave on 08.06.20.
//

#include "NetClient.hpp"
#include "engine.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include "AbstractEvent.hpp"
#include <cereal/archives/json.hpp>

NetClient::NetClient(){
    if (enet_initialize() != 0) {
        printf("ERROR: An error occurred while initializing ENet");
        return;
    }
    //TODO: insert variables for host
    this->host = enet_host_create(nullptr, 1, 1, 0, 0);
}

NetClient::~NetClient() {
    // Clean up ENet
    disconnectClient();
    enet_host_destroy(this->host);
    enet_deinitialize();
}

bool NetClient::connectClient(std::string serverAddress, enet_uint16 port) {
    mServerAddress = serverAddress;
    mPort = port;
    log_message(INFO, "attempting to connect");
    enet_address_set_host(&address, mServerAddress.c_str());
    address.port = mPort;

    //Initiate the connection, with only one channel
    this->peer = enet_host_connect(this->host, &address, 1, 0);
    if (peer == NULL) {
        fprintf(stderr, "No available peers for initiating an ENet connection.\n");
        return false;
    }
    // Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(this->host, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT) {
        std::stringstream msg;
        msg << "Connection to " << serverAddress << ":" <<  port << " succeeded";
        log_message(INFO, msg.str());
        // Send follow up message
        // sendStringMessage("game_info");
        return true;

    } else {
        enet_peer_reset(this->peer);
        std::stringstream msg;
        msg << "Connection to " << serverAddress << ":" <<  port << " failed";
        log_message(INFO, msg.str());
        return false;
    }
}

void NetClient::pollServer(){
  while(enet_host_service(this->host, &event, 0)>0){
   if (event.type == ENET_EVENT_TYPE_RECEIVE) {
     // event occured
     std::stringstream data_in;
     data_in << event.packet->data;
     std::unique_ptr<AbstractEvent> receive_event;
     // cereal::JSONInputArchive inArchive(data_in);

     log_message(DEBUG, "received message: " + data_in.str());

     // inArchive(receive_event);

     /* Make the pointer shared so we can handle it elsewhere */
     // std::shared_ptr<AbstractEvent> sp_to_handle = std::move(receive_event);
   }
  }
  return;
}



void NetClient::disconnectClient() {
    //An ENET_EVENT_DISCONNECT event will be generated by enet_host_service() once the disconnection is complete.
    // We need to poll, as we could recieve other packets first?
    ENetEvent event;
    enet_peer_disconnect(this->peer, 0);
    while (enet_host_service(this->host, &event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("Disconnection succeeded.\n");
                return;
            default:
                break;
        }
    }
    //Disconnect didn't happen in three seconds, force reset peer
    enet_peer_reset(this->peer);
}

void NetClient::sendStringMessage(std::string message) {
    ENetPacket *packet = enet_packet_create(message.c_str(), strlen(message.c_str())+1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(this->peer, 0, packet);
    enet_host_flush(this->host);
    std::cout << "Sent Message\n";
}


bool NetClient::isConnected() {
    if (&this->host != nullptr) {
        return true;
    }
    return false;
}
