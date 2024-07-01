﻿#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <assert.h>
#include <cmath>
#include "Vector3.h"
#include <imgui.h>


const int kWindowHeight = 720;
const int kWindowWidth = 1280;

struct Vector2 final {
	float x;
	float y;
};

struct Vector2i final {
	int x;
	int y;
};

struct Vertex final {
	float left;
	float right;
	float top;
	float bottom;
};

//直線
struct Line final {
	Vector3 origin; //始点
	Vector3 diff; //終点への差分ベクトル
};

//半直線
struct Ray final {
	Vector3 origin; //始点
	Vector3 diff; //終点への差分ベクトル
};

//線分
struct Segment final {
	Vector3 origin; //始点
	Vector3 diff; //終点への差分ベクトル
};

struct Plane {
	Vector3 normal; //法線
	float distance; //距離
};

struct ForCorners final {
	Vector2 topLeft;
	Vector2 topRight;
	Vector2 bottomLeft;
	Vector2 bottomRight;
};

struct Matrix2x2 final {
	float m[2][2];
};

struct Matrix3x3 final {
	float m[3][3];
};

struct Matrix4x4 final {
	float m[4][4];
};

struct Balls final {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float radius;
};

struct Box {
	Vector2 position;
	Vertex vertex;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceleratiion;
	float mass;
	unsigned int color;
};

struct Sphere {
	Vector3 center;
	float radius;
};
struct Triangle {
	Vector3 vertices[3]; //頂点
};

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

/// <summary>
/// 最短距離
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
inline float Length(Vector2 const& obj) {
	return sqrtf(obj.x * obj.x + obj.y * obj.y);
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
inline Vector2 Normalize(Vector2 const& obj) {
	float length = 0;
	Vector2 newObj = {};

	length = Length(obj);

	newObj.x = obj.x;
	newObj.y = obj.y;

	if (length != 0.0f) {
		newObj.x = obj.x / length;
		newObj.y = obj.y / length;
	}
	return newObj;
}

/// <summary>
/// 内積
/// </summary>
/// <param name="obj1"></param>
/// <param name="obj2"></param>
/// <returns></returns>
inline float DotProduct(Vector2 const& obj1, Vector2 const& obj2) {
	return obj1.x * obj2.x + obj1.y * obj2.y;
}

/// <summary>
/// 外積
/// </summary>
/// <param name="obj1"></param>
/// <param name="obj2"></param>
/// <returns></returns>
inline float CrossProduct(Vector2 const& obj1, Vector2 const& obj2) {
	return obj1.x * obj2.y - obj1.y * obj2.x;
}

/// <summary>
/// 回転
/// </summary>
/// <param name="obj">オブジェクトの四隅の座標</param>
/// <param name="num">何分の1π回転させるか</param>
/// <returns></returns>
inline ForCorners Rotate(ForCorners const& obj, float const& num) {
	ForCorners newObj = {};

	float theta = 1.0f / num * float(M_PI);
	newObj.bottomLeft.x = obj.bottomLeft.x * cosf(theta) - obj.bottomLeft.y * sinf(theta);
	newObj.bottomLeft.y = obj.bottomLeft.y * cosf(theta) + obj.bottomLeft.x * sinf(theta);
	newObj.bottomRight.x = obj.bottomRight.x * cosf(theta) - obj.bottomRight.y * sinf(theta);
	newObj.bottomRight.y = obj.bottomRight.y * cosf(theta) + obj.bottomRight.x * sinf(theta);
	newObj.topLeft.x = obj.topLeft.x * cosf(theta) - obj.topLeft.y * sinf(theta);
	newObj.topLeft.y = obj.topLeft.y * cosf(theta) + obj.topLeft.x * sinf(theta);
	newObj.topRight.x = obj.topRight.x * cosf(theta) - obj.topRight.y * sinf(theta);
	newObj.topRight.x = obj.topRight.y * cosf(theta) + obj.topRight.x * sinf(theta);

	return newObj;
}

/// <summary>
/// 行列の加算
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
inline Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix1.m[i][j] += matrix2.m[i][j];
		}
	}
	return matrix1;
}

