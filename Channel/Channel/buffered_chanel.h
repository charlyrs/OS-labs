#pragma once
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <map>

template <class T>
class BufferedChannel {
	
	std::queue<T> container;
	std::condition_variable cv;
	std::mutex mutex;
	int buffer_size;
	bool is_opened;
public:
	BufferedChannel(int size);
	BufferedChannel();
	BufferedChannel& operator =(BufferedChannel&& other);
	void Send(T value);
	std::pair<T, bool> Recv();
	void Close();

};
template <class T>
BufferedChannel<T>::BufferedChannel(int size)
{
	buffer_size = size;
	is_opened = true;
}
template <class T>
BufferedChannel<T>::BufferedChannel()
{
	buffer_size = 10;
	is_opened = true;
}
template <class T>
BufferedChannel<T>& BufferedChannel<T>::operator=(BufferedChannel<T>&& other)
{
	if (this != &other)
	{
		container = other.container;
	}
	return *this;
}

template <class T>
void BufferedChannel<T>::Send(T value)
{
	std::unique_lock<std::mutex> u(mutex);
	if (!is_opened) {
		throw std::runtime_error("Channel is closed");
	}
		
	
	cv.wait(u, [&] {return !(container.size() == buffer_size); });
	container.push(value);
	u.unlock();
	cv.notify_one();	
}

template <class T>
std::pair<T, bool> BufferedChannel<T>::Recv()
{
	std::unique_lock<std::mutex> u(mutex);
	cv.wait(u, [&] {return !container.empty(); });
	T val = container.front();
	container.pop();
	u.unlock();
	cv.notify_one();
	return std::pair<T, bool>(val, is_opened);
}
template <class T>
void BufferedChannel<T>::Close()
{
	std::unique_lock<std::mutex> u(mutex);
	is_opened = false;	
	u.unlock();
	cv.notify_one();
}