#pragma once

#include <YRPPCore.h>
#include <GeneralStructures.h>
#include <Quaternion.h>

#include <Helpers/CompileTime.h>

template <typename T>
class Vector4D
{
public:
	static const Vector4D Empty;

	//no constructor, so this class stays aggregate and can be initialized using the curly braces {}
	T X, Y, Z, W;

	// TODO add Vector4 methods
};

template <typename T>
const Vector4D<T> Vector4D<T>::Empty = { T(), T(), T(), T() };

class Matrix3D
{
public:

	//Constructor

	Matrix3D() = default;

	// plain floats ctor
	Matrix3D(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		row[0][0] = m00; row[0][1] = m01; row[0][2] = m02; row[0][3] = m03;
		row[1][0] = m10; row[1][1] = m11; row[1][2] = m12; row[1][3] = m13;
		row[2][0] = m20; row[2][1] = m21; row[2][2] = m22; row[2][3] = m23;
		// JMP_THIS(0x5AE630);
	}

	// column vector ctor
	Matrix3D(
		Vector3D<float> const& x,
		Vector3D<float> const& y,
		Vector3D<float> const& z,
		Vector3D<float> const& pos)
	{
		row[0][0] = x.X; row[0][1] = y.X; row[0][2] = z.X; row[0][3] = pos.X;
		row[1][0] = x.Y; row[1][1] = y.Y; row[1][2] = z.Y; row[1][3] = pos.Y;
		row[2][0] = x.Z; row[2][1] = y.Z; row[2][2] = z.Z; row[2][3] = pos.Z;
		// JMP_THIS(0x5AE690);
	}

	// some other rotation ctor?
	Matrix3D(float rotate_z, float rotate_x) { JMP_THIS(0x5AE6F0); }

	// rotation ctor
	Matrix3D(Vector3D<float>* axis, float angle) { JMP_THIS(0x5AE750); }

	// copy ctor
	Matrix3D(const Matrix3D& another)
	{
		memcpy(this, &another, sizeof(Matrix3D));
		// JMP_THIS(0x5AE610);
	}

	Matrix3D(Matrix3D&& another) = default;

	Matrix3D& operator=(const Matrix3D& another)
	{
		memcpy(this, &another, sizeof(Matrix3D));
		return *this;
	}

	Matrix3D& operator=(Matrix3D&& another) = default;

	// Non virtual

	// operators
	Matrix3D operator*(const Matrix3D& b) const
	{
		Matrix3D ret;
		MatrixMultiply(&ret, this, &b);
		return ret;
	}
	void operator*=(const Matrix3D& another)
	{
		MatrixMultiply(this, this, &another);
	}
	Vector3D<float> operator*(const Vector3D<float>& point) const
	{
		Vector3D<float> ret;
		MatrixMultiply(&ret, this, &point);
		return ret;
	}

