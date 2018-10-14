/******************************************************************
* File:        ImPopup.cpp
* Description: implement ImPopup class. This is a popup dialog class
*              that use ImGUI to render.
* Author:      Vincent Pham
*
* Copyright (c) 2018 VincentPT.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#include "ImPopup.h"

ImGuiID ImPopup::_autoIdGenerator = 0;

ImPopup::ImPopup(const std::string& name) :_isOpen(false) {
	_popUpId = name + "##";
	_autoIdGenerator++;
	_popUpId.append(std::to_string(_autoIdGenerator));
}

ImPopup::~ImPopup() {

}

void ImPopup::showWindow(bool show) {
	_isOpen = show;
}

void ImPopup::update()
{
	if (_isOpen == false) {
		return;
	}

	if (!ImGui::IsPopupOpen(_popUpId.c_str())) {
		ImGui::SetNextWindowSize(_window_size, ImGuiCond_Always);

		ImGui::OpenPopup(_popUpId.c_str());
	}
	//if (ImGui::BeginPopup(_popUpId.c_str(), _window_flags)) {
	if (ImGui::BeginPopupModal(_popUpId.c_str(), &_isOpen, _window_flags)) {
		updateContent();

		ImGui::EndPopup();
		return;
	}
}