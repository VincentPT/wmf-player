/******************************************************************
* File:        UIThreadRunner.cpp
* Description: implement UIThreadRunner class. An instance of this
*              class allows user push a task from any thread then
*              execute the task in UI thread.
* Author:      Vincent Pham
*
* Copyright (c) 2018 VincentPT.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#include "UIThreadRunner.h"

UIThreadRunner::UIThreadRunner() {
}

UIThreadRunner::~UIThreadRunner() {
}

void UIThreadRunner::postTask(UpdateTask&& task) {
	_tasks.pushMessage(std::move(task));
}

void UIThreadRunner::executeTasks(float t) {
	UpdateTask task;
	while (_tasks.tryPopMessage(task))
	{
		task(t);
	}
}