
#ifndef CONTAINER_H
#define CONTAINER_H

#include "core/Types.h"
#include "core/Defines.h"
#include "core/Allocators.h"

#define D_CONTAINER_DEFAULT_SIZE                  16


/**
 * This object is a vector that can contain pointers.
 */
class Container 
{
	public:
		Container(uint32_t size = D_CONTAINER_DEFAULT_SIZE,bool reg=true);
		virtual ~Container();

		/**
		 *               Add a pointer into Container
		 *               NOTE : why not const void*, because
		 *               when we get back we don't know if it's
		 *               const or not.
		 * @param _ptr pointer
		 */
		void add(void* _ptr);

		/**
		 *               Replace a pointer into Container
		 * @param index index in Container
		 * @param _ptr pointer
		 * @return old pointer value
		 */
		void* set(uint32_t index,void*_ptr);

		/**
		 *               Remove a pointer from Container
		 * @param index index in Container
		 * @return pointer at this index
		 */
		void* remove(uint32_t index);

		void* removePtr(void *ref);

		/**
		 *               Get a pointer from Container
		 * @param index index of Container
		 * @return pointer at this index
		 */
		void* get(uint32_t index) const;

		/**
		 *               Size of Container
		 * @return
		 */
		uint32_t size() const;

		/**
		 *               Clear Container
		 */
		void clear();


		/**
		 *               If the Container contains char*
		 *               it will free it automatically.
		 *               Call with caution !!!
		 */
		void flushMallocedContent();


	private:

		bool check_size();
		void rebuild(uint32_t index);

	private:
		friend class Map;
		void       **m_data;
		uint32_t     m_size_data;
		uint32_t     m_alloc_size;



};
#endif
