#pragma once
struct Vector3 final{
	float x;
	float y;
	float z;
};
class mt2
{
private:
	Vector3 num_;

public:
	mt2(Vector3 num = {}) {
		num_.x = num.x;
		num_.y = num.y;
		num_.z = num.z;
	}

	mt2 operator+(Vector3 obj) {
		Vector3 result;
		result.x = obj.x + num_.x;
		result.y = obj.y + num_.y;
		result.z = obj.z + num_.z;

		return result;
	}

	mt2 operator-(Vector3 obj) {
		Vector3 result;
		result.x = obj.x - num_.x;
		result.y = obj.y - num_.y;
		result.z = obj.z - num_.z;

		return result;
	}

	mt2 operator*(Vector3 obj) {
		Vector3 result;
		result.x = obj.x * num_.x;
		result.y = obj.y * num_.y;
		result.z = obj.z * num_.z;

		return result;
	}

};

