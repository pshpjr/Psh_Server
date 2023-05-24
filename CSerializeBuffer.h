#pragma once

class CSerializeBuffer
{
	enum bufferOption { BUFFER_SIZE = 1400 };


public:
	CSerializeBuffer() : _buffer(new char[BUFFER_SIZE]), _front(_buffer), _rear(_buffer) { }
	CSerializeBuffer(char* buffer) : _buffer(buffer), _front(_buffer), _rear(_buffer) {  }

	~CSerializeBuffer() { delete _buffer; }

	void Clear()
	{
		_front = _buffer;
		_rear = _buffer;
	}

	int getBufferSize() { return  _bufferSize; }
	int		GetDataSize(void) { return _dataSize; }

	char* GetBufferPtr(void) { return _buffer; }
	void		MoveWritePos(int size) { _rear += size; _dataSize += size; }
	void		MoveReadPos(int size) { _front += size; _dataSize -= size; }

public:
	CSerializeBuffer& operator <<(unsigned char value);
	CSerializeBuffer& operator <<(char value);

	CSerializeBuffer& operator <<(unsigned short value);
	CSerializeBuffer& operator <<(short value);

	CSerializeBuffer& operator <<(unsigned int value);
	inline CSerializeBuffer& operator <<(int value)
	{
		*(int*)_rear = value;
		_rear += sizeof(unsigned int);
		_dataSize += sizeof(int);
		return *this;
	}

	CSerializeBuffer& operator <<(unsigned long value);
	CSerializeBuffer& operator <<(long value);

	CSerializeBuffer& operator <<(unsigned long long value);
	CSerializeBuffer& operator <<(long long value);

	CSerializeBuffer& operator <<(float value);
	CSerializeBuffer& operator <<(double value);



	CSerializeBuffer& operator >>(unsigned char& value);
	CSerializeBuffer& operator >>(char& value);

	CSerializeBuffer& operator >>(unsigned short& value);
	CSerializeBuffer& operator >>(short& value);

	CSerializeBuffer& operator >>(unsigned int& value);
	CSerializeBuffer& operator >>(int& value);

	CSerializeBuffer& operator >>(unsigned long& value);
	CSerializeBuffer& operator >>(long& value);

	CSerializeBuffer& operator >>(unsigned long long& value);
	CSerializeBuffer& operator >>(long long& value);

	CSerializeBuffer& operator >>(float& value);
	CSerializeBuffer& operator >>(double& value);
private:

	void _resize();


	char* _buffer = nullptr;
	char* _front = nullptr;
	char* _rear = nullptr;
	int _dataSize = 0;
	int _bufferSize = BUFFER_SIZE;


};