	void MakeIdentity() { JMP_THIS(0x5AE860); } // 1-matrix
	void Translate(float x, float y, float z) { JMP_THIS(0x5AE890); }
	void Translate(Vector3D<float> const& vec) { JMP_THIS(0x5AE8F0); }
	void TranslateX(float x) { JMP_THIS(0x5AE980); }
	void TranslateY(float y) { JMP_THIS(0x5AE9B0); }
	void TranslateZ(float z) { JMP_THIS(0x5AE9E0); }
	void Scale(float factor) { JMP_THIS(0x5AEA10); }
	void Scale(float x, float y, float z) { JMP_THIS(0x5AEA70); }
	void ScaleX(float factor) { JMP_THIS(0x5AEAD0); }
	void ScaleY(float factor) { JMP_THIS(0x5AEAF0); }
	void ScaleZ(float factor) { JMP_THIS(0x5AEB20); }
	void ShearYZ(float y, float z) { JMP_THIS(0x5AEB50); }
	void ShearXY(float x, float y) { JMP_THIS(0x5AEBA0); }
	void ShearXZ(float x, float z) { JMP_THIS(0x5AEBF0); }
	void PreRotateX(float theta) { JMP_THIS(0x5AEC40); }
	void PreRotateY(float theta) { JMP_THIS(0x5AED50); }
	void PreRotateZ(float theta) { JMP_THIS(0x5AEE50); }
	void RotateX(float theta) { JMP_THIS(0x5AEF60); }
	void RotateX(float Sin, float Cos) { JMP_THIS(0x5AF000); }
	void RotateY(float theta) { JMP_THIS(0x5AF080); }
	void RotateY(float Sin, float Cos) { JMP_THIS(0x5AF120); }
	void RotateZ(float theta) { JMP_THIS(0x5AF1A0); }
	void RotateZ(float Sin, float Cos) { JMP_THIS(0x5AF240); }
	float GetXVal() { JMP_THIS(0x5AF2C0); }
	float GetYVal() { JMP_THIS(0x5AF310); }
	float GetZVal() { JMP_THIS(0x5AF360); }
	float GetXRotation() { JMP_THIS(0x5AF3B0); }
	float GetYRotation() { JMP_THIS(0x5AF410); }
	float GetZRotation() { JMP_THIS(0x5AF470); }
	Vector3D<float>* RotateVector(Vector3D<float>* ret, Vector3D<float>* rotate) { JMP_THIS(0x5AF4D0); }
	Vector3D<float> RotateVector(Vector3D<float>& rotate)
	{
		Vector3D<float> buffer;
		RotateVector(&buffer, &rotate);
		return buffer;
	}
	void LookAt1(Vector3D<float>& p, Vector3D<float>& t, float roll) { JMP_THIS(0x5AF550); }
	void LookAt2(Vector3D<float>& p, Vector3D<float>& t, float roll) { JMP_THIS(0x5AF710); }

	static Matrix3D* __fastcall MatrixMultiply(Matrix3D* ret, const Matrix3D* A, const Matrix3D* B) { JMP_STD(0x5AF980); }
	static Matrix3D MatrixMultiply(const Matrix3D& A, const Matrix3D& B)
	{
		Matrix3D buffer;
		MatrixMultiply(&buffer, &A, &B);
		return buffer;
	}
	static Vector3D<float>* __fastcall MatrixMultiply(Vector3D<float>* ret, const Matrix3D* mat, const Vector3D<float>* vec) { JMP_STD(0x5AFB80); }
	static Vector3D<float> MatrixMultiply(const Matrix3D& mat, const Vector3D<float>& vec)
	{
		Vector3D<float> buffer;
		MatrixMultiply(&buffer, &mat, &vec);
		return buffer;
	}
	static Matrix3D* __fastcall TransposeMatrix(Matrix3D* buffer, const Matrix3D* mat) { JMP_STD(0x5AFC20); }
	static Matrix3D TransposeMatrix(const Matrix3D& mat)
	{
		Matrix3D buffer;
		TransposeMatrix(&buffer, &mat);
		return buffer;
	}
	void Transpose()
	{
		*this = TransposeMatrix(*this);
	}

	static Matrix3D* __fastcall FromQuaternion(Matrix3D* mat, const Quaternion* q) { JMP_STD(0x646980); }
	static Matrix3D FromQuaternion(const Quaternion& q)
	{
		Matrix3D buffer;
		FromQuaternion(&buffer, &q);
		return buffer;
	}
	void ApplyQuaternion(const Quaternion& q)
	{
		*this = FromQuaternion(q) * *this;
	}

	static constexpr reference<Matrix3D, 0xB44318> VoxelDefaultMatrix{};
	static constexpr reference<Matrix3D, 0xB45188, 21> VoxelRampMatrix{};

	//Properties
public:
	union
	{
		Vector4D<float> Row[3];
		float row[3][4];
		float Data[12];
	};
};
