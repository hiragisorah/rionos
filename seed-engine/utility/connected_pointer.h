#pragma once

template<class _Type> class ConnectedPointer
{
public:
	ConnectedPointer(void)
		: pointer_(new _Type)
	{
		this->ppointer_ = &pointer_;
	}
	ConnectedPointer(unsigned int)
		: pointer_(nullptr)
		, ppointer_(nullptr)
	{
	}
	ConnectedPointer(const ConnectedPointer & connected_pointer)
		: pointer_(nullptr)
		, ppointer_(connected_pointer.ppointer_)
	{}
	virtual ~ConnectedPointer(void)
	{
		this->Release();
	}

private:
	_Type * pointer_;
	_Type ** ppointer_;

public:
	const bool isExpired(void) { return *this->ppointer_ == nullptr; }
	void Release(void)
	{
		if (!this->isExpired())
		{
			delete *this->ppointer_;
			*this->ppointer_ = nullptr;
		}
	}
	template<class _NewType> void Reset(void)
	{
		this->pointer_ = new _NewType;
		this->ppointer_ = &this->pointer_;
	};

public:
	_Type * const operator->(void) { return *this->ppointer_; }
};