# Philosophers

The philosopher's problem is a classic synchronization problem in computer science that highlights challenges in resource allocation and deadlock prevention. Imagine a group of philosophers seated around a circular table, with a bowl of spaghetti placed between each pair of adjacent philosophers. Each philosopher alternates between thinking and eating, using a single fork to eat the spaghetti. However, to eat, a philosopher must have both forks. The problem arises when each philosopher grabs the fork to their left, resulting in a deadlock, as no philosopher can proceed without acquiring the fork to their right. Various strategies, such as using semaphore-based solutions or introducing a dining protocol, can be employed to ensure fair resource allocation and prevent deadlock in this scenario.

## Table of Contents

- [Semaphore Solution](#Semaphore Solution)
- [Mutex Solution](#Mutex Solution)
- [Difference between Semaphore and Mutex](#Difference between Semaphore and Mutex)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Semaphore Solution:
In the context of synchronization, a semaphore is a variable used to control access to a shared resource. Semaphores can have a certain number of permits associated with them, and these permits act as tokens that determine how many threads can access the resource concurrently. The two main operations associated with semaphores are "wait" (decrementing the count of permits) and "post" (incrementing the count of permits). 

In the philosopher's problem, a semaphore can be used to represent the forks. Each philosopher will try to acquire the forks by performing a "wait" operation on the corresponding semaphore. If the philosopher successfully acquires both forks, they can proceed to eat. After finishing, they release the forks by performing a "post" operation on the corresponding semaphore.

## Mutex Solution:
A mutex (short for mutual exclusion) is another synchronization mechanism used to prevent multiple threads from accessing a shared resource simultaneously. Unlike a semaphore, a mutex can only have two states: locked or unlocked. When a thread wants to access the protected resource, it attempts to acquire the mutex. If the mutex is currently locked by another thread, the requesting thread will be blocked until the mutex becomes available.

In the philosopher's problem, each fork can be represented by a mutex. When a philosopher wants to eat, they attempt to acquire both fork mutexes. If a mutex is already locked (i.e., the fork is in use by another philosopher), the requesting philosopher will wait until the mutex is released. Once they have acquired both fork mutexes, they can eat and then release the mutexes for other philosophers to use.

## Difference between Semaphore and Mutex:
The main difference between semaphores and mutexes lies in their usage and functionality. 

1. Counting vs. Binary: Semaphores can have a count greater than 1, allowing a specified number of threads to access a resource simultaneously. Mutexes, on the other hand, are binary and can only be locked or unlocked, allowing only one thread to access a resource at a time.

2. Ownership: Mutexes typically have ownership, meaning the thread that locked the mutex is responsible for unlocking it. In contrast, semaphores do not have ownership, and any thread can signal (increment permits) on a semaphore, regardless of which thread performed the wait operation.

3. Waiting: In the case of a semaphore, multiple threads can wait on the same semaphore and be woken up when a signal occurs. With a mutex, only the thread that initially acquired the mutex can unlock it, meaning no other thread can unlock a mutex on behalf of another thread.

In summary, semaphores are more versatile and can allow a specified number of threads to access a resource simultaneously, while mutexes are binary and provide mutual exclusion, allowing only one thread at a time to access a shared resource.

## Usage

`./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]`
- number_of_philosophers: The number of philosophers and also the number
of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
