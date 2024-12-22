#include "toml.hpp"
#include <array>
#include <cstdio>

#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <tray.hpp>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, void(*)(FILE*)> pipe(popen(cmd, "r"),
    [](FILE * f) -> void
    {
        // wrapper to ignore the return value from pclose() is needed with newer versions of gnu g++
        std::ignore = pclose(f);
    });
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

enum MODES
{
    COOLING = 0,
    PERFORMANCE = 1,
    BATTERY = 2,
};

void handle_others(std::vector<std::shared_ptr<Tray::Button>> buttons, MODES mode)
{
    const std::regex pattern("\\[\\*\\]");

    switch (mode)
    {
        case MODES::COOLING:
            buttons[0]->setText("Intelligent Cooling [*]");
            for (int i = 0 ; i < static_cast<int>(buttons.size()); i++)
            {
                if (i == MODES::COOLING) {continue;}
                buttons[i] ->setText( std::regex_replace(buttons[i]->getText(), pattern, " "));
            }
            break;
        case BATTERY:
            buttons[MODES::BATTERY]->setText("Battery Saver [*]");
            for (int i = 0 ; i < static_cast<int>(buttons.size()); i++)
            {
                if (i == MODES::BATTERY) {continue;}
                buttons[i] ->setText( std::regex_replace(buttons[i]->getText(), pattern, " "));
            }
                break;
            case MODES::PERFORMANCE:
                buttons[MODES::PERFORMANCE]->setText("Extreme Performance [*]");
                for (int i = 0 ; i < static_cast<int>(buttons.size()); i++)
                {
                    if (i == MODES::PERFORMANCE) {continue;}
                    buttons[i] ->setText( std::regex_replace(buttons[i]->getText(), pattern, " "));
                }
                break;
        }
}
bool check_if_supported()
{
    auto conf = toml::parse("test.toml");
    // auto r= conf["supported"]["laptops"];

    const std::string input = exec("cat /sys/devices/virtual/dmi/id/product_version");
    const std::regex regex(R"(^(?:\S+\s+){3}(\S+))");
    std::smatch match;

    std::regex_search(input, match, regex);
    for (std::string const &i: toml::find<std::vector<std::string>>(conf,"supported", "laptops"))
    {

        if (i == match[1].str())
        {
            return true;
        }
    }
    throw std::invalid_argument("Unsupported laptop, try editing the config");


}
int main()
{
    check_if_supported();
    std::vector<std::shared_ptr<Tray::Button>> buttons;
    Tray::Tray tray("Ideapad Control", "icon.svg");
    tray.addEntry(Tray::Label("Ideapad Control"))->setDisabled(false);
    std::shared_ptr<Tray::Submenu> const submenu= tray.addEntry(Tray::Submenu("Power Modes"));
    auto cool_button = submenu->addEntry(Tray::Button("Intelligent Cooling",[&] {
        handle_others(buttons, MODES::COOLING);
    }));
    buttons.push_back(cool_button);
    auto perf_button = submenu->addEntry(Tray::Button("Extreme Performance", [&] {
        handle_others(buttons, MODES::PERFORMANCE);
    }));
    buttons.push_back(perf_button);
    auto batt_button = submenu->addEntry(Tray::Button("Battery Saver",[&] {
        handle_others(buttons, MODES::BATTERY);
    }));
    buttons.push_back(batt_button);
    tray.run();

    return 0;
}