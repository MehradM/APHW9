#ifndef TA_19_LEAFMENU_H
#define TA_19_LEAFMENU_H

#include <string>
#include <functional>
#include "Menu.h"

class LeafMenu : public Menu{
private:
    std::function<void(Controller&)> functionality;
public:
    LeafMenu(std::string name, Menu* parent,std::function<void(Controller&)> functionality);
    virtual void showSubMenus() const override;
    virtual void run() override;

};


#endif //TA_19_LEAFMENU_H
