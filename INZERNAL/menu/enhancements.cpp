#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>

void menu::enhancements_tab() {
    char CustomText[20];
    ImGui::Text("This tab is currently under modification.");
    ImGui::Text("Custom Text:");
    ImGui::InputText("##custominput", &CustomText[20], IM_ARRAYSIZE(&CustomText[20]));
   if (ImGui::Button("Send Message")) {
        gt::log(&CustomText[20]);
    }
    if (ImGui::CollapsingHeader("Custom Server")) {
        if (ImGui::BeginChild("###customserver", AUTOSIZE(2.f), true)) {
            imwrap::checkbox("Enable###custom", opt::custom_server_on, "You can use this to connect to private servers too");
            ImGui::SameLine();
            imwrap::inputstring("##serverval", &opt::custom_server_val, 0);
            ImGui::Text("Works with growtopia2 (gt1 is usually broken), and private servers.");
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Login info spoofing")) {
        if (ImGui::BeginChild("###loginspoof", ImVec2(ImGui::GetWindowWidth() * 0.93f, 60.f), true)) {
            ImGui::Checkbox("Enable###spoof", &opt::spoof_login);
            ImGui::SameLine();
            imwrap::checkbox("spoof name", opt::spoof_name, "sets requestedName to randomized string");

            //  menu::InputTextSTL("##serverval", &opt::custom_server_val);
            ImGui::EndChild();
        }
    }

}