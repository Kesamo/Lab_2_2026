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
#include "UI/view.hpp"
#include "utils/Exceptions.hpp"
#include "BitSequence/BitProxy.hpp"
#include "BitSequence/BitSequence.hpp"

#include <chrono> 
using namespace std::chrono_literals;
using namespace ftxui;
  
// int main() {
//     auto screen = App::Fullscreen();
 
//     int type_index = 0;
//     int mut_index = 0;
//     int selected_container = -1; 

//     std::vector<std::string> Typ = {
//         "int",
//         "doubel",
//         "flout",
//         "char",
//     };
 
//     std::vector<std::string> tub_values = {
//         "SequencArray",
//         "SequenceList",
//         "BitSequence",
//     };
    
//     std::vector<std::string> Mut = {
//         "Mutable",
//         "Immutable"
//     };

//     std::vector<std::string> container_names = {};
       
//     auto radiobox_type = Radiobox(&Typ, &type_index);
//     auto radiobox_mut = Radiobox(&Mut, &mut_index);
//     auto exit_button = Button("Quit", screen.ExitLoopClosure());

//     int tab_selected = 0;
//     auto tab_toggle = Toggle(&tub_values, &tab_selected);
    
//     auto tab_array = Renderer([&] { 
//         return text("SequenceArray") | center; 
//     });
//     auto tab_list = Renderer([&] { 
//         return text("SequenceList") | center; 
//     });
//     auto tab_bit = Renderer([&] { 
//         return text("BitSequence") | center; 
//     });

//     auto tab_container = Container::Tab(
//         { tab_array, tab_list, tab_bit },
//         &tab_selected
//     );

//     int list_width = 25;

//     auto left_panel = Renderer([&] {
//         if(container_names.empty()){
//             return vbox({
//                 text("Нет контейнеров"),
//                 // Button("Create", [&]{})->Render() | center
//             });
//         }
//         auto radio = Radiobox(&container_names, &selected_container);
//         return vbox({
//             text("Containers:") | bold,
//             separator(),
//             radio->Render() |frame |flex,
//             separator(),
//             //
//         }) | border;
//     });

//     auto right_panel = Renderer([&] {
//         return vbox({
//             text("Preview:") | bold,
//             separator(),
//             tab_container->Render() | flex,
//             text("Type: " + Typ[type_index]) | dim
//         });
//     });

//     auto split_panel = ResizableSplitLeft(
//         left_panel,
//         right_panel,
//         &list_width
//     );

//     auto main_container = Container::Vertical({
//       Container::Horizontal({
//             radiobox_type,
//             radiobox_mut,
//             exit_button
//       }),
//       tab_toggle,
//       split_panel
//   });
    
//     auto main_renderer = Renderer(main_container, [&] {
//         return vbox({
//             hbox({
//                 window(text("Type"), radiobox_type->Render() | center),
//                 window(text("Mut"), radiobox_mut->Render() ),
//                 filler(),
//                 exit_button->Render()
//             }),
//             tab_toggle->Render(),
//             separator(),
//             split_panel->Render() | flex | border,
//         })
//         | bgcolor(Color::Black);
//     });
    
//     screen.Loop(main_renderer);
    
//     return 0;
// }

int main() {
    try{
        SequenceUI app;
        app.Run();
    }
    catch(const Exception& e){
        std::cerr << "Ошибка:" << e.what() << std::endl;
    }
    // MutableBitSequence<int>* seq = nullptr;
    // Bit<int> arr[] = {3, 6, 7, 8};
    // seq = new MutableBitSequence<int>(arr, 4);

    // int also = seq->GetAsInteger(1);
    // std::cout << also << std::endl; 

    // std::cout << seq->Get(1)[2] << ",";
    // std::cout << seq->Get(1)[1] << ",";
    // std::cout << seq->Get(1)[0] << std::endl;

    // seq->GetMutable(1)[4] = 1;

    // std::cout << seq->Get(1)[4] << ",";
    // std::cout << seq->Get(1)[3] << ",";
    // std::cout << seq->Get(1)[2] << ",";
    // std::cout << seq->Get(1)[1] << ",";
    // std::cout << seq->Get(1)[0] << std::endl;

    // int also_ = seq->GetAsInteger(1);
    // std::cout << also_ << std::endl;

    // for(int i = 0; i < 4; i++){
    //     std::cout << seq->GetAsInteger(i) << ",";
    // }

    

}