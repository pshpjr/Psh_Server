#include "CSerializeBuffer.h"

#include <cstring>

CSerializeBuffer& CSerializeBuffer::operator<<(unsigned char value)
{
	*(unsigned char*)_rear = value;
	_rear += sizeof(unsigned char);
	_dataSize += sizeof(unsigned char);

	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(char value)
{
	*(_rear) = value;
	_rear += sizeof(char);
	_dataSize += sizeof(char);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(unsigned short value)
{
	*(unsigned short*)_rear = value;
	_rear += sizeof(unsigned short);
	_dataSize += sizeof(unsigned short);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(short value)
{
	*(short*)(_rear) = value;
	_rear += sizeof(unsigned short);
	_dataSize += sizeof(short);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(unsigned int value)
{
	*(unsigned int*)(_rear) = value;
	_rear += sizeof(unsigned int);
	_dataSize += sizeof(unsigned int);
	return *this;
}



CSerializeBuffer& CSerializeBuffer::operator<<(unsigned long value)
{
	*(unsigned long*)(_rear) = value;
	_rear += sizeof(unsigned long);
	_dataSize += sizeof(unsigned long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(long value)
{
	*(long*)(_rear) = value;
	_rear += sizeof(long);
	_dataSize += sizeof(long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(unsigned long long value)
{
	*(unsigned long long*)(_rear) = value;
	_rear += sizeof(unsigned long long);
	_dataSize += sizeof(unsigned long long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(long long value)
{
	*(long long*)(_rear) = value;
	_rear += sizeof(long long);
	_dataSize += sizeof(long long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(float value)
{
	*(float*)(_rear) = value;
	_rear += sizeof(float);
	_dataSize += sizeof(float);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator<<(double value)
{
	*(double*)(_rear) = value;
	_rear += sizeof(double);
	_dataSize += sizeof(double);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(unsigned char& value)
{
	value = *(unsigned char*)(_front);
	_front += sizeof(unsigned char);
	_dataSize -= sizeof(unsigned char);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(char& value)
{
	value = *(char*)(_front);
	_front += sizeof(unsigned char);
	_dataSize -= sizeof(char);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(unsigned short& value)
{
	value = *(unsigned short*)(_front);
	_front += sizeof(unsigned short);
	_dataSize -= sizeof(unsigned short);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(short& value)
{
	value = *(short*)(_front);
	_front += sizeof(short);
	_dataSize -= sizeof(short);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(unsigned int& value)
{
	value = *(unsigned int*)(_front);
	_front += sizeof(unsigned int);
	_dataSize -= sizeof(unsigned int);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(int& value)
{
	value = *(int*)(_front);
	_front += sizeof(int);
	_dataSize -= sizeof(int);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(unsigned long& value)
{
	value = *(unsigned long*)(_front);
	_front += sizeof(unsigned long);
	_dataSize -= sizeof(unsigned long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(long& value)
{
	value = *(long*)(_front);
	_front += sizeof(long);
	_dataSize -= sizeof(long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(unsigned long long& value)
{
	value = *(unsigned long long*)(_front);
	_front += sizeof(unsigned long long);
	_dataSize -= sizeof(unsigned long long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(long long& value)
{
	value = *(long long*)(_front);
	_front += sizeof(long long);
	_dataSize -= sizeof(long long);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(float& value)
{
	value = *(float*)(_front);
	_front += sizeof(float);
	_dataSize -= sizeof(float);
	return *this;
}

CSerializeBuffer& CSerializeBuffer::operator>>(double& value)
{
	value = *(double*)(_front);
	_front += sizeof(double);
	_dataSize -= sizeof(double);
	return *this;
}

