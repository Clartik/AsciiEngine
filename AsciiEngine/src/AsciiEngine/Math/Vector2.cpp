#include "vector2.h"

namespace AsciiEngine
{
	const Vector2& Vector2::UP = Vector2(0, -1);
	const Vector2& Vector2::DOWN = Vector2(0, 1);
	const Vector2& Vector2::LEFT = Vector2(-1, 0);
	const Vector2& Vector2::RIGHT = Vector2(1, 0);

	Vector2::Vector2()
		: x(0), y(0)
	{
	}

	Vector2::Vector2(const int& x, const int& y)
		: x(x), y(y)
	{
	}

	Vector2 Vector2::Add(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 Vector2::Subtract(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Subtract(other);
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2& Vector2::Set(const Vector2& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const Vector2& other)
	{
		return Set(other);
	}

	Vector2& Vector2::operator++()
	{
		x++;
		y++;
		return *this;
	}

	Vector2& Vector2::operator++(int)
	{
		Vector2* temp = this;
		++*this;
		return *temp;
	}

	Vector2& Vector2::operator--()
	{
		x--;
		y--;
		return *this;
	}

	Vector2& Vector2::operator--(int)
	{
		Vector2* temp = this;
		--*this;
		return *temp;
	}

	bool Vector2::IsEqual(const Vector2& other) const
	{
		if (x != other.x)
			return false;

		if (y != other.y)
			return false;

		return true;
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return IsEqual(other);
	}

	bool Vector2::operator!=(const Vector2& other) const
	{
		return !IsEqual(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2& vector2)
	{
		stream << vector2.x << ", " << vector2.y;
		return stream;
	}
}