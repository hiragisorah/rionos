#pragma once

template<class _Type> class ConnectedPointer
{
public:
	ConnectedPointer(_Type * pointer = nullptr, bool auto_release = true)
		: auto_release_(auto_release)
	{
		this->ppointer_ = new _Type*;
		*this->ppointer_ = pointer;
	}
	virtual ~ConnectedPointer(void)
	{
		if(this->auto_release_)
			this->Release();
	}

private:
	_Type ** ppointer_;
	bool auto_release_;

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
		*this->ppointer_ = new _NewType;
	};

public:
	_Type * const operator->(void) { return *this->ppointer_; }
	_Type * const operator&(void) { return *this->ppointer_; }
	const _Type & operator*(void) { return **this->ppointer_; }
	const _Type & operator=(const _Type & a) { return **this->ppointer_ = a; }
};