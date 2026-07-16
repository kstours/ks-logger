#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <format>
#include <mutex>

struct Message {
    std::string timestamp;
    std::string text;

    Message(const std::string& msg_text)
        : text(msg_text),
        timestamp(std::format("[{:%H:%M:%S}]", std::chrono::current_zone()->to_local(std::chrono::system_clock::now())))
    {
    }
};

struct Log_Channel {
    std::string name;
    bool is_open = true;
    std::vector<Message> messages;
};

extern std::vector<Log_Channel> active_channels;
extern std::mutex logger_mutex;