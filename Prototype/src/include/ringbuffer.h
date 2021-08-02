//Ring Buffer In-Place
#ifndef RINGBUFFER_H
#define RINGBUFFER_H


namespace Gib {
	template <class T>
	class RingBuffer {
	private:
		static const unsigned short BUFFER_SIZE = 16;
		T buffer[BUFFER_SIZE];
		T* held;

		unsigned short headIndex = 0;
		unsigned short tailIndex = 0;
	public:
		RingBuffer<T>();

		T& updateTail(); //push
		T& getHead(); //pop

		const bool empty() {return headIndex == tailIndex;}
	};
}


template <class T>
Gib::RingBuffer<T>::RingBuffer() {
	for(unsigned short i = 0; i < BUFFER_SIZE; i += 1) {
		buffer[i] = T();
	}
}


template <class T>
T& Gib::RingBuffer<T>::updateTail() {
	held = &buffer[tailIndex];
	tailIndex += 1;

	if(tailIndex == BUFFER_SIZE) {
		tailIndex = 0;
	}

	if(tailIndex + 1 == headIndex) {
		//log an error that next last available queue index was taken. Next enqueue may overwrite unprocessed objects
	}

	return *held;
}


template <class T>
T& Gib::RingBuffer<T>::getHead() {
	if(headIndex == tailIndex) {
		//queue is either full or empty- assume empty for safety
	}

	held = &buffer[headIndex];
	//buffer[headIndex] = nullptr;

	headIndex += 1;
	if(headIndex == BUFFER_SIZE) {
		headIndex = 0;
	}

	if(headIndex == tailIndex) {
		//now empty
	}

	return *held;

	/*if(headIndex == tailIndex) {
		//queue is either full or empty- assume empty for safety
		return nullptr;
	}

	held = buffer[headIndex];
	buffer[headIndex] = nullptr;

	headIndex += 1;
	if(headIndex == BUFFER_SIZE) {
		headIndex = 0;
	}

	if(headIndex == tailIndex) {
		//now empty
	}

	return held;*/
}


/*
template <class T>
void Gib::RingBuffer<T>::push(T& obj) {
	buffer[tailIndex] = &obj;
	tailIndex += 1;

	if(tailIndex == BUFFER_SIZE) {
		tailIndex = 0;
	}

	if(tailIndex + 1 == headIndex) {
		//log an error that next last available queue index was taken. Next enqueue may overwrite unprocessed objects
	}
}
*/

#endif