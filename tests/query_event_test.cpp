#include "bomberbloke.h"
#include <SDL2/SDL.h>
#include "cereal/archives/portable_binary.hpp"
#include "cereal/archives/json.hpp"
#include "bloke.hpp"
#include "bomb.hpp"
#include "NetClient.hpp"
#include "NetServer.hpp"
#include "QueryEvent.hpp"
#include <thread>
#include <assert.h>

int main() {
    // Don't display any graphics for this test, or even create a window
    _draw = false;
    int rc = 0;
    /* Create a NetClient and NetServer
     * By default the server runs on port 8888
     */
    NetClient net_client;
    NetServer net_server;

    assert(net_server.init_enet());

    std::stringstream data_blob;
    std::stringstream receive_blob;

    std::unique_ptr<AbstractEvent> q_event(new QueryEvent);
    std::unique_ptr<AbstractEvent> test_in_event(new QueryEvent);

    /*  Braces necessary for cereal */
    {
      cereal::JSONOutputArchive outArchive(data_blob);
      outArchive(q_event);
    }


    cereal::JSONInputArchive  inArchive(data_blob);

    inArchive(test_in_event);

    log_message(DEBUG, "query_event_test event to send is " + data_blob.str());

    /* Wait for a few moments */
    SDL_Delay(1000);
    std::thread server_thread(&NetServer::pollLoop, &net_server);

    if (net_client.connectClient("newhm.am", 8888)) {
      net_client.sendStringMessage(data_blob.str());
      SDL_Delay(900);
    }
    else {
      rc = -1;
    }
    _halt = true;
    SDL_Delay(900);

    server_thread.join();
    return rc;
}

void gameUpdate() {
    return;
}

void new_game(std::string) {
    return;
}