/// <summary>
/// 行列の減算
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
inline Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			matrix1.m[i][j] -= matrix2.m[i][j];
		}
	}
	return matrix1;
}

/// <summary>
/// 行列の積
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
inline Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 matrix3 = {};

	matrix3.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	matrix3.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	matrix3.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
	matrix3.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	matrix3.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	matrix3.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
	matrix3.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	matrix3.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	matrix3.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];
	return matrix3;
}

/// <summary>
/// 行列の積
/// </summary>
/// <param name="matrix1"></param>
/// <param name="matrix2"></param>
/// <returns></returns>
inline Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 matrix3 = {};

	matrix3.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0];
	matrix3.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1];
	matrix3.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0];
	matrix3.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1];
	return matrix3;
}

/// <summary>
/// ベクトルと行列の積
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
inline Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 obj = {};
	obj.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	obj.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];

	return obj;
}

/// <summary>
/// 逆行列
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
inline Matrix2x2 Inverse(Matrix2x2 matrix) {
	Matrix2x2 matrix2 = {};
	float num = 1.0f / (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	matrix2.m[0][0] = num * matrix.m[1][1];
	matrix2.m[0][1] = num * -matrix.m[0][1];
	matrix2.m[1][0] = num * -matrix.m[1][0];
	matrix2.m[1][1] = num * matrix.m[0][0];

	return matrix2;
}

/// <summary>
/// 逆行列
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
inline Matrix3x3 Inverse(Matrix3x3 matrix) {
	Matrix3x3 matrix2 = {};
	float num = 1.0f / (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][1] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

	matrix2.m[0][0] = num * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	matrix2.m[0][1] = num * (-(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]));
	matrix2.m[0][2] = num * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	matrix2.m[1][0] = num * (-(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]));
	matrix2.m[1][1] = num * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	matrix2.m[1][2] = num * (-(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]));
	matrix2.m[2][0] = num * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	matrix2.m[2][1] = num * (-(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]));
	matrix2.m[2][2] = num * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return matrix2;
}

/// <summary>
/// 回転行列
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
inline Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 matrix = {};
	matrix.m[0][0] = float(cos(theta));
	matrix.m[0][1] = float(sin(theta));
	matrix.m[1][0] = -1.0f * float(sin(theta));
	matrix.m[1][1] = float(cos(theta));
	return matrix;
}

/// <summary>
/// 回転行列
/// </summary>
/// <param name="theta"></param>
/// <returns></returns>
inline Matrix3x3 MakeRotateMatrix3x3(float theta) {
	Matrix3x3 matrix = {};
	matrix.m[0][0] = float(cos(theta));
	matrix.m[0][1] = float(sin(theta));
	matrix.m[1][0] = -1.0f * float(sin(theta));
	matrix.m[1][1] = float(cos(theta));
	matrix.m[2][2] = 1;
	return matrix;
}

/// <summary>
/// 平行移動行列の作成
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
inline Matrix3x3 MakeTransLateMatrix(Vector2 translate) {
	Matrix3x3 matrix = {};
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[2][0] = translate.x;
	matrix.m[2][1] = translate.y;

	return matrix;
}

/// <summary>
/// 拡大縮小行列の作成
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
inline Matrix3x3 MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 matrix = {};
	matrix.m[0][0] = scale.x;
	matrix.m[1][1] = scale.y;
	matrix.m[2][2] = 1;
	return matrix;
}

/// <summary>
/// アフィン行列
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
inline Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	return Multiply(Multiply(MakeScaleMatrix(scale), MakeRotateMatrix3x3(rotate)), MakeTransLateMatrix(translate));
}

/// <summary>
/// 2次元ベクトルを同次座標に変換
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
inline Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result = {};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0);

	result.x /= w;
	result.y /= w;

	return result;
}

/// <summary>
/// 転置行列を求める
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
inline Matrix2x2 Transpose(Matrix2x2 matrix) {
	Matrix2x2 matrix2 = {};

	matrix2.m[0][0] = matrix.m[0][0];
	matrix2.m[0][1] = matrix.m[1][0];
	matrix2.m[1][0] = matrix.m[0][1];
	matrix2.m[1][1] = matrix.m[1][1];

	return matrix2;
}

