#pragma once
#include <chrono>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
 
#include "ftxui/component/app.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp" 
#include "ftxui/component/component_options.hpp"
#include "ftxui/dom/elements.hpp"

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/box.hpp"
#include "Sequence.hpp"

using namespace std::chrono_literals;
using namespace ftxui;

struct ContainerData {
    std::string name;
    int type_idx;
    int mut_idx;
    int seq_type_idx;
    void* seq_ptr = nullptr;
};

class SequenceUI{
private:
    int type_index = 0;
    int mut_index = 0;
    int tab_index = 0;
    int selected_container = 0;
    int list_width = 25;

    std::vector<std::string> Typ = {
        "int",
        "doubel",
        "flout",
        "char",
    };
    std::vector<std::string> Tab = {
        "SequencArray",
        "SequenceList",
        "BitSequence",
    };
    std::vector<std::string> Mut = {
        "Mutable",
        "Immutable"
    };

    std::vector<std::string> container_names;
    std::vector<ContainerData> containers_data;

    Component radiobox_type;
    Component radiobox_mut;
    Component exit_button;
    Component tab_toggle;
    Component tab_container;
    Component create_button;
    Component left_panel;
    Component right_panel;
    Component split_panel;
    Component main_container;
    Component main_renderer;

    Component TabArray() {
        return Renderer([&] {
            return text("SequenceArray") | center;
        });
    }

    Component TabList() {
        return Renderer([&] {
            return text("SequenceList") | center;
        });
    }

    Component TabLBit() {
        return Renderer([&] {
            return text("SequenceBit") | center;
        });
    }


    Component LeftPanel() {
        return Renderer([&] {
            if(container_names.empty()){
                return vbox({
                    text("Нет контейнеров"),
                });
            }
            auto radio = Radiobox(&container_names, &selected_container);
            return vbox({
                text("Containers:") | bold,
                separator(),
                radio->Render() |frame |flex,
                separator(),
            }) | border;
        });
    }

    Component RightPanel() {
        return Renderer([&] {
            return vbox({
                text("Preview:") | bold,
                separator(),
                tab_container->Render() | flex,
                text("Type: " + Typ[type_index]) | dim
            });
        });
    }

    Component SplitPanel() {
        return ResizableSplitLeft(left_panel, right_panel, &list_width);
    }

    Component MainContainer() {
        return Container::Vertical({
            Container::Horizontal({
                radiobox_type,
                radiobox_mut,
                exit_button
            }),
            tab_toggle,
            split_panel
        });
    }

    Component MainRenderer() {
        return Renderer(main_container, [&] {
            return vbox({
                hbox({
                    window(text("Type"), radiobox_type->Render() | center),
                    window(text("Mut"), radiobox_mut->Render()),
                    filler(),
                    exit_button->Render()
                }),
                tab_toggle->Render(),
                separator(),
                split_panel->Render() | flex | border,
            })
            | bgcolor(Color::Black);
        });
    }

public:

    SequenceUI() {
        radiobox_type = Radiobox(&Typ, &type_index);
        radiobox_mut = Radiobox(&Mut, &mut_index);

        auto tab_option = MenuOption::HorizontalAnimated();
        tab_option.underline.SetAnimationFunction(animation::easing::BackOut);
        tab_option.underline.SetAnimationDuration(350ms);

        tab_toggle = Menu(&Tab, &tab_index, tab_option);

        tab_container = Container::Tab(
            {TabArray(), TabList(), TabLBit()},
            &tab_index
        );

       
        
    }

    void Run() {
        auto screen = App::Fullscreen();

        exit_button = Button("Quit", screen.ExitLoopClosure());
        
        left_panel = LeftPanel();
        right_panel = RightPanel();
        split_panel = SplitPanel();
        main_container = MainContainer();
        main_renderer = MainRenderer();

        screen.Loop(main_renderer);
    }

    ~SequenceUI() = default;
    
};

