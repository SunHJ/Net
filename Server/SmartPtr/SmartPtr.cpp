#include "SmartPtr.h"

RefPtr::RefPtr(int c/* =0 */) : use_count(c)
{
	//
}

RefPtr::~RefPtr()
{
	//
}

int RefPtr::addref()
{
	return ++use_count;
}

int RefPtr::release()
{
	return --use_count;
}

template<class T>
SmartPtr<T>::SmartPtr(T* ptr) : p(ptr), u(::new RefPtr(1))
{
	//
}

template<class T>
SmartPtr<T>::SmartPtr() : p(NULL), u(NULL)
{
	//
}

template<class T>
SmartPtr<T>::~SmartPtr()
{
	if (p && u->release() <=0)
	{
		delete p;
		p = NULL;
		delete u;
		u = NULL;
	}
}

template<class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& t)
{
	p = t.p;
	u = t.u;

	if (u)
	{
		u->addref();
	}
}

template<class T>
void SmartPtr<T>::operator = (SmartPtr<T>& t)
{
	if (p && u->release() <=0)
	{
		delete p;
		p = NULL;
		delete u;
		u = NULL;
	}
	p = t.p;
	u = t.u;

	if (u)
	{
		u->addref();
	}
}

template<class T>
void SmartPtr<T>::reset(T* ptr)
{
	if (p && u->release() <=0)
	{
		delete p;
		p = NULL;
		delete u; 
		u = NULL;
	}

	p = ptr;
	if (p)
		u = new RefPtr(1);
	else
		u = NULL;
}

template<class T>
void SmartPtr<T>::reset(SmartPtr<T>& t)
{
	if (p && u->release() <=0)
	{
		delete p;
		p = NULL;
		delete u;
		u = NULL;
	}

	p = t.p;
	u = t.u;

	if (u)
	{
		u->addref();
	}
}