/// <summary>
/// 転置行列を求める
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
inline Matrix3x3 Transpose(Matrix3x3 matrix) {
	Matrix3x3 matrix2 = {};

	matrix2.m[0][0] = matrix.m[0][0];
	matrix2.m[0][1] = matrix.m[1][0];
	matrix2.m[0][2] = matrix.m[2][0];
	matrix2.m[1][0] = matrix.m[0][1];
	matrix2.m[1][1] = matrix.m[1][1];
	matrix2.m[1][2] = matrix.m[2][1];
	matrix2.m[2][0] = matrix.m[0][2];
	matrix2.m[2][1] = matrix.m[1][2];
	matrix2.m[2][2] = matrix.m[2][2];

	return matrix2;
}

/// <summary>
/// 2x2行列の表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="matrix"></param>
inline void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// 3x3行列の表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="matrix"></param>
inline void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// 正射影行列
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
/// <returns></returns>
inline Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 matrix = {};

	matrix.m[0][0] = 2.0f / (right - left);
	matrix.m[1][1] = 2.0f / (top - bottom);
	matrix.m[2][0] = (left + right) / (left - right);
	matrix.m[2][1] = (top + bottom) / (bottom - top);
	matrix.m[2][2] = 1.0f;

	return matrix;
}

/// <summary>
/// ビューポート行列
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <returns></returns>
inline Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 matrix = {};

	matrix.m[0][0] = width / 2.0f;
	matrix.m[1][1] = -height / 2.0f;
	matrix.m[2][0] = left + width / 2.0f;
	matrix.m[2][1] = top + height / 2.0f;
	matrix.m[2][2] = 1.0f;

	return matrix;
}

/// <summary>
/// ベクターの表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="vector"></param>
inline void VectorScreenPrintf(int x, int y, Vector2 vector) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
}

/// <summary>
/// スクリーン座標変換
/// </summary>
/// <param name="position"></param>
/// <returns></returns>
inline Vector2 ScreenCoodinate(Vector2 position) {
	position.y = (position.y - 500) * -1;

	return position;
}

/// <summary>
/// 線形補間
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="t"></param>
/// <returns></returns>
inline Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
	return { t * a.x + (1.0f - t) * b.x, t * a.y + (1.0f - t) * b.y };
}

/// <summary>
/// 2次ベジエ曲線上の点を求める
/// </summary>
/// <param name="p0"></param>
/// <param name="pi"></param>
/// <param name="p2"></param>
/// <param name="t"></param>
/// <returns></returns>
inline Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
	Vector2 p0p1 = Lerp(p0, p1, t);

	Vector2 p1p2 = Lerp(p1, p2, t);

	return  Lerp(p0p1, p1p2, t);
}

