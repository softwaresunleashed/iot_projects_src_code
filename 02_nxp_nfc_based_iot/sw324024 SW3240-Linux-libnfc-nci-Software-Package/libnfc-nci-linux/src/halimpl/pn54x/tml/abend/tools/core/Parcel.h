#ifndef Parcel_H
#define Parcel_H

#include "core/Types.h"
#include "core/Defines.h"
#include "core/Allocators.h"


/**
 * This class allows to serialize data.
 * FIXME : Endianess not supported !
**/
class Parcel
{
	public:
		Parcel();
		Parcel(const Parcel &p);
		virtual ~Parcel();

		uint8_t readByte() const;
		void writeByte(uint8_t i);

		uint16_t readShort() const;
		void writeShort(uint16_t i);

		uint32_t readInt32() const;
		void writeInt32(uint32_t i);

		uint64_t readInt64() const;
		void writeInt64(uint64_t i);

		float readFloat() const;
		void writeFloat(float f);

		double readDouble() const;
		void writeDouble(double d);

		const char* readString() const;
		void writeString(const char* s);

		/**
		 *               Read a buffer. The size of buffer is serialized.
		 * @param outBuffer This buffer should be allocated by caller.
		 * @param len size of buffer
		 */
		void read(void* outBuffer, uint32_t &len) const;
		/**
		 *               Write a buffer. The size of buffer is serialized.
		 * @param buffer Buffer to write
		 * @param len size of buffer
		 */
		void write(const void* buffer, uint32_t len);

		/**
		 *               Read a buffer. The size is not serialized.
		 * @param outBuffer This buffer should be allocated by caller.
		 * @param len size of buffer
		 */
		void readRaw(void* outBuffer, uint32_t len) const;
		/**
		 *               Write a buffer. The size is not serialized.
		 * @param buffer Buffer to write
		 * @param len size of buffer
		 */
		void writeRaw(const void* buffer, uint32_t len);

		/**
		 *               Return a pointer of the data at the current
		 *               position.
		 *               Pointer remains valid while Parcel is not modified.
		 */
		const uint8_t* dataAtCurrentPosition() const;
		
		/**
		 *               Return remaining data length at ccurrent position.
		 * @return size in byte
		 */
		uint32_t getRemainingDataSize() const;
		
		/**
		 *               Return a reference of serialized buffer.
		 * @return Reference. Ownership is not transfered.
		 */
		const uint8_t *getData() const;
		/**
		 *               Return the size of serialized buffer.
		 * @return size in byte.
		 */
		uint32_t       getSize() const;

		/**
		 *               Set the new content of Parcel.
		 * @param data A serialized buffer.
		 * @param size size of buffer.
		 */
		void setData(const uint8_t* data,uint32_t size);

		/**
		 *               Rewind the Parcel at begining.
		 */
		void rewind() const;

		/**
		 *               Skip bytes in Parcel. Same behavior
		 *               as readByte() called X time.
		 *               NOTE : if end of Parcel is reached. This
		 *               function has no effect.
		 * @param nbBytes Number of bytes to skip.
		 */
		void forward(uint32_t nbBytes) const;
		
		/**
		 *               Empty the Parcel.
		 */
		void clear();

		virtual void serialize(Parcel &p)const ;
		virtual void deserialize(Parcel &p);


	private:
		void growData(uint32_t len);

	private:
		uint8_t          *m_data;
		uint32_t          m_dataLength;
		uint32_t          m_curLength;
		mutable uint32_t  m_curPosition;

};


#endif // ndef Parcel_H


