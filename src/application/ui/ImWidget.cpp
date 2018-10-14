/******************************************************************
* File:        ImWidget.cpp
* Description: implement ImWidget class. This is base class of UI
*              controlls that use ImGui to render.
* Author:      Vincent Pham
*
* Copyright (c) 2018 VincentPT.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#include "ImWidget.h"

ImWidget::ImWidget() : _window_size(300, 200)
{
	_window_flags = 0;
	//_window_flags |= ImGuiWindowFlags_NoTitleBar;
	//_window_flags |= ImGuiWindowFlags_MenuBar;
	//_window_flags |= ImGuiWindowFlags_NoMove;
	//_window_flags |= ImGuiWindowFlags_NoResize;
	//_window_flags |= ImGuiWindowFlags_NoCollapse;
}


ImWidget::~ImWidget()
{
}

void ImWidget::update() {}
void ImWidget::draw() {}

void ImWidget::setSize(float w, float h) {
	_window_size.x = w;
	_window_size.y = h;
}

float ImWidget::getWidth() {
	return _window_size.x;
}

float ImWidget::getHeight() {
	return _window_size.y;
}

void ImWidget::setPos(float x, float y) {
	_window_pos.x = x;
	_window_pos.y = y;
}

float ImWidget::getX() {
	return _window_pos.x;
}

float ImWidget::getY() {
	return _window_pos.y;
}
