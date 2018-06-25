#pragma once

class GRAPHICSDLL_API Geometry2D
{
public:
	enum class TYPE
	{
		TRIANGLE,
		QUAD,
		CIRCLE
	};

public:
	const TYPE & get_type(void) const { return this->type_; };
	void set_type(const TYPE & type) { this->type_ = type; }

private:
	TYPE type_;
};