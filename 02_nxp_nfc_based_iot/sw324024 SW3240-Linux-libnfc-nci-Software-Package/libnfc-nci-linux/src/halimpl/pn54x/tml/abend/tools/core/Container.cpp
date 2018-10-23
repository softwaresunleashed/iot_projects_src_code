
#include "Container.h"

#include <string.h>


Container::Container(uint32_t size,bool reg)
{
	m_data=(void**)malloc(size*sizeof(void*));
	memset(m_data,0,size*sizeof(void*));
	m_size_data=0;
	m_alloc_size=size;
}

Container::~Container()
{
	free(m_data);
}


void Container::add(void* _ptr)
{
	check_size();
	m_data[m_size_data]=_ptr;
	m_size_data++;
}


void* Container::set(uint32_t index,void*_ptr)
{
	if (index>m_size_data)
	{
		add(_ptr);
		return NULL;
	}

	void* _old=m_data[index];
	m_data[index]=_ptr;

	return _old;
}
void* Container::remove(uint32_t index)
{
	if (index<m_size_data)
	{
		void* _old=m_data[index];
		m_data[index]=NULL;
		if (index==m_size_data-1)
		{
			// We delete the last one
			m_size_data--;
			return _old;
		}
		rebuild(index);
		m_size_data--;
		return _old;
	}
	return NULL;
}

void* Container::get(uint32_t index) const
{
	if (index<m_size_data)
	{
		return m_data[index];
	}
	return NULL;
}

uint32_t Container::size() const
{
	return m_size_data;
}

bool Container::check_size()
{
	if (m_size_data==m_alloc_size)
	{
		m_alloc_size=m_alloc_size*2;

		void** m_new_data=(void**)malloc(sizeof(void*)*m_alloc_size);
		memmove(m_new_data,m_data,m_size_data*sizeof(void*));
		free(m_data);
		m_data=m_new_data;
	}
	return true;
}

void Container::rebuild(uint32_t index)
{
	void** _zero=m_data+index;
	void** _start_cpy=_zero+1;
	int32_t size=(m_size_data-1)-index;
	if (size <= 0) return;
	memmove(_zero,_start_cpy,size*sizeof(void*));
}

void Container::clear()
{
	memset(m_data,0,m_size_data);
	m_size_data = 0;
}


void Container::flushMallocedContent()
{
	void *old = NULL;
	uint32_t sz = size();
	for (uint32_t i = 0 ; i < sz;i++)
	{
		old = get(i);
		free(old);
	}
	clear();
}

void* Container::removePtr(void* ref)
{
	void *scan = NULL;
	uint32_t sz = size();
	for (uint32_t i = 0; i < sz;i++)
	{
		scan = get(i);
		if (scan == ref)
		{
			return remove(i);
		}
	}
	return NULL;
}