/// <summary>
/// スプライン曲線
/// </summary>
/// <param name="p0"></param>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <param name="p3"></param>
/// <param name="t"></param>
/// <returns></returns>
inline Vector2 CatmullRom(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, float t) {
	Vector2 position = {};

	position.x = 1.0f / 2.0f * ((-p0.x + 3.0f * p1.x - 3 * p2.x + p3.x) * t * t * t +
		(2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t * t +
		(-p0.x + p2.x) * t +
		2 * p1.x);
	position.y = 1.0f / 2.0f * ((-p0.y + 3.0f * p1.y - 3 * p2.y + p3.y) * t * t * t +
		(2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t * t +
		(-p0.y + p2.y) * t +
		2 * p1.y);

	return position;
}

/// <summary>
/// wvpVp変換
/// </summary>
/// <param name="worldMatrix"></param>
/// <param name="cameraWorldMatrix"></param>
/// <param name="cameraVertex"></param>
/// <param name="viewPortPosition"></param>
/// <param name="viewPortSize"></param>
/// <returns></returns>
inline Matrix3x3 MakewvpVpMatrix(Matrix3x3 worldMatrix, Matrix3x3 cameraWorldMatrix, Vertex cameraVertex, Vector2 viewPortPosition, Vector2 viewPortSize) {
	Matrix3x3 viewMatrix = Inverse(cameraWorldMatrix);
	Matrix3x3 orthoMatrix = MakeOrthographicMatrix(cameraVertex.left, cameraVertex.top, cameraVertex.right, cameraVertex.bottom);
	Matrix3x3 viewportMatrix = MakeViewportMatrix(viewPortPosition.x, viewPortPosition.y, viewPortSize.x, viewPortSize.y);

	Matrix3x3 vpVpMatrix = Multiply(viewMatrix, orthoMatrix);
	vpVpMatrix = Multiply(vpVpMatrix, viewportMatrix);

	return Multiply(worldMatrix, vpVpMatrix);

}

/// <summary>
/// vpVp変換
/// </summary>
/// <param name="cameraWorldMatrix"></param>
/// <param name="cameraVertex"></param>
/// <param name="viewPortPosition"></param>
/// <param name="viewPortSize"></param>
/// <returns></returns>
inline Matrix3x3 MakevpVpMatrix(Matrix3x3 cameraWorldMatrix, Vertex cameraVertex, Vector2 viewPortPosition, Vector2 viewPortSize) {
	Matrix3x3 viewMatrix = Inverse(cameraWorldMatrix);
	Matrix3x3 orthoMatrix = MakeOrthographicMatrix(cameraVertex.left, cameraVertex.top, cameraVertex.right, cameraVertex.bottom);
	Matrix3x3 viewportMatrix = MakeViewportMatrix(viewPortPosition.x, viewPortPosition.y, viewPortSize.x, viewPortSize.y);

	Matrix3x3 vpVpMatrix = Multiply(viewMatrix, orthoMatrix);
	return Multiply(vpVpMatrix, viewportMatrix);
}

/// <summary>
/// 三次元の加算
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
inline Vector3 Add(const Vector3& v1, const Vector3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

/// <summary>
/// 三次元の減算
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
inline Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

/// <summary>
/// スカラー倍
/// </summary>
/// <param name="scalar"></param>
/// <param name="v"></param>
/// <returns></returns>
inline Vector3 Multiply(float scalar, const Vector3& v) {
	return { scalar * v.x, scalar * v.y, scalar * v.z };
}

/// <summary>
/// 内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
inline float Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// <summary>
/// 長さ（ノルム）
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
inline float Length(const Vector3& v) {
	return sqrtf(Dot(v, v));
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
inline Vector3 Normalize(const Vector3& v) {
	float v2 = 0.0f;
	v2 = Length(v);

	return { v.x / v2, v.y / v2, v.z / v2 };
}

/// <summary>
/// 三次元ベクトルの数値表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="vector"></param>
/// <param name="label"></param>
inline void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

/// <summary>
/// 行列の加算
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
inline Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 m3 = {};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m3.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return m3;
}

/// <summary>
/// 行列の減算
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
inline Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 m3 = {};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m3.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return m3;

}

/// <summary>
/// 行列の積
/// </summary>
/// <param name="m1"></param>
/// <param name="m2"></param>
/// <returns></returns>
inline Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 m3 = {};

	m3.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	m3.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	m3.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	m3.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	m3.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	m3.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	m3.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	m3.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	m3.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	m3.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	m3.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	m3.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	m3.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	m3.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	m3.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	m3.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return m3;
}

/// <summary>
/// 逆行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
inline Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 m2 = {};
	float num = 1.0f /
		(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
			m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
			m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -
			m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
			m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
			m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -
			m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
			m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
			m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +
			m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
			m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
			m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
			m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
			m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
			m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -
			m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
			m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
			m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -
			m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
			m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
			m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +
			m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
			m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
			m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]
			);

	m2.m[0][0] = num * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
	m2.m[0][1] = num * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
	m2.m[0][2] = num * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
	m2.m[0][3] = num * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);
	m2.m[1][0] = num * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
	m2.m[1][1] = num * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
	m2.m[1][2] = num * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
	m2.m[1][3] = num * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);
	m2.m[2][0] = num * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
	m2.m[2][1] = num * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
	m2.m[2][2] = num * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
	m2.m[2][3] = num * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);
	m2.m[3][0] = num * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
		+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
	m2.m[3][1] = num * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
	m2.m[3][2] = num * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
		+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
	m2.m[3][3] = num * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	return m2;

}

