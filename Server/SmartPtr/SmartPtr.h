#pragma once
//引用计数类
class RefPtr
{
public:
	RefPtr(int c=0);
	~RefPtr();
	//增加引用计数，并返回计数值
	int addref();
	//减少引用计数，并返回计数值
	int release();
private:
	//计数变量
	int use_count;
};

//智能指针
template <class T>
class SmartPtr
{
private:
	T* p;
	RefPtr* u;
public:
	//构造指针，并将引用计数置1
	explicit SmartPtr(T* ptr);
	//构造空指针
	explicit SmartPtr();
	//智能指针析构
	~SmartPtr();
	//智能指针的拷贝构造函数
	SmartPtr(const SmartPtr<T>& t);
	//指针赋值
	void operator = (SmartPtr<T>& t);
	// 得到原指针.
	T* get() const
	{ 
		return p; 
	}

	void reset(T* ptr);

	void reset(SmartPtr<T>& t);

	//重载->操作
	T* operator -> (void) 
	{ 
		return p; 
	}
	//重载*操作符
	T& operator * (void) 
	{ 
		return *p; 
	}
	//重载！操作符
	bool operator ! (void)
	{ 
		return !p; 
	}
	// 重载指针bool值操作符
	typedef SmartPtr<T> this_type;
	typedef T * this_type::*unspecified_bool_type;
	operator unspecified_bool_type() const
	{ 
		return !p ? 0: &this_type::p; 
	}
};

// 重载==操作符.
template<class T, class U> 
inline bool operator==(SmartPtr<T> & a, SmartPtr<U> & b)
{
	return a.get() == b.get();
}

// 重载!=操作符.
template<class T, class U> 
inline bool operator!=(SmartPtr<T> & a, SmartPtr<U> & b)
{
	return a.get() != b.get();
}