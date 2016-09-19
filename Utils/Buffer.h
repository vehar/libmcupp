#pragma once

#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#ifndef nullptr
#define nullptr NULL
#endif

#ifndef override
#define override
#endif

namespace Utils {
	class Buffer {
	public:
		Buffer(uint8_t* buffer = nullptr, size_t size = 0) 
			: buffer(buffer), size(size), iter(0), _isLocked(false) {}

		uint8_t&	operator[]	(size_t index) { return this->buffer[index]; }
		operator 	uint8_t*	() { return this->buffer; }
		operator 	size_t		() { return this->size; }

		bool		isValid 	() { return (this->buffer != nullptr && this->size > 0); }
		bool		isLocked 	() const { return this->_isLocked; }
		bool		isEmpty		() { return this->iter == 0; }
		bool		isEnd 		() { return this->iter >= this->size; }

		void 		set 		(uint8_t* buffer, size_t size) { this->buffer = buffer; this->size = size; this->iter = 0; }
		void		erase		() { if(this->buffer != nullptr && this->size != 0) { for(size_t i = 0; i < this->size; ++i) { this->buffer[i] = 0x00; } } this->iter = 0; }
		void		reset		() { this->iter = 0; }
		void		moveUp		() { this->iter++; }
		void		moveDown	() { this->iter--; }
		void		add 		(uint8_t data) { if(!this->isEnd()) { this->buffer[this->iter] = data; this->iter++; } }

		void		lock 		() { this->_isLocked = true; } 
		void		unlock		() { this->_isLocked = false; }

		uint8_t* 	getBuffer	() { return this->buffer; }
		size_t		getSize		() { return this->size; }
		size_t&		getIter		() { return this->iter; }

		uint8_t&	getCurrent	() { return this->buffer[this->iter]; }
	private:
		uint8_t* 	buffer;
		size_t 		size;

		size_t 		iter;
		bool		_isLocked;
	};
}