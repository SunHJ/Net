#pragma once
//���ü�����
class RefPtr
{
public:
	RefPtr(int c=0);
	~RefPtr();
	//�������ü����������ؼ���ֵ
	int addref();
	//�������ü����������ؼ���ֵ
	int release();
private:
	//��������
	int use_count;
};

//����ָ��
template <class T>
class SmartPtr
{
private:
	T* p;
	RefPtr* u;
public:
	//����ָ�룬�������ü�����1
	explicit SmartPtr(T* ptr);
	//�����ָ��
	explicit SmartPtr();
	//����ָ������
	~SmartPtr();
	//����ָ��Ŀ������캯��
	SmartPtr(const SmartPtr<T>& t);
	//ָ�븳ֵ
	void operator = (SmartPtr<T>& t);
	// �õ�ԭָ��.
	T* get() const
	{ 
		return p; 
	}

	void reset(T* ptr);

	void reset(SmartPtr<T>& t);

	//����->����
	T* operator -> (void) 
	{ 
		return p; 
	}
	//����*������
	T& operator * (void) 
	{ 
		return *p; 
	}
	//���أ�������
	bool operator ! (void)
	{ 
		return !p; 
	}
	// ����ָ��boolֵ������
	typedef SmartPtr<T> this_type;
	typedef T * this_type::*unspecified_bool_type;
	operator unspecified_bool_type() const
	{ 
		return !p ? 0: &this_type::p; 
	}
};

// ����==������.
template<class T, class U> 
inline bool operator==(SmartPtr<T> & a, SmartPtr<U> & b)
{
	return a.get() == b.get();
}

// ����!=������.
template<class T, class U> 
inline bool operator!=(SmartPtr<T> & a, SmartPtr<U> & b)
{
	return a.get() != b.get();
}