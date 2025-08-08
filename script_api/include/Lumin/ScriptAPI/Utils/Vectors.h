/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <iostream>

#pragma region Vector2

	class Vector2
	{
	public:
		Vector2() { x = 0; y = 0; }
		Vector2(double X, double Y) { x = X; y = Y; }

		Vector2 operator + (const Vector2& vector) const
		{
			return Vector2(x + vector.x, y + vector.y);
		}

		Vector2 operator - (const Vector2& vector) const
		{
			return Vector2(x - vector.x, y - vector.y);
		}

		Vector2 operator * (const Vector2& vector) const
		{
			return Vector2(x * vector.x, y * vector.y);
		}

		Vector2 operator / (const Vector2& vector) const
		{
			return Vector2(x / vector.x, y / vector.y);
		}

		bool operator == (const Vector2& vector) const
		{
			if (x == vector.x && y == vector.y)
				return true;
			else
				return false;
		}
		bool operator != (const Vector2& vector) const
		{
			if (x != vector.x && y != vector.y)
				return true;
			else
				return false;
		}
		bool operator > (const Vector2& vector) const
		{
			if (x > vector.x && y > vector.y)
				return true;
			else
				return false;
		}
		bool operator < (const Vector2& vector) const
		{
			if (x < vector.x && y < vector.y)
				return true;
			else
				return false;
		}

		Vector2& operator += (const Vector2& vector)
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}

		Vector2& operator -= (const Vector2& vector)
		{
			x -= vector.x;
			y -= vector.y;
			return *this;
		}

		Vector2& operator *= (const Vector2& vector)
		{
			x *= vector.x;
			y *= vector.y;
			return *this;
		}

		Vector2& operator /= (const Vector2& vector)
		{
			x /= vector.x;
			y /= vector.y;
			return *this;
		}

		Vector2 operator - () const
		{
			return Vector2(-x, -y);
		}

		Vector2& operator++ ()
		{
			x += 1;
			y += 1;
			return *this;
		}
		Vector2& operator-- ()
		{
			x -= 1;
			y -= 1;
			return *this;
		}

		double x = 0, y = 0;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		stream << "(" << vector.x << ", " << vector.y << ")";
		return stream;
	}
#pragma endregion

#pragma region Vector3

	class Vector3
	{
	public:
		Vector3() { x = 0; y = 0; z = 0; }
		Vector3(double X, double Y, double Z) { x = X; y = Y; z = Z; }

		Vector3 operator + (const Vector3& vector) const
		{
			return Vector3(x + vector.x, y + vector.y, z + vector.z);
		}

		Vector3 operator - (const Vector3& vector) const
		{
			return Vector3(x - vector.x, y - vector.y, z - vector.z);
		}

		Vector3 operator * (const Vector3& vector) const
		{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}

		Vector3 operator / (const Vector3& vector) const
		{
			return Vector3(x / vector.x, y / vector.y, z / vector.z);
		}

		bool operator == (const Vector3& vector) const
		{
			if (x == vector.x && y == vector.y && z == vector.z)
				return true;
			else
				return false;
		}
		bool operator != (const Vector3& vector) const
		{
			if (x != vector.x && y != vector.y && z != vector.z)
				return true;
			else
				return false;
		}
		bool operator > (const Vector3& vector) const
		{
			if (x > vector.x && y > vector.y && z > vector.z)
				return true;
			else
				return false;
		}
		bool operator < (const Vector3& vector) const
		{
			if (x < vector.x && y < vector.y && z < vector.z)
				return true;
			else
				return false;
		}

		Vector3& operator += (const Vector3& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		Vector3& operator -= (const Vector3& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}

		Vector3& operator *= (const Vector3& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
			return *this;
		}

		Vector3& operator /= (const Vector3& vector)
		{
			x /= vector.x;
			y /= vector.y;
			z /= vector.z;
			return *this;
		}

		Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		//Postfix
		Vector3& operator++ ()
		{
			x += 1;
			y += 1;
			z += 1;
			return *this;
		}
		Vector3& operator-- ()
		{
			x -= 1;
			y -= 1;
			z -= 1;
			return *this;
		}

		double x = 0, y = 0, z = 0;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
	{
		stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}
#pragma endregion

#pragma region Vector4

	class Vector4
	{
	public:
		Vector4() { x = 0; y = 0; z = 0; w = 0; }
		Vector4(double X, double Y, double Z, double W) { x = X; y = Y; z = Z; w = W; }

		Vector4 operator + (const Vector4& vector) const
		{
			return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
		}

		Vector4 operator - (const Vector4& vector) const
		{
			return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
		}

		Vector4 operator * (const Vector4& vector) const
		{
			return Vector4(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
		}

		Vector4 operator / (const Vector4& vector) const
		{
			return Vector4(x / vector.x, y / vector.y, z / vector.z, w / vector.w);
		}

		bool operator == (const Vector4& vector) const
		{
			if (x == vector.x && y == vector.y && z == vector.z && w == vector.w)
				return true;
			else
				return false;
		}
		bool operator != (const Vector4& vector) const
		{
			if (x != vector.x && y != vector.y && z != vector.z && w != vector.w)
				return true;
			else
				return false;
		}
		bool operator > (const Vector4& vector) const
		{
			if (x > vector.x && y > vector.y && z > vector.z && w > vector.w)
				return true;
			else
				return false;
		}
		bool operator < (const Vector4& vector) const
		{
			if (x < vector.x && y < vector.y && z < vector.z && w < vector.w)
				return true;
			else
				return false;
		}

		Vector4& operator += (const Vector4& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			w += vector.w;
			return *this;
		}

		Vector4& operator -= (const Vector4& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			w -= vector.w;
			return *this;
		}

		Vector4& operator *= (const Vector4& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
			w *= vector.w;
			return *this;
		}

		Vector4& operator /= (const Vector4& vector)
		{
			x /= vector.x;
			y /= vector.y;
			z /= vector.z;
			w /= vector.w;
			return *this;
		}

		Vector4 operator - () const
		{
			return Vector4(-x, -y, -z, -w);
		}

		Vector4& operator++ ()
		{
			x += 1;
			y += 1;
			z += 1;
			w += 1;
			return *this;
		}
		Vector4& operator-- ()
		{
			x -= 1;
			y -= 1;
			z -= 1;
			w -= 1;
			return *this;
		}

		double x = 0, y = 0, z = 0, w = 0;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
	{
		stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}
#pragma endregion