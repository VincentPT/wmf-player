/******************************************************************
* File:        UIThreadRunner.h
* Description: declare UIThreadRunner class. An instance of this
*              class allows user push a task from any thread then
*              execute the task in UI thread.
* Author:      Vincent Pham
*
* Copyright (c) 2018 VincentPT.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#pragma once
#include "../common/SyncMessageQueue.hpp"
#include <functional>

typedef std::function<void(float)> UpdateTask;

class UIThreadRunner
{
protected:
	SemiSyncMessageQueue<UpdateTask> _tasks;
public:
	UIThreadRunner();
	virtual ~UIThreadRunner();

	void postTask(UpdateTask&& task);
	void executeTasks(float t);
};