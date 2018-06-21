#pragma once

template<class _Type> class ConnectedPointer
{
public:
	template<class ... Args>
	ConnectedPointer(Args ... args)
	{
		this->ppointer_ = new _Type*;
		*this->ppointer_ = new _Type(args ...);
	}
	ConnectedPointer(unsigned int)
		: ppointer_(nullptr)
	{
	}
	ConnectedPointer(const ConnectedPointer & connected_pointer)
		: ppointer_(connected_pointer.ppointer_)
	{}
	virtual ~ConnectedPointer(void)
	{
		this->Release();
	}

private:
	_Type ** ppointer_;

public:
	const bool isExpired(void) { return *this->ppointer_ == nullptr; }
	void Release(void)
	{
		if (!this->isExpired())
		{
			delete *this->ppointer_;
			delete this->ppointer_;
			*this->ppointer_ = nullptr;
		}
	}
	template<class _NewType> void Reset(void)
	{
		this->Release();
		this->ppointer_ = new _Type*;
		*this->ppointer_ = new _Type;
	};

public:
	_Type * const operator->(void) { return *this->ppointer_; }
	const _Type & operator*(void) { return **this->ppointer_; }
};