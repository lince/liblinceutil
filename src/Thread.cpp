#include "../include/Thread.h"

using namespace std;

namespace cpputil {

	Thread::Thread() {
		pthread_mutex_init(&threadMutex, NULL);

		isSleeping = false;
		pthread_mutex_init(&threadFlagMutex, NULL);
		pthread_mutex_init(&threadFlagMutexLockUntilSignal, NULL);

		isWaiting = false;
		pthread_cond_init(&threadFlagConditionVariable, NULL);
		pthread_cond_init(&threadFlagCVLockUntilSignal, NULL);
	}

	Thread::~Thread() {
		wakeUp();
		pthread_cond_signal(&threadFlagConditionVariable);
		pthread_cond_destroy(&threadFlagConditionVariable);

		unlockConditionSatisfied();
		pthread_cond_signal(&threadFlagCVLockUntilSignal);
		pthread_cond_destroy(&threadFlagCVLockUntilSignal);

		pthread_mutex_unlock(&threadMutex);
		pthread_mutex_destroy(&threadMutex);

		pthread_mutex_unlock(&threadFlagMutex);
		pthread_mutex_destroy(&threadFlagMutex);

		pthread_mutex_unlock(&threadFlagMutexLockUntilSignal);
		pthread_mutex_destroy(&threadFlagMutexLockUntilSignal);
	}

	void* Thread::function(void* ptr) {
		if (!ptr) {
			return NULL;
		}

		static_cast<Thread*>(ptr)->run();
		pthread_exit(ptr);
		return NULL;
	}

	void Thread::start() {
		pthread_create(&threadId_, 0, Thread::function, this);
		pthread_detach(threadId_);
	}

	bool Thread::sleep(long int seconds) {
		return this->usleep(seconds * 1000);
	}

	bool Thread::usleep(long int milliseconds) {
		isSleeping = true;
		int res;
		struct timeval time;
		struct timespec timeOut;

		gettimeofday(&time, NULL);
		timeOut.tv_sec = time.tv_sec + (long int)(milliseconds / 1000);
		long int micro;
		micro = ((milliseconds%1000) * 1000) + time.tv_usec;
		if (micro > 1000000) {
			timeOut.tv_sec++;
			micro -= 1000000;
		}

		timeOut.tv_nsec = micro * 1000;

		pthread_mutex_lock(&threadFlagMutex);
		res = pthread_cond_timedwait(
			    &threadFlagConditionVariable,
			    &threadFlagMutex,
			    (const struct timespec*)(&timeOut));

		pthread_mutex_unlock(&threadFlagMutex);
		isSleeping = false;
		return (res == ETIMEDOUT);
	}

	void Thread::wakeUp() {
		if (isSleeping) {
			pthread_cond_signal(&threadFlagConditionVariable);
		}
		isSleeping = false;
	}

	void Thread::lock() {
		pthread_mutex_lock(&threadMutex);
	}

	void Thread::unlock() {
		pthread_mutex_unlock(&threadMutex);
	}

	void Thread::waitForUnlockCondition() {
		isWaiting = true;
		pthread_mutex_lock(&threadFlagMutexLockUntilSignal);
		pthread_cond_wait(
			    &threadFlagCVLockUntilSignal, &threadFlagMutexLockUntilSignal);

		isWaiting = false;
		pthread_mutex_unlock(&threadFlagMutexLockUntilSignal);
	}

	bool Thread::unlockConditionSatisfied() {
		if (isWaiting) {
			pthread_cond_signal(&threadFlagCVLockUntilSignal);
			return true;
		}
		return false;
	}

}
