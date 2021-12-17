#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>
#include <Windows.h>
#include <hooks/hooks.h>
#include <core/gt.h>


void menu::visuals_tab() {
    ImGui::Text("every change made here is going to be client-sided.");
    if (ImGui::Button("Legendary Wings (in build)")) {
       // auto local = sdk::GetGameLogic()->GetLocalPlayer();
       
       
    }
    ImGui::EndChild();
}