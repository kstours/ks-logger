
#include <vector>
#include <functional>
#include <string>

namespace window_menu {

	struct MenuItem{
		struct Option {
			std::string name;
			std::string keybind;
			std::function<void()> callback;
	 	};

		std::string name;
		std::vector<Option> options;
		MenuItem& addOption(std::string name, std::string keybind = "", std::function<void()> callback = nullptr) {
			options.push_back({name,keybind,callback});
			return *this;
		}

	inline std::vector<MenuItem>& get() {
        static std::vector<MenuItem> instance;
        return instance;
    }

    inline MenuItem& create(std::string name) {
        get().push_back({name, {}});
        return get().back();
    }
};

inline std::vector<MenuItem> menu;
void initWindowMenu();

}
