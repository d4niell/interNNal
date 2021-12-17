#pragma once
#include <core/utils.h>
#include <menu/menu.h>
#include <core/globals.h>

class LoginStuff {
   public:
  
    char username[200]{};
    char password[200]{};
}login;
void menu::animate() {
    static bool direction = false;

    //most imgui controls have a custom added fading effect
    global::fade += direction ? -0.003f : 0.003f;
    if (global::fade <= 0.0f) {
        direction = !direction;
        global::fade = 0.0f;
    }
    else if (global::fade >= 0.3f) {
        direction = !direction;
        global::fade = 0.3f;
    }
}
string convertToString(char* a, int size) {
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void menu::EndScene(IDirect3DDevice9* device, bool active) {
//loadmenu:
    if (!global::load) { //init imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplDX9_Init(device);
        ImGui::StyleColorsDark();
        //load_config();
        utils::printc("93", "dx9 and imgui init done");
        global::load = true;
    }
    if (global::load) {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2{ 800, 450 }, ImGuiCond_Once);
        if (opt::login == false) {
            if (global::draw && ImGui::Begin(std::string("Login page. Please provide the correct credentials.").c_str(), &global::draw, ImGuiWindowFlags_NoCollapse)) {
                animate();
                ImGui::Text("Username:");              
                ImGui::InputText("##un", login.username, IM_ARRAYSIZE(login.username));               
                int username_size = sizeof(login.username) / sizeof(char);
                ImGui::Text("Password:");              
                ImGui::InputText("##pw", login.password, IM_ARRAYSIZE(login.password), ImGuiInputTextFlags_Password); 
                int password_size = sizeof(login.password) / sizeof(char);
                if (ImGui::Button("login")) {
                    utils::printc("91", "Checking credentials...");                    
                   std::string s_username = convertToString(login.username, username_size);
                   std::string s_password = convertToString(login.password, password_size);                   
                   utils::printc("83", s_username.c_str());                  
                   utils::printc("93", s_password.c_str());
                   if (s_username == "d4niel" && s_password == "alpha ") {
                       system("pause");
                       utils::printc("91", "Welcome back, d4niel");
                       opt::login == true;
                   }
                   else {
                       utils::printc("92", "Invalid Credentials");
                   }

                }
                ImGui::End();
                ImGui::EndFrame();
                ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            }
        }


        else
        if (global::draw && ImGui::Begin(std::string("interNNal " + global::version).c_str(), &global::draw, ImGuiWindowFlags_NoCollapse)) {
            animate();
            static char* tab_names[] = { (char*)"Enhancements", (char*)"Cheats", (char*)"Framework", (char*)"Visuals", (char*)"Credits" };
            static int active_tab = 0;

            auto& style = ImGui::GetStyle();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, style.WindowPadding.y });

            float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 10));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
            imwrap::horizontal_tabs(tab_names, active_tab, group_w / _countof(tab_names), 33.0f);
            ImGui::PopStyleVar(3);

            switch (active_tab) {
                case 0: enhancements_tab(); break;
                case 1: cheats_tab(); break;
                case 2: framework_tab(); break;
                case 3: visuals_tab(); break;
                case 4: credits_tab(); break;
            }
            ImGui::End();
        }
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
}

bool menu::WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    static bool init = false;
    if (!global::d9init)
        return false;

    if (global::load && !init) {
        ImGui_ImplWin32_Init(wnd);
        init = true;
    }

    if (msg == WM_KEYUP && wparam == VK_F2)
        global::draw = !global::draw;

    /*  if (msg == WM_KEYUP && wparam == VK_F4)
        load_config();*/

    return ImGui_ImplWin32_WndProcHandler(wnd, msg, wparam, lparam);
}