/// <summary>
/// 転置行列
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
inline Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 m2 = {};

	m2.m[0][0] = m.m[0][0];
	m2.m[0][1] = m.m[1][0];
	m2.m[0][2] = m.m[2][0];
	m2.m[0][3] = m.m[3][0];
	m2.m[1][0] = m.m[0][1];
	m2.m[1][1] = m.m[1][1];
	m2.m[1][2] = m.m[2][1];
	m2.m[1][3] = m.m[3][1];
	m2.m[2][0] = m.m[0][2];
	m2.m[2][1] = m.m[1][2];
	m2.m[2][2] = m.m[2][2];
	m2.m[2][3] = m.m[3][2];
	m2.m[3][0] = m.m[0][3];
	m2.m[3][1] = m.m[1][3];
	m2.m[3][2] = m.m[2][3];
	m2.m[3][3] = m.m[3][3];

	return m2;

}

/// <summary>
/// 単位行列の作成
/// </summary>
/// <returns></returns>
inline Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 m = {};

	m.m[0][0] = 1.0f;
	m.m[1][1] = 1.0f;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;

	return m;
}

/// <summary>
/// 行列の表示
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="matrix"></param>
inline void MatrixScreenPrint(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s\n", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
inline Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// 拡大縮小行列
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
inline Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = {};

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;

}

/// <summary>
/// 座標変換
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
inline Vector3 Transform(const Vector3& vector, const Matrix4x4 matrix) {
	Vector3 result = {};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

/// <summary>
/// x軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
inline Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// y軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
inline Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1.0f;

	return result;

}

/// <summary>
/// z軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
inline Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result = {};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;

}

/// <summary>
/// 3次元アフィン変換行列
/// </summary>
/// <param name="scale"></param>
/// <param name="rotate"></param>
/// <param name="translate"></param>
/// <returns></returns>
inline Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	return Multiply(Multiply(MakeScaleMatrix(scale), rotateXYZMatrix), MakeTranslateMatrix(translate));
}

/// <summary>
/// 透視投影行列
/// </summary>
/// <param name="fovY"></param>
/// <param name="aspectRatio"></param>
/// <param name="nearClip"></param>
/// <param name="farCrip"></param>
/// <returns></returns>
inline Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farCrip) {
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f / aspectRatio * (1.0f / std::tanf(fovY / 2.0f));
	result.m[1][1] = 1.0f / std::tanf(fovY / 2.0f);
	result.m[2][2] = farCrip / (farCrip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farCrip) / (farCrip - nearClip);
	return result;
}

/// <summary>
/// 正射影行列
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="bottom"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
/// <returns></returns>
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result = {};

	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;
}

/// <summary>
/// ビューポート変換行列
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="minDepth"></param>
/// <param name="maxDepth"></param>
/// <returns></returns>
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = {};

	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeViewProjectionMatrix(Vector3 scale, Vector3 rotate, Vector3 translate, Vector3 cameraScale, Vector3 cameraRotate, Vector3 cameraTranslate) {
	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	return (Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix)));

}

/// <summary>
/// クロス積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

