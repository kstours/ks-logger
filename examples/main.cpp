#include <ks_logger.h>
#include <chrono>
#include <thread>

int main() {
    auto& logger = ks::Logger::Get();
    logger.init(); 
        logger.log("Example log" );
        logger.log("Example Channel Log", "Channel 2");

    while (1) {

    }
    return 0;
}