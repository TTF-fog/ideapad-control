#include <iostream>
#include <memory>
#include <regex>
#include <tray.hpp>

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

int main()
{
    std::vector<std::shared_ptr<Tray::Button>> buttons;
    Tray::Tray tray("Ideapad Control", "icon.svg");
    tray.addEntry(Tray::Label("Ideapad Control"))->setDisabled(false);
    std::shared_ptr<Tray::Submenu> const submenu= tray.addEntry(Tray::Submenu("Power Modes"));
    auto cool_button = submenu->addEntry(Tray::Button("Intelligent Cooling",[] {
        handle_others(buttons, MODES::COOLING);
    }));
    buttons.push_back(cool_button);
    auto perf_button = submenu->addEntry(Tray::Button("Extreme Performance", [] {
        handle_others(buttons, MODES::PERFORMANCE);
    }));
    buttons.push_back(perf_button);
    auto batt_button = submenu->addEntry(Tray::Button("Battery Saver",[] {
        handle_others(buttons, MODES::BATTERY);
    }));
    buttons.push_back(batt_button);
    tray.run();

    return 0;
}