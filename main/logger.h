#pragma once

class Logger {
private:
	Logger() {
		memset(buffer, 0, sizeof(buffer));
		size = 0;
	}
	
	void flush() {
		if (size == 0)
			return;
	
		Serial.print(buffer);
		
		size = 0;
		memset(buffer, 0, sizeof(buffer));
	}

	void _append(char ch) {
		buffer[size++] = ch;
		if (size == BUFFER_SIZE) {
			flush();
		}
	}

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

	Logger& append(long long arg) {
		static constexpr int MAX_DIGITS = 64;
		char digits[MAX_DIGITS];
	
		int len = 0;
		while (arg > 0) {
			digits[len++] = arg % 10 + '0';
			arg /= 10;
		}

		while (len--) {
			_append(digits[len]);
		}
			
		return *this;
	}

	Logger& append(int arg) {
		return append((long long)arg);
	}

	Logger& append(char arg) {
		_append(arg);
		return *this;
	}

	Logger& append(const char* arg) {
		while (*arg != '\0') {
			_append(*arg);
			arg++;
		}
		return *this;
	}

	void commit() {
		_append('\n');
		flush();
	}

	Logger& debug() {
		return append("[DEBUG]: ");
	}

	Logger& info() {
		return append("[INFO]: ");
	}

	Logger& warn() {
		return append("[WARN]: ");
	}

	Logger& error() {
		return append("[ERROR]: ");
	}

private:
	static Logger* logger;
	
	static constexpr int BUFFER_SIZE = 127;
	char buffer[BUFFER_SIZE + 1];
	int size = 0;
};

Logger* Logger::logger = nullptr;
