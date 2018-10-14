/******************************************************************
* File:        ImWidget.h
* Description: declare ImWidget class. This is base class of UI
*              controlls that use ImGui to render.
* Author:      Vincent Pham
*
* Copyright (c) 2018 VincentPT.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#pragma once
#include "Widget.h"
#include "CinderImGui.h"

class ImWidget : public Widget
{
protected:
	ImVec2 _window_pos;
	ImVec2 _window_size;
	ImGuiWindowFlags _window_flags;
public:
	ImWidget();
	virtual ~ImWidget();

	virtual void update();
	virtual void draw();
	virtual void setSize(float w, float h);
	virtual void setPos(float x, float y);
	float getWidth();
	float getHeight();
	float getX();
	float getY();
};

