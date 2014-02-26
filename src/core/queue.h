// This file is part of the :(){ :|:& };:'s project
// Licensing information can be found in the LICENSE file
// (C) 2014 :(){ :|:& };:. All rights reserved.
#ifndef __CORE_QUEUE_H__
#define __CORE_QUEUE_H__

// -----------------------------------------------------------------------------
// Lock-free queue
// This structure is intended to be used to communicate between two threads:
// one producer and one consumer
// If no messages are available, the receiver will block until the other threads
// sends a message
// If there is no space in the queue, the sender will block until the receiver
// Processes enough messages and frees up space
// -----------------------------------------------------------------------------
template<typename T, int Capacity>
class AsyncQueue
{
public:
  // Creates an empty queue
  AsyncQueue()
    : head(0)
    , tail(0)
  {
  }

  // Adds an element to the end of the queue (called from producer)
  void Push(const T& elem)
  {
    while ((head + 1) % Capacity == tail);

    data[head] = elem;
    head = (head + 1) % Capacity;
  }

  // Removes an element from the front of the queue (called from consumer)
  T Pop()
  {
    T temp;

    while (head == tail);

    temp = data[tail];
    tail = (tail + 1) % Capacity;

    return temp;
  }

  // Returns the number of elements in the queue
  size_t Size()
  {
    return head > tail ? (head - tail) : (Capacity - tail + head);
  }

  // Checks whether the queue is empty
  bool Empty()
  {
    return head == tail;
  }

private:
  T                data[Capacity];
  volatile size_t  head;
  volatile size_t  tail;
};

#endif
