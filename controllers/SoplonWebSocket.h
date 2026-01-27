#pragma once

#include <drogon/WebSocketController.h>

using namespace drogon;

class SoplonWebSocket : public drogon::WebSocketController<SoplonWebSocket>
{
  public:
    virtual void handleNewMessage(const WebSocketConnectionPtr&,
                                  std::string &&,
                                  const WebSocketMessageType &) override;
    virtual void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr&) override;
    virtual void handleConnectionClosed(const WebSocketConnectionPtr&) override;
    WS_PATH_LIST_BEGIN
    // list path definitions here;
    // WS_PATH_ADD("/path", "filter1", "filter2", ...);
    WS_PATH_ADD("/echo");
    WS_PATH_LIST_END
};

/*
Common WebSocket interface

void send(const char * msg,uint64_t len);
void send(const std:string &msg);

const trantor::InetAddress &localAddr() const;
const trantor:InetAddress &peerAddr() const;

bool connected() const;
bool disconnected() const;

void shutdown();
void forceClose();

void setContent(const any &context);
const any &getContext() const;
any *getMutableContext();

*/
