#include "guiManager.h"

GuiManager::GuiManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
}

GuiManager::~GuiManager()
{
	ImGui::DestroyContext();
}
