#include <ks_logger.h>

int main() {
	auto& logger = ks::Logger::Get();
	logger.init();

	while (1) {};
	return 0;
}