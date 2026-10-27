#pragma once

#include <cmath>

namespace math {

struct Vector3 {
	float x, y, z;

	Vector3 operator-(const Vector3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	static Vector3 cross(const Vector3& a, const Vector3& b) {
		return {
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x,
		};
	}

	static Vector3 normalize(const Vector3& v) {
		const float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		return { v.x / length, v.y / length, v.z / length };
	}
};

struct Matrix4 {
	float elements[4][4];

	static Matrix4 fromRows(const float (&rows)[4][4]) {
		Matrix4 result;
		for (int row = 0; row < 4; ++row) {
			for (int column = 0; column < 4; ++column) {
				result.elements[column][row] = rows[row][column];
			}
		}
		return result;
	}

	static Matrix4 identity() {
		return fromRows({
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 },
		});
	}

	static Matrix4 translation(float x, float y, float z) {
		return fromRows({
			{ 1, 0, 0, x },
			{ 0, 1, 0, y },
			{ 0, 0, 1, z },
			{ 0, 0, 0, 1 },
		});
	}

	static Matrix4 scale(float x, float y, float z) {
		return fromRows({
			{ x, 0, 0, 0 },
			{ 0, y, 0, 0 },
			{ 0, 0, z, 0 },
			{ 0, 0, 0, 1 },
		});
	}

	static Matrix4 rotationX(float angle) {
		const float c = std::cos(angle), s = std::sin(angle);
		return fromRows({
			{ 1, 0,  0, 0 },
			{ 0, c, -s, 0 },
			{ 0, s,  c, 0 },
			{ 0, 0,  0, 1 },
		});
	}

	static Matrix4 rotationY(float angle) {
		const float c = std::cos(angle), s = std::sin(angle);
		return fromRows({
			{  c, 0, s, 0 },
			{  0, 1, 0, 0 },
			{ -s, 0, c, 0 },
			{  0, 0, 0, 1 },
		});
	}

	static Matrix4 rotationZ(float angle) {
		const float c = std::cos(angle), s = std::sin(angle);
		return fromRows({
			{ c, -s, 0, 0 },
			{ s,  c, 0, 0 },
			{ 0,  0, 1, 0 },
			{ 0,  0, 0, 1 },
		});
	}

	static Matrix4 perspective(float fov, float aspect, float near, float far) {
		const float t = std::tan(fov / 2);
		return fromRows({
			{ 1 / (aspect * t), 0,     0,                   0                          },
			{ 0,                1 / t, 0,                   0                          },
			{ 0,                0,     far / (far - near), -far * near / (far - near) },
			{ 0,                0,     1,                   0                          },
		});
	}

	static Matrix4 orthographic(float height, float aspect, float near, float far) {
		const float width = height * aspect;
		return fromRows({
			{ 1 / width, 0,          0,                  0                    },
			{ 0,         1 / height, 0,                  0                    },
			{ 0,         0,          1 / (far - near),  -near / (far - near) },
			{ 0,         0,          0,                  1                    },
		});
	}

	Matrix4 operator*(const Matrix4& other) const {
		Matrix4 result;
		for (int row = 0; row < 4; ++row) {
			for (int column = 0; column < 4; ++column) {
				float sum = 0;
				for (int k = 0; k < 4; ++k) {
					sum += elements[k][row] * other.elements[column][k];
				}
				result.elements[column][row] = sum;
			}
		}
		return result;
	}
};

}
