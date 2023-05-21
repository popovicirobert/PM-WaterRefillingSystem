#pragma once

#include "ArduinoSTL.h"
#include "set"

class EventHandler {
public:
	template<typename T>
	void addEvent(long long expireTime, const T& callback) {
		static long long lastEventId = 0;
		BaseEvent* event = new Event<T>(lastEventId, expireTime, callback);
		lastEventId++;
		eventQueue.insert(event);
	}

	void checkEvents() {
		long long tickCounter = clock_1ms::getTickCounter();
		while (!eventQueue.empty()) {
			BaseEvent* event = *eventQueue.begin();
			if (event->expireTime <= tickCounter) {
				eventQueue.erase(eventQueue.begin());
				event->call();
				delete event;
			} else {
				break;
			}
		}
	}
	
private:
	struct BaseEvent {
		long long eventId;
		long long expireTime;

		BaseEvent(long long eventId, long long expireTime) {
			this->eventId = eventId;
			this->expireTime = expireTime;
		}

		bool operator<(const BaseEvent& rhs) const {
			if (expireTime == rhs.expireTime)
				return eventId < rhs.eventId;
			return expireTime < rhs.expireTime;
		}

		virtual void call() {
			// can't make it pure virtual because we need to use less than operator inside set comparator
		}
	};

	template<typename T>
	struct Event : public BaseEvent {
		const T& callback;

		Event(long long eventId, long long expireTime, const T& callback) 
			: BaseEvent(eventId, expireTime),
			  callback(callback) {}

		void call() override {
			callback();
		}
	};
	
private:

	struct EventComparator {
		bool operator()(const BaseEvent* e1, const BaseEvent* e2) const {
			return *e1 < *e2;
		}
	};

	std::set<BaseEvent*, EventComparator> eventQueue;
};
