//
// Created by valdemar on 22.10.17.
//

#pragma once

#include <viewer/Scene.h>

#include <csimplesocket/PassiveSocket.h>
#include <csimplesocket/ActiveSocket.h>

struct Frame;

/**
 * Negotiation with running strategy
 *  - listen socket, read json primitives
 *  - decode json primitives to one of Primitives.h
 *  - configure Frame object
 *  - send Frame to Scene when ready
 *  - running in personal thread
 */
class NetListener {
public:
    enum class ConStatus {
        WAIT,
        ESTABLISHED,
        CLOSED
    };

    NetListener(Scene *scene, const std::string &listen_host, uint16_t listen_port);

    ///Return current connection status.
    ///Will be wait until first data chunk, established while tcp connection alive
    ConStatus connection_status() const;

    ///Start gathering and operating information from socket
    ///Blocking call, should be running on personal thread
    void run();

    void stop();

private:
    std::vector<signed char> read_bytes(unsigned int byteCount);
    uint32_t read_uint32();

    uint32_t read_uint32(const signed char** iterator);
    uint16_t read_int16(const signed char** iterator);
    float read_float(const signed char** iterator);

    void process_message(const std::vector<signed char>& package);

    Scene *scene_;
    std::unique_ptr<CPassiveSocket> socket_;
    CActiveSocket *client_ = nullptr;
    ConStatus status_;

    std::unique_ptr<Frame> frame_ = nullptr;
    bool stop_ = false;
};