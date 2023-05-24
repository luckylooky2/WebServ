#ifndef CHUNKDECODER_HPP
#define CHUNKDECODER_HPP

#include "IHTTPBodyDecoder.hpp"
#include <stddef.h>
#include <string>

class ChunkDecoder : public IHTTPBodyDecoder {
public:
enum State
	{
		S_NOT_STARTED = 0,
		S_SIZE,
		S_CHUNK,
		S_CHUNK_END,
		S_CHUNK_END2,
		S_OVER
	};

private:
	bool _isAllocated;
	State _state;

private:
	ChunkDecoder();
	ChunkDecoder(const ChunkDecoder &other);

	ChunkDecoder&
	operator=(const ChunkDecoder &other);

public:
	ChunkDecoder(bool isAllocated);

	virtual
	~ChunkDecoder();

	bool
	consume(const std::string &in, std::string &out, size_t &consumed, bool max);

	void
	cleanup();

	ChunkDecoder::State
	state();

	static inline bool 
	isValidCharacter(char c)
	{
		return (std::isalnum(c));
	}

private:
	int _sizeNb;
	std::string _sizeStr;
	std::string _parsedChunk;
	long long _totalSize;
};

#endif
