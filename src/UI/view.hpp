#pragma once
#include <chrono>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "controller.hpp"
 
#include "ftxui/component/app.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp" 
#include "ftxui/component/component_options.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/box.hpp"


using namespace std::chrono_literals;
using namespace ftxui;

class SequenceUI{
private:
    int mut_index = 0;
    int tab_index = 0;
    int selected_container = 0;
    int list_width = 25;

    std::vector<std::string> Tab = {
        "SequencArray",
        "SequenceList",
    };
    std::vector<std::string> Mut = {
        "Mutable",
        "Immutable"
    };

    std::vector<std::string> container_names;

    std::string input_idx = "";
    std::string input_val = "";
    std::string input_end_idx = "";

    Component radiobox_mut;
    Component exit_button;
    Component tab_toggle;
    Component tab_container;
    Component create_button;
    Component delete_button;
    Component menu;
    Component input_idx_comp;
    Component input_val_comp;
    Component input_end_idx_comp;
    Component input_container;

    Component left_panel;
    Component right_panel;
    Component split_panel;
    Component main_container;
    Component main_renderer;

    Component view_array;
    Component view_list;
    
    Manager manager;

    ButtonOption ButtonStyle() {
        return ButtonOption::Animated(
            Color::Default,
            Color::White,
            Color::Default,
            Color::GrayDark     
        );
    }

    
    void InitTabs() {        
        auto buttons_array = FuncButtons(0);
        auto buttons_list = FuncButtons(1);
        
        view_array = Renderer(buttons_array, [buttons_array] {
            return buttons_array->Render() 
            | frame
            | vscroll_indicator
            | size(HEIGHT, LESS_THAN, 12);
        });
        
        view_list = Renderer(buttons_list, [buttons_list] {
            return buttons_list->Render() 
            | frame
            | vscroll_indicator
            | size(HEIGHT, LESS_THAN, 12);
        });
        
        tab_container = Container::Tab(
            { view_array, view_list },
            &tab_index
        );
    }
    
    void RefreshContainer(){
        container_names.clear();
        for (size_t i = 0; i < manager.size(); ++i) {
            container_names.push_back(manager.getName(i));
        }
        if (selected_container >= container_names.size() && !container_names.empty()){
            selected_container = container_names.size() - 1;
        }
    }
    
    void InitInput(){
        input_idx_comp = Input(&input_idx, "index/star index");
        input_idx_comp |= CatchEvent([&](Event e) {
        if (e.is_character()) {
                char c = e.character()[0];
                if (!std::isdigit(c)){ 
                    return true;
                }
                std::string future = input_val + c;
                if (future.size() > 3){ 
                    return true;
                }
                int num = std::stoi(future);    
                if (num > 255){ 
                    return true;
                }
            }
            return false;
        });

        input_val_comp = Input(&input_val, "value");
        input_val_comp |= CatchEvent([&](Event e) {
        if (e.is_character()) {
                char c = e.character()[0];
                if (!std::isdigit(c)){ 
                    return true;
                }
                std::string future = input_val + c;
                if (future.size() > 3){ 
                    return true;
                }
                int num = std::stoi(future);    
                if (num > 255){ 
                    return true;
                }
            }
            return false;
        });

        input_end_idx_comp = Input(&input_end_idx, "end index");
        input_end_idx_comp |= CatchEvent([&](Event e) {
            if (e.is_character()) {
                char c = e.character()[0];
                if (!std::isdigit(c)){ 
                    return true;
                }
                std::string future = input_val + c;
                if (future.size() > 3){ 
                    return true;
                }
                int num = std::stoi(future);    
                if (num > 255){ 
                    return true;
                }
            }
            return false;
        });

        input_container = Container::Vertical({
            input_idx_comp,
            input_val_comp,
            input_end_idx_comp
        });
    }

    void Append(){
        if (!input_val.empty()) {
            manager.addAppend(selected_container, static_cast<uint8_t>(std::stoi(input_val)));
            RefreshContainer();
        }
    }

    void Prepend(){
        if (!input_val.empty()) {
            manager.addPrepend(selected_container, static_cast<uint8_t>(std::stoi(input_val)));
            RefreshContainer();
        }
    }

    void InsertAt(){
        if (!input_val.empty() && !input_idx.empty()) {
            manager.addInsertAt(selected_container, static_cast<uint8_t>(std::stoi(input_val)), std::stoi(input_idx));
            RefreshContainer();
        }
    }

    void Concat(){
        if (!input_idx.empty()) {
            manager.addConcat(selected_container, std::stoi(input_idx));
            RefreshContainer();
        }
    }

    void GetSubsequence() {
        if (!input_idx.empty() && !input_end_idx.empty()) {
            manager.addGetSubsequence(selected_container, std::stoi(input_idx), std::stoi(input_end_idx));
            RefreshContainer();
        }
    }

    Component FuncButtons(int tab) {
        auto style = ButtonStyle();
        Components buttons;
        buttons.push_back(Button("Append",   [&]{ Append(); }, style));
        buttons.push_back(Button("Prepend",  [&]{ Prepend(); }, style));
        buttons.push_back(Button("InsertAt", [&]{ InsertAt(); }, style));
        buttons.push_back(Button("Concat",   [&]{ Concat(); }, style));
        buttons.push_back(Button("GetSubseq", [&]{ GetSubsequence(); }, style));

        return Container::Vertical(buttons);
    }


    Component LeftPanel() {
        return Renderer(menu, [&] {
            if (container_names.empty()) {
                return vbox({ 
                    text("Нет контейнеров"),
                    filler(),
                    text("Пожалуйста, не пытайтесь сломать мой интерфейс ;(")| dim
                });
            }
            return vbox({
                text("Контейнеры:") | bold,
                separator(),
                menu->Render() | frame | vscroll_indicator | flex,
                text(std::format("Count:{}", manager.size()))| dim 
            });
        });
    }

    Component RightPanel() {

        auto right_combined = Container::Vertical({
            tab_container,
            input_container
        });

        return Renderer(right_combined, [&] {
            Element len;
            std::string leng = "0";
            std::string seq_t = manager.PrintNode(selected_container);
            Element header = text(Tab[tab_index]) | bold;
            Element preview = text(seq_t) | dim | center;
            auto seq = manager.get(selected_container);
            if(seq){
                leng = std::to_string(seq->GetLength());
            }
            len = text(std::format("Lengh:{}",leng))| dim;

            Element input_section = vbox({
                text("Ввод:"),
                hbox({text("Index:"), input_idx_comp->Render()}),
                hbox({text("IndexEnd:"), input_end_idx_comp->Render()}),
                hbox({text("Value:"), input_val_comp->Render()}),
                filler(),
                text("Просьба: Дорогой пользователь, вводи значения от 0 до 255 в отведённые для этого строки ;)")| dim 
            });
            
            return vbox({
                header,
                separator(),
                hbox({
                    tab_container->Render(),
                    separator(),
                    input_section,
                }),
                separator(),
                preview | flex,
                len,

            });
        });        
    }

    Component SplitPanel() {
        return ResizableSplitLeft(left_panel, right_panel, &list_width);
    }

    Component MainContainer() {
        return Container::Vertical({
            Container::Horizontal({
                radiobox_mut,
                create_button,
                delete_button,
                exit_button
            }),
            tab_toggle,
            split_panel,
        });
    }


    Component MainRenderer() {
        return Renderer(main_container, [&] {
            return vbox({
                hbox({
                    window(text("Mutable"), radiobox_mut->Render()),
                    create_button->Render(),
                    delete_button->Render(),
                    filler(),
                    exit_button->Render()
                }),
                tab_toggle->Render(),
                separator(),
                split_panel->Render() | flex,
            })
            | bgcolor(Color::Black)
            | border;
        });
    }
public:

    SequenceUI() {
        radiobox_mut = Radiobox(&Mut, &mut_index);
        menu = Menu(&container_names, &selected_container);
        
        auto tab_option = MenuOption::HorizontalAnimated();
        tab_option.underline.SetAnimationFunction(animation::easing::BackOut);
        tab_option.underline.SetAnimationDuration(350ms);
        
        tab_toggle = Menu(&Tab, &tab_index, tab_option);
        
        InitTabs();

        InitInput();

        manager.create(0, 0);
        RefreshContainer();
        
    }

    void Run() {
        auto screen = App::Fullscreen();

        exit_button = Button("Выход", screen.ExitLoopClosure());
        create_button = Button("Создать", [&] {
            manager.create(tab_index, mut_index);
            RefreshContainer();
        });

        delete_button = Button("Удалить", [&]{
            if(manager.size() > 0 && selected_container >= 0){
                manager.remove(selected_container);
                RefreshContainer();
            }
        });

        left_panel = LeftPanel();
        right_panel = RightPanel();
        split_panel = SplitPanel();
        main_container = MainContainer();
        main_renderer = MainRenderer();

        screen.Loop(main_renderer);
    }

    ~SequenceUI() = default;
    
};

