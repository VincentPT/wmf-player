#pragma once
#include <mutex>
#include <list>

template <class T>
class SyncMessageQueue
{
	std::list<T> _messageQueue;
	std::mutex _messageQueueMutex;
	std::condition_variable _hasMessageCV;
public:
	SyncMessageQueue() {}
	virtual ~SyncMessageQueue() {}

	void pushMessage(const T& message) {
		std::lock_guard<std::mutex> lk(_messageQueueMutex);
		_messageQueue.push_back(message);
		_hasMessageCV.notify_one();
	}

	void pushMessageFront(const T& message) {
		std::lock_guard<std::mutex> lk(_messageQueueMutex);
		_messageQueue.push_front(message);
		_hasMessageCV.notify_one();
	}

	void popMessage(T& message) {
		std::unique_lock<std::mutex> lk(_messageQueueMutex);
		_hasMessageCV.wait(lk, [this, &message] {
			if (_messageQueue.size() > 0) {
				message = _messageQueue.front();
				_messageQueue.pop_front();
				return true;
			}

			return false;
		});
	}

	bool popMessage(T& message, unsigned int waitTimeMiliSeconds) {
		std::unique_lock<std::mutex> lk(_messageQueueMutex);

		std::chrono::duration<decltype(waitTimeMiliSeconds), std::milli> timeout(waitTimeMiliSeconds);
		bool res = _hasMessageCV.wait_for(lk, timeout, [this, &message] {
			if (_messageQueue.size() > 0) {
				message = _messageQueue.front();
				_messageQueue.pop_front();
				return true;
			}

			return false;
		});

		return res;
	}

	template <class Fx>
	void removeMessage(Fx fx) {
		std::unique_lock<std::mutex> lk(_messageQueueMutex);
		_messageQueue.remove_if(fx);
	}

	void clear() {
		std::unique_lock<std::mutex> lk(_messageQueueMutex);
		_messageQueue.clear();
	}
};


template <class T>
class SemiSyncMessageQueue
{
	std::list<T> _messageQueue;
	std::mutex _messageQueueMutex;
public:
	SemiSyncMessageQueue() {}
	virtual ~SemiSyncMessageQueue() {}

	void pushMessage(const T& message) {
		std::lock_guard<std::mutex> lk(_messageQueueMutex);
		_messageQueue.push_back(message);
	}

	void pushMessage(T&& message) {
		std::lock_guard<std::mutex> lk(_messageQueueMutex);
		_messageQueue.push_back(message);
	}

	void pushMessageFront(const T& message) {
		std::lock_guard<std::mutex> lk(_messageQueueMutex);
		_messageQueue.push_front(message);
	}

	void pushMessageFront(T&& message) {
		std::lock_guard<std::mutex> lk(_messageQueueMutex);
		_messageQueue.push_front(message);
	}

	bool tryPopMessage(T& message) {
		std::unique_lock<std::mutex> lk(_messageQueueMutex);
		if (_messageQueue.size() == 0) return false;

		message = _messageQueue.front();
		_messageQueue.pop_front();

		return true;
	}

	template <class Fx>
	void removeMessage(Fx fx) {
		std::unique_lock<std::mutex> lk(_messageQueueMutex);
		_messageQueue.remove_if(fx);
	}

	void clear() {
		std::unique_lock<std::mutex> lk(_messageQueueMutex);
		_messageQueue.clear();
	}
};

template <class T>
class Signal
{
	T _signal;
	bool _notifyAll;
	bool _signalReceived;
	std::mutex _signalMutex;
	std::condition_variable _hasMessageCV;
	std::function<bool()> _checkSignalFunc;
public:
	Signal(bool notifyToAll) : _notifyAll(notifyToAll), _signalReceived(false) {
		_checkSignalFunc = std::bind(&Signal::checkSignal, this);
	}
	virtual ~Signal() {}

	void resetState(const T& resetSignalVale) {
		std::lock_guard<std::mutex> lk(_signalMutex);
		_signal = resetSignalVale;
		_signalReceived = false;
	}

	void sendSignal(const T& signal) {
		{
			std::lock_guard<std::mutex> lk(_signalMutex);
			_signal = signal;
			_signalReceived = true;
		}
		if (_notifyAll) {
			_hasMessageCV.notify_all();
		}
		else {
			_hasMessageCV.notify_one();
		}
	}

	bool waitSignal(T& signal, unsigned int miliseconds) {
		std::unique_lock<std::mutex> lk(_signalMutex);

		std::chrono::duration<decltype(miliseconds), std::milli> timeout(miliseconds);

		bool res = _hasMessageCV.wait_for(lk, timeout, _checkSignalFunc);

		if (res) {
			signal = _signal;
		}

		return res;
	}

	bool checkSignal() {
		if (_signalReceived) {
			if (!_notifyAll) _signalReceived = false;
			return true;
		}

		return false;
	}

	void waitSignal(T& signal) {
		std::unique_lock<std::mutex> lk(_signalMutex);
		_hasMessageCV.wait(lk, _checkSignalFunc);

		signal = _signal;
	}
};

class SignalAny
{
	bool _notifyAll;
	bool _signalReceived;
	std::mutex _signalMutex;
	std::condition_variable _hasMessageCV;
	std::function<bool()> _checkSignalFunc;
public:
	SignalAny(bool notifyToAll) : _notifyAll(notifyToAll), _signalReceived(false) {
		_checkSignalFunc = std::bind(&SignalAny::checkSignal, this);
	}
	virtual ~SignalAny() {}

	void resetState() {
		std::lock_guard<std::mutex> lk(_signalMutex);
		_signalReceived = false;
	}

	void signal() {
		{
			std::lock_guard<std::mutex> lk(_signalMutex);
			_signalReceived = true;
		}
		if (_notifyAll) {
			_hasMessageCV.notify_all();
		}
		else {
			_hasMessageCV.notify_one();
		}
	}

	bool waitSignal(unsigned int miliseconds) {
		std::unique_lock<std::mutex> lk(_signalMutex);

		std::chrono::duration<decltype(miliseconds), std::milli> timeout(miliseconds);

		return _hasMessageCV.wait_for(lk, timeout, _checkSignalFunc);
	}

	bool checkSignal() {
		if (_signalReceived) {
			if (!_notifyAll) _signalReceived = false;
			return true;
		}

		return false;
	}

	void waitSignal() {
		std::unique_lock<std::mutex> lk(_signalMutex);
		_hasMessageCV.wait(lk, _checkSignalFunc);
	}
};
