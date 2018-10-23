
#include "Parcel.h"

#define VERBOSE_TAG "Parcel"
#include "Verbose.h"


#define INC_COUNTER(x) \
do \
{ \
	m_curPosition += x; \
	if (m_curLength < m_curPosition) \
	{ \
		m_curLength   += x; \
	} \
}while(0)


Parcel::Parcel()
{
	m_data        = (uint8_t*)malloc(32);
	m_dataLength  = 32;
	m_curPosition = 0;
	m_curLength   = 0;

	memset(m_data, 0, 32);
}


Parcel::Parcel(const Parcel & p)
{
	m_data        = NULL;
	m_dataLength  = 0;
	m_curPosition = 0;
	m_curLength   = 0;

	this->setData(p.getData(),p.getSize());
	m_curPosition = p.m_curPosition;
}



Parcel::~Parcel()
{
	free(m_data);
}

uint8_t Parcel::readByte() const
{
	if (m_curPosition < m_curLength)
	{
		uint8_t result = m_data[m_curPosition];
		m_curPosition += sizeof(uint8_t);
		return result;
	}
	return 0;
}

void Parcel::writeByte(uint8_t i)
{
	growData(sizeof(uint8_t));
	m_data[m_curPosition] = i;
	INC_COUNTER(sizeof(uint8_t));
}

uint16_t Parcel::readShort() const
{
	if (m_curPosition < m_curLength)
	{
		void* result = m_data+m_curPosition;
		m_curPosition += sizeof(uint16_t);
		return *reinterpret_cast<uint16_t*>(result);
	}
	return 0;

}

void Parcel::writeShort(uint16_t i)
{
	growData(sizeof(uint16_t));
	*reinterpret_cast<uint16_t*>(m_data+m_curPosition) = i;
	INC_COUNTER(sizeof(uint16_t));
}

uint32_t Parcel::readInt32() const
{
	if (m_curPosition < m_curLength)
	{
		void* result = m_data+m_curPosition;
		m_curPosition += sizeof(uint32_t);
		return *reinterpret_cast<uint32_t*>(result);
	}
	return 0;
}

void Parcel::writeInt32(uint32_t i)
{
	growData(sizeof(uint32_t));
	*reinterpret_cast<uint32_t*>(m_data+m_curPosition) = i;
	INC_COUNTER(sizeof(uint32_t));
}

uint64_t Parcel::readInt64() const
{
	if (m_curPosition < m_curLength)
	{
		void* result = m_data+m_curPosition;
		m_curPosition += sizeof(uint64_t);
		return *reinterpret_cast<uint64_t*>(result);
	}
	return 0;
}

void Parcel::writeInt64(uint64_t i)
{
	growData(sizeof(uint64_t));
	*reinterpret_cast<uint64_t*>(m_data+m_curPosition) = i;
	INC_COUNTER(sizeof(uint64_t));
}



float Parcel::readFloat() const
{
	if (m_curPosition < m_curLength)
	{
		void* result = m_data+m_curPosition;
		m_curPosition += sizeof(float);
		return *reinterpret_cast<float*>(result);
	}
	return 0;
}

void Parcel::writeFloat(float f)
{
	growData(sizeof(float));
	*reinterpret_cast<float*>(m_data+m_curPosition) = f;
	INC_COUNTER(sizeof(float));
}

double Parcel::readDouble() const
{
	if (m_curPosition < m_curLength)
	{
		void* result = m_data+m_curPosition;
		m_curPosition += sizeof(double);
		return *reinterpret_cast<double*>(result);
	}
	return 0;
}

void Parcel::writeDouble(double d)
{
	growData(sizeof(double));
	*reinterpret_cast<double*>(m_data+m_curPosition) = d;
	INC_COUNTER(sizeof(double));
}

const char * Parcel::readString() const
{
	if (m_curPosition < m_curLength)
	{
		char* result =(char*)(m_data+m_curPosition);
		m_curPosition += strlen(result)+1;
		return result;
	}
	return NULL;
}

void Parcel::writeString(const char * s)
{
	growData(strlen(s)+1); // Trailling 0
	strcpy((char*)(m_data+m_curPosition),s);
	INC_COUNTER(strlen(s)+1);
}

void Parcel::read(void * outBuffer, uint32_t &len) const
{
	if (!outBuffer)
	{
		len = 0;
		return;
	}

	len = readInt32();
	if (m_curPosition < m_curLength)
	{
		uint8_t *start =m_data+m_curPosition;
		memcpy(outBuffer,start,len);
		m_curPosition += len;
	}

}

void Parcel::write(const void * buffer, uint32_t len)
{
	writeInt32(len);
	growData(len);
	memcpy((m_data+m_curPosition),buffer,len);
	INC_COUNTER(len);
}

const uint8_t * Parcel::getData() const
{
	return m_data;
}

uint32_t Parcel::getSize() const
{
	return m_curLength;
}

void Parcel::setData(const uint8_t * data, uint32_t size)
{
	free(m_data);
	if (size > 0)
	{
		m_data = (uint8_t*)malloc(size);
		memcpy(m_data,data,size);
		m_dataLength = size;
	}else
	{
		m_data = (uint8_t*)malloc(32);
		memset(m_data,0,32);
		m_dataLength = 32;
	}

	
	m_curLength = size;

	m_curPosition = 0;
}

void Parcel::growData(uint32_t len)
{
	if ((m_curPosition+len) < m_dataLength)
		return;

	uint32_t newSize = m_dataLength + len;

	uint8_t *newBuffer = (uint8_t*)malloc(newSize);

	memcpy(newBuffer,m_data, m_dataLength);

	free(m_data);

	m_data = newBuffer;
	m_dataLength = newSize;
}


void Parcel::readRaw(void * outBuffer, uint32_t len) const
{
	if (!outBuffer)
	{
		len = 0;
		return;
	}

	if (m_curPosition < m_curLength)
	{
		uint8_t *start =m_data+m_curPosition;
		/*
		if (m_curPosition + len >= m_curLength)
		{
			WARN("Try to read out of buffer ! Data will be truncated.\n");
			len = m_curLength;
		}*/

		memcpy(outBuffer,start,len);
		m_curPosition += len;
	}
}

void Parcel::writeRaw(const void * buffer, uint32_t len)
{
	growData(len);
	memcpy((m_data+m_curPosition),buffer,len);
	INC_COUNTER(len);
}

void Parcel::rewind() const
{
	m_curPosition = 0;
}


void Parcel::serialize(Parcel & p) const
{
	p.writeInt32(m_curLength);
	if (m_curLength>0)
	{
		p.writeRaw(m_data,m_curLength);
	}
}

void Parcel::deserialize(Parcel & p)
{
	uint32_t size = p.readInt32();
	uint8_t* data = NULL;
	if (size > 0)
	{
		data = (uint8_t*)malloc(size);
		p.readRaw(data,size);
		setData(data,size);
		free(data);
		rewind();
	}else
	{
		clear();
	}
}

void Parcel::clear()
{
	m_curPosition = 0;
	m_curLength   = 0;
	memset(m_data, 0, m_dataLength);
}


const uint8_t* Parcel::dataAtCurrentPosition() const
{
	return (m_data+m_curPosition);
}

uint32_t Parcel::getRemainingDataSize() const
{
	return m_curLength-m_curPosition;
}

void Parcel::forward(uint32_t nbBytes) const
{
	if (m_curPosition+nbBytes <= m_curLength)
	{
		m_curPosition+=nbBytes;
	}
}







