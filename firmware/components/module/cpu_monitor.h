#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"

#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include <unordered_map>

class CPU_Monitor {
private:
	TaskHandle_t task_handle = nullptr;

	CPU_Monitor()
	{
		xTaskCreate(&process, "monitor", 4096 * 5, NULL, 6, &task_handle);
		vTaskSuspend(task_handle);
	}

	~CPU_Monitor()
	{
		vTaskDelete(task_handle);
	}

	// struct TaskInfo {
	//  uint32_t id;
	//  std::string name_n_status;
	//  uint8_t cpu_usage;
	//  uint32_t mem_remaining;
	// };

	// struct TaskInfo {
	//  // std::string name;
	//  char status;
	//  uint8_t priority;
	//  uint32_t mem_remain;
	//  uint8_t task_number;
	//  int8_t core;    // -1 for not specified pin to core

	//  uint32_t count;
	//  std::string cpu_usage;
	// };

	static void process(void *param)
	{
		char info_buffer[50 * 20] = {0};     // 20 tasks
		// std::regex pattern;
		// std::smatch matches;
		// std::string line;
		// std::unordered_map<std::string, std::string> map;

		while (1) {
			// tasks_status.clear();

			vTaskList((char *) info_buffer);
			// std::istringstream stream1(info_buffer);
			std::cout << info_buffer << std::endl;

			vTaskGetRunTimeStats((char *) info_buffer);
			// std::istringstream stream2(info_buffer);
			std::cout << info_buffer << std::endl;

			// 双核的版本，IDLE有两个，并且vTaskGetRunTimeStats不带coreID信息，无法合并，算球~~
			// merge_taskinfo(map, stream1, stream2);

			// for (const auto &n : map) {
			//  std::cout << n.first << ": " << n.second << std::endl;
			// }

			vTaskDelay(2000 / portTICK_PERIOD_MS);
		}
	}

	// 以stream1的名字为准
	// 方法一：使用istringstream输入来提取（适合简单规律的情况）
	// 方法二：正则表达式（适合于更加复杂的情况）
	// 方法三：甚至不需要取出来，就是拼接一下字符串而已。
	static void merge_taskinfo(std::unordered_map<std::string, std::string> &map, std::istringstream &stream1, std::istringstream &stream2)
	{
		std::string line;
		std::string name;
		std::string rest;

		map.clear();

		// 对于map中没有的key，会自动添加条目
		while (std::getline(stream1, line)) {
			name.clear();
			rest.clear();

			// std::cout << "origin1:" << line << std::endl;
			std::istringstream lineStream1(line);
			lineStream1 >> name;
			std::getline(lineStream1, rest);
			map[name] = rest;

			std::cout << "map1[name]:" << name << ":" << map[name] << std::endl;
		}

		line.clear();
		name.clear();
		rest.clear();

		while (std::getline(stream2, line)) {
			name.clear();
			rest.clear();

			// std::cout << "origin2:" << line << std::endl;
			std::istringstream lineStream2(line);
			lineStream2 >> name;
			std::getline(lineStream2, rest);
			map[name] += rest;

			std::cout << "map2[name]:" << name << ":" << map[name] << std::endl;
		}

	}

public:

	static CPU_Monitor *get_instance()
	{
		static CPU_Monitor *instance;
		if (!instance) {
			instance = new CPU_Monitor();
		}
		return instance;
	}

	int start()
	{
		vTaskResume(task_handle);
		return 0;
	}

	int stop()
	{
		vTaskSuspend(task_handle);
		return 0;
	}
};

