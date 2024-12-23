#pragma once

#include <iostream>

namespace AsciiEngine
{
	class Vector2
	{
	public:
		static const Vector2& UP;
		static const Vector2& DOWN;
		static const Vector2& LEFT;
		static const Vector2& RIGHT;
	public:
		int x, y;
	public:
		Vector2();
		Vector2(const int& x, const int& y);
		Vector2 Add(const Vector2& other) const;
		Vector2 Subtract(const Vector2& other) const;

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;

		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);

		Vector2& Set(const Vector2& other);

		Vector2& operator=(const Vector2& other);

		// Pre Increment
		Vector2& operator++();
		// Post Increment
		Vector2& operator++(int);

		// Pre Increment
		Vector2& operator--();
		// Post Increment
		Vector2& operator--(int);

		bool IsEqual(const Vector2& other) const;

		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector2);
	};
}