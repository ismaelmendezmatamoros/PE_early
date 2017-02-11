#pragma once

template<typename T>
struct pointerOperationsWrapper  {
	T* pointer;
	pointerOperationsWrapper(T* ptr) :pointer(ptr) {};
	bool operator > (const T&& other) { *pointer > *other; };
	bool operator < (const T&& other) { *pointer < *other; };
	bool operator == (const T&& other) { *pointer == *other; };
	T& operator* {return *pointer; };
	T& operator -> {return *pointer; };
	//T& operator -> {return *pointer; };
};

#define MILISECONDS_TIPE std::chrono::system_clock::time_point//std::chrono::milliseconds	//clock_t

#define ID_COUNTER_TYPE std::atomic<ID_TYPE>
#define ID_TYPE unsigned long

#define TASK_LAMBDA void()
#define TASKS_QUEUED_TYPE PE_ScheduledTask*
