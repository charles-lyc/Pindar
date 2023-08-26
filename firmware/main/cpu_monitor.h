#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include <vector>
#include <string>
#include <iostream>

class CPU_Monitor {
private:
	TaskHandle_t task_handle = nullptr;

	CPU_Monitor()
	{
		xTaskCreate(&process, "monitor", 2048, NULL, 6, &task_handle);
		vTaskSuspend(task_handle);
	}

	~CPU_Monitor()
	{
		vTaskDelete(task_handle);
	}

	struct TaskInfo {
		uint32_t id;
		std::string name_n_status;
		uint8_t cpu_usage;
		uint32_t mem_remaining;
	};

	static void process(void *param)
	{
		char InfoBuffer[1024] = {0};
		std::vector<struct TaskInfo> tasks_status;

		while (1) {
			tasks_status.clear();

			vTaskList((char *) &InfoBuffer);
			// printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");


			vTaskGetRunTimeStats((char *) &InfoBuffer);
			// printf("\r\n任务名\t\t\t\t运行计数\t\t\t\t使用率\r\n");

			std::cout << "id\t\tname\t\tcpu\t\tmem" << std::endl;
			for (auto n : tasks_status) {
				std::cout << n.id << "\t\t" << n.name_n_status << "\t\t" << n.cpu_usage << "\t\t" << n.mem_remaining << std::endl;
			}

			vTaskDelay(1000 / portTICK_PERIOD_MS);
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

