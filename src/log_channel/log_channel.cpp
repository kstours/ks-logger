#include "log_channel.h"

std::vector<Log_Channel> active_channels;
std::mutex logger_mutex;