/// <summary>
/// 球の描画
/// </summary>
/// <param name="sphere"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawSphere(const Sphere& sphere, const Matrix4x4 viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	//分割数
	const uint32_t kSubdivision = 12;
	//緯度分割1つ分の角度
	const float kLonEvery = 2 * 3.14f / kSubdivision;
	const float kLatEvery = 3.14f / kSubdivision;

	Vector3 ndcAVertex = {};
	Vector3 ScreenAVertices = {};
	Vector3 ndcBVertex = {};
	Vector3 ScreenBVertices = {};
	Vector3 ndcCVertex = {};
	Vector3 ScreenCVertices = {};

	//緯度の方向に分割　-π～π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		//現在の緯度シータ
		float lat = -3.14f / 2.0f + kLatEvery * latIndex;
		//緯度の方向に分割 0 ～　2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			//現在の経度ファイ
			float lon = lonIndex * kLonEvery;
			//world座標系でのa,b,cを求める
			Vector3 a, b, c;
			a.x = sphere.center.x + sphere.radius * cosf(lat) * cosf(lon);
			a.y = sphere.center.y + sphere.radius * sinf(lat);
			a.z = sphere.center.z + sphere.radius * cosf(lat) * sinf(lon);

			b.x = sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon);
			b.y = sphere.center.y + sphere.radius * sinf(lat + kLatEvery);
			b.z = sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon);

			c.x = sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery);
			c.y = sphere.center.y + sphere.radius * sinf(lat);
			c.z = sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery);


			//a,b,cをScreen座標系まで変換
			ndcAVertex = Transform(a, viewProjectionMatrix);
			ScreenAVertices = Transform(ndcAVertex, viewportMatrix);
			ndcBVertex = Transform(b, viewProjectionMatrix);
			ScreenBVertices = Transform(ndcBVertex, viewportMatrix);
			ndcCVertex = Transform(c, viewProjectionMatrix);
			ScreenCVertices = Transform(ndcCVertex, viewportMatrix);
			//ab,bcで線を引く
			Novice::DrawLine((int)ScreenAVertices.x, (int)ScreenAVertices.y, (int)ScreenBVertices.x, (int)ScreenBVertices.y, color);
			Novice::DrawLine((int)ScreenAVertices.x, (int)ScreenAVertices.y, (int)ScreenCVertices.x, (int)ScreenCVertices.y, color);
		}
	}


}

/// <summary>
/// グリッドの描画
/// </summary>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewportMatrix) {
	//グリッドの半分の幅
	const float kGridHalfWidth = 2.0f;
	//分割数
	const uint32_t kSubdivision = 10;
	//一つ分の長さ
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	Vector3 startPoint = {};
	Vector3 endPoint = {};

	Vector3 ndcStartVertex = {};
	Vector3 ScreenStartVertices = {};
	Vector3 ndcEndVertex = {};
	Vector3 ScreenEndVertices = {};


	//奥から手前の線を徐々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		startPoint.x = kGridHalfWidth - kGridEvery * xIndex;
		startPoint.z = -kGridHalfWidth;
		endPoint.x = kGridHalfWidth - kGridEvery * xIndex;
		endPoint.z = kGridHalfWidth;

		ndcStartVertex = Transform(startPoint, viewProjectionMatrix);
		ScreenStartVertices = Transform(ndcStartVertex, viewportMatrix);

		ndcEndVertex = Transform(endPoint, viewProjectionMatrix);
		ScreenEndVertices = Transform(ndcEndVertex, viewportMatrix);

		Novice::DrawLine(int(ScreenStartVertices.x), int(ScreenStartVertices.y), int(ScreenEndVertices.x), int(ScreenEndVertices.y), 0xAAAAAAFF);
	}

	//奥から手前の線を徐々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		startPoint.z = kGridHalfWidth - kGridEvery * zIndex;
		startPoint.x = -kGridHalfWidth;
		endPoint.z = kGridHalfWidth - kGridEvery * zIndex;
		endPoint.x = kGridHalfWidth;

		ndcStartVertex = Transform(startPoint, viewProjectionMatrix);
		ScreenStartVertices = Transform(ndcStartVertex, viewportMatrix);

		ndcEndVertex = Transform(endPoint, viewProjectionMatrix);
		ScreenEndVertices = Transform(ndcEndVertex, viewportMatrix);

		Novice::DrawLine(int(ScreenStartVertices.x), int(ScreenStartVertices.y), int(ScreenEndVertices.x), int(ScreenEndVertices.y), 0xAAAAAAFF);
	}
}

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};

	result.x = Dot(v1, Normalize(v2)) * Normalize(v2).x;
	result.y = Dot(v1, Normalize(v2)) * Normalize(v2).y;
	result.z = Dot(v1, Normalize(v2)) * Normalize(v2).z;

	return result;
}

/// <summary>
/// 最近接点
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
/// <returns></returns>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 cp = {};
	Vector3 result = {};
	return Add(Project(Subtract(point, segment.origin), segment.diff), segment.origin);
}

Vector3 operator+(Vector3 num1, Vector3 num2) {
	num1.x += num2.x;
	num1.y += num2.y;
	num1.z += num2.z;

	return num1;
}

Vector3 operator-(Vector3 num1, Vector3 num2) {
	num1.x -= num2.x;
	num1.y -= num2.y;
	num1.z -= num2.z;

	return num1;
}

/// <summary>
/// 球同士の衝突判定
/// </summary>
/// <param name="s1"></param>
/// <param name="s2"></param>
/// <returns></returns>
bool isCollision(const Sphere& s1, const Sphere& s2) {
	//二つの球の中心点間の距離を求める
	float distance = Length(s2.center - s1.center);

	//半径の合計よりも短ければ衝突
	if (distance <= s1.radius + s2.radius) {
		return true;
	}

	return false;
}

/// <summary>
/// 球と平面の衝突判定
/// </summary>
/// <param name="sphere"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool isCollision(const Sphere& sphere, const Plane& plane) {
	if (sphere.radius >= fabsf(Dot(plane.normal, sphere.center) - plane.distance)) {
		return true;
	}

	return false;
}

/// <summary>
/// 垂直なベクトルを求める
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };
	}

	return { 0.0f, -vector.z, vector.y };
}

/// <summary>
/// 平面の描画
/// </summary>
/// <param name="plane"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];

	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t i = 0; i < 4; ++i) {
		Vector3 extend = Multiply(2.0f, perpendiculars[i]);
		Vector3 point = Add(center, extend);
		points[i] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);
}

/// <summary>
/// 直線と平面の衝突判定
/// </summary>
/// <param name="line"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool IsCollision(const Line& line, const Plane& plane) {
	float dot = Dot(plane.normal, line.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	if (t == -1.0f) {
		return true;
	}

	return false;
}

/// <summary>
/// 半直線と平面の衝突判定
/// </summary>
/// <param name="ray"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool IsCollision(const Ray& ray, const Plane& plane) {
	float dot = Dot(plane.normal, ray.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(ray.origin, plane.normal)) / dot;

	if (t == 2.0f) {
		return true;
	}

	return false;
}

/// <summary>
/// 線分と平面の衝突判定
/// </summary>
/// <param name="segment"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool IsCollision(const Segment& segment, const Plane& plane) {
	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}

	return false;
}

/// <summary>
/// 直線の描画
/// </summary>
/// <param name="line"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawSegment(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 start = Transform(Transform(line.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(line.origin, line.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

/// <summary>
/// 半直線の描画
/// </summary>
/// <param name="ray"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawSegment(const Ray& ray, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 start = Transform(Transform(ray.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(ray.origin, ray.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

/// <summary>
/// 線分の描画
/// </summary>
/// <param name="segment"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

/// <summary>
/// 三角形と線分の衝突判定
/// </summary>
/// <param name="triangle"></param>
/// <param name="segment"></param>
/// <returns></returns>
bool IsCollision(const Triangle& triangle, const Segment& segment) {
	Vector3 v01 = triangle.vertices[0] - triangle.vertices[1];
	Vector3 v12 = triangle.vertices[1] - triangle.vertices[2];
	Vector3 v20 = triangle.vertices[2] - triangle.vertices[0];
	segment;
	//Vector3 p = segment.origin +  
	//
	//	Vector3 v0p{}, v1p{}, v2p{};

	return false;
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 start[3];
	Vector3 end[3];

	for (uint32_t i = 0; i < 3; i++) {
		start[i] = Transform(Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
		end[i] = Transform(Transform(triangle.vertices[(i + 1) % 3], viewProjectionMatrix), viewportMatrix);
		Novice::DrawLine(int(start[i].x), int(start[i].y), int(end[i].x), int(end[i].y), color);
	}


}