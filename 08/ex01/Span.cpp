#include <algorithm>
#include <exception>
#include "Span.hpp"

Span::Span()
{
}

Span::Span(size_t size)
	: mCapacity(size)
	, mSize(0)
{
	mVector.reserve(size);
}

Span::Span(const Span& copy)
	: mCapacity(copy.mCapacity)
	, mSize(copy.mSize)
{
	mVector.reserve(mCapacity);
	mVector = copy.mVector;
}

Span& Span::operator=(const Span& rhs)
{
	if (&rhs != this)
	{
		mCapacity = rhs.mCapacity;
		mSize = rhs.mSize;
		mVector.reserve(mCapacity);
		mVector = rhs.mVector;
	}
	return (*this);
}

Span::~Span()
{
}

void Span::addNumber(int num)
{
	if (mSize >= mCapacity)
	{
		throw std::out_of_range("Index out of range");
	}
	mVector.push_back(num);
	mSize++;
}

unsigned long Span::shortestSpan(void) const
{
	if (mSize < 2)
	{
		throw std::length_error("Size must be at least 2");
	}
	std::vector<int> sorted_vector = mVector;
	std::sort(sorted_vector.begin(), sorted_vector.end());
	unsigned long 	min = std::numeric_limits<int>::max() - std::numeric_limits<int>::min();
	unsigned long	span;
	for (size_t i = 1; i < mSize; ++i)
	{
		span = sorted_vector[i] - sorted_vector[i - 1];
		if (span == 0)
		{
			return (0);
		}
		else if (span < min)
		{
			min = span;
		}
	}
	return (min);
}

unsigned long Span::longestSpan(void) const
{
	if (mSize < 2)
	{
		throw std::length_error("Size must be at least 2");
	}
	int min = mVector[0];
	int max = mVector[0];
	for (size_t i = 1; i < mSize; ++i)
	{
		if (mVector[i] < min)
		{
			min = mVector[i];
		}
		if (mVector[i] > max)
		{
			max = mVector[i];
		}
	}
	return (static_cast<unsigned long>(max - min));
}