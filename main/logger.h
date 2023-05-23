#pragma once

#include <Arduino.h>
#include <cstring>

class Logger {
private:
	Logger();
	
	void flush();

	void _append(char ch);

public:
	Logger(const Logger& rhs) = delete;
	Logger(Logger&& rhs) = delete;
	Logger& operator=(const Logger& rhs) = delete;
	Logger& operator=(Logger&& rhs) = delete;

	static void setup(int baudRate) {
		if (logger != nullptr)
			return;

		Serial.begin(baudRate);
		logger = new Logger();
	}
	
	static Logger& getLogger() {
		return *logger;
	}

	template<typename T, typename... Args>
	Logger& append(T value, Args... args) {
		append(value);
		return append(args...);
	}

	Logger& append(long long arg);

	Logger& append(int arg);

	Logger& append(char arg);

	Logger& append(const char* arg);

	void commit();

	Logger& debug();

	Logger& info();

	Logger& warn();

	Logger& error();

private:
	static Logger* logger;
	
	static constexpr int BUFFER_SIZE = 127;
	char buffer[BUFFER_SIZE + 1];
	int size = 0;
};
