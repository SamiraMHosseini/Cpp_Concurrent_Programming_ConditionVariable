# Practice-Multithreading
​CPP_Multithreaded_Practice_RecursiveLock ​

A recursive mutex in C++ is a type of mutex (short for "mutual exclusion") that allows the same thread to lock it multiple times, whereas a non-recursive mutex will deadlock if the same thread tries to lock it more than once.

A mutex is used in multithreaded programming to ensure that only one thread at a time can access a shared resource, such as a data structure or a file, to prevent race conditions and other synchronization issues. By allowing the same thread to lock a recursive mutex multiple times, it allows the thread to perform a series of operations that require exclusive access to the resource, without having to worry about releasing the lock prematurely.

In C++, you can create a recursive mutex using std::recursive_mutex. To use it, you lock the mutex using lock() method and release it using unlock().

Until the lock count of a recursive mutex reaches zero, meaning that all locks have been released, no other thread can access the resource protected by the mutex. This ensures that the shared resource can only be accessed by one thread at a time, avoiding synchronization problems and race conditions.

Each time a thread locks a recursive mutex, the lock count is incremented, and each time the thread unlocks the mutex, the lock count is decremented. The mutex is only released when the lock count reaches zero, meaning that all locks have been released. At this point, other threads are free to lock the mutex and access the shared resource.

In this way, a recursive mutex provides exclusive access to a shared resource, ensuring that multiple threads can access the resource safely and efficiently, even if the same thread needs to lock and unlock the mutex multiple times.
