#include <iostream>
#include <memory>
#include <tray.hpp>
enum MODES
{
    COOLING = 0,
    BATTERY = 1,
    PERFORMANCE = 2,
};
void handle_others(std::vector<std::shared_ptr<Tray::Button>> buttons, MODES mode)
{switch (mode)
    {
        case MODES::COOLING:
            std::cout << "COOLING" << std::endl;
            buttons[1]->setDisabled(true);
            buttons[2]->setDisabled(true);
            buttons[0]->setText("Intelligent Cooling [*]");
            break;
        case MODES::BATTERY:
            std::cout << "BATTERY" << std::endl;
            break;
        case MODES::PERFORMANCE:
            std::cout << "PERFORMANCE" << std::endl;
            break;
    }
}

int main()
{
    std::vector<std::shared_ptr<Tray::Button>> buttons;
    Tray::Tray tray("test", "icon.svg");
    std::shared_ptr<Tray::Submenu> submenu= tray.addEntry(Tray::Submenu("Test Submenu"));
    auto m = submenu->addEntry(Tray::Button("Intelligent Cooling",[&] {
        handle_others(buttons, MODES::COOLING);;
    }));
    buttons.push_back(m);
    auto t = submenu->addEntry(Tray::Button("Extreme Performance"));
    buttons.push_back(t);
    auto n = submenu->addEntry(Tray::Button("Battery Saver"));
    buttons.push_back(n);
    tray.run();

    return 0;
}