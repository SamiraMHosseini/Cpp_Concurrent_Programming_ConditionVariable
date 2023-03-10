#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

struct SharedResource
{
	SharedResource() :
		cv_mutex(), cv(), counter(0)
	{

	}

	/*
	This mutex is used for three purposes:
	1) to synchronize accesses to counter
	2) to synchronize accesses to std::cerr
	3) for the condition variable cv
	*/
	std::mutex cv_mutex;
	std::condition_variable cv;
	int counter;
};

void waits(SharedResource& sharedRes)
{
	std::unique_lock<std::mutex> lk(sharedRes.cv_mutex);
	std::cerr << "Waiting... \n";
	//Solution1
	while (!(sharedRes.cv.wait_for(lk, std::chrono::duration(3s), [&]() { return (sharedRes.counter == 1); })))
	{

		std::cerr << "Thread ID: " << std::this_thread::get_id() << " wakes up every 3 second.\n";
	}

	std::cerr << "...finished waiting." << "counter: " << sharedRes.counter << std::endl;
} //The lk object will be unlocked after this scope ends.

void signals(SharedResource& sharedRes)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lk(sharedRes.cv_mutex);
		std::cerr << "Notifying...\n";
	} // The lk object will be unlocked after this scope ends.
	sharedRes.cv.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(12));

	{
		std::lock_guard<std::mutex> lk(sharedRes.cv_mutex);
		sharedRes.counter = 1;
		std::cerr << "Notifying again...\n";
	} // The lk object will be unlocked after this scope ends.
	sharedRes.cv.notify_all();
}

int main()
{
	SharedResource sharedRes;

	std::thread
		t1(waits, std::ref(sharedRes)),
		t2(waits, std::ref(sharedRes)),
		t3(waits, std::ref(sharedRes)),
		t4(signals, std::ref(sharedRes));
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}



