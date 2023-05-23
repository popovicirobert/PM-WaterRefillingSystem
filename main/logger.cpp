#include "logger.h"

Logger* Logger::logger = nullptr;

Logger::Logger() {
    memset(buffer, 0, sizeof(buffer));
    size = 0;
}

void Logger::flush() {
    if (size == 0)
        return;

    Serial.print(buffer);
    
    size = 0;
    memset(buffer, 0, sizeof(buffer));
}

void Logger::_append(char ch) {
    buffer[size++] = ch;
    if (size == BUFFER_SIZE) {
        flush();
    }
}

Logger& Logger::append(long long arg) {
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

Logger& Logger::append(int arg) {
    return append((long long)arg);
}

Logger& Logger::append(char arg) {
    _append(arg);
    return *this;
}

Logger& Logger::append(const char* arg) {
    while (*arg != '\0') {
        _append(*arg);
        arg++;
    }
    return *this;
}

void Logger::commit() {
    _append('\n');
    flush();
}

Logger& Logger::debug() {
    return append("[DEBUG]: ");
}

Logger& Logger::info() {
    return append("[INFO]: ");
}

Logger& Logger::warn() {
    return append("[WARN]: ");
}

Logger& Logger::error() {
    return append("[ERROR]: ");
}
