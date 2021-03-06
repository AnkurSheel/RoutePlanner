//  *******************************************************************************************************************
//  Vector3   version:  1.0   Ankur Sheel  date: 2012/08/28
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef Vector3_h__
#define Vector3_h__

#include "BaseDefines.h"
#include "MathIncludes.h"

namespace Base
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Encapsulates a 3D vector with X, Y and Z components .
	///
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cVector3
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cVector3();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] X The X component of the vector
		/// @param[in] Y The Y component of the vector
		/// @param[in] Z The Z component of the vector
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cVector3(const float X, const float Y, const float Z);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] arr Array of float for the /code v component
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cVector3(float arr[]);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns true if the vector is 0.
		///
		/// @return True if the vector is 0
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool IsZero() const { return LengthSquared() < EpsilonFloat; }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Gets the reverse vector
		///
		/// @return Reverse of this vector
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cVector3 GetReverse() { return cVector3(-x, -y, -z); }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Checks if the passed in vector is equal to the current vector
		///
		/// @param[in] inVec The vector to check against.
		/// @return True if the 2 vectors are equal. False otherwise.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator == (const cVector3 & inVec) const { return (isEqual(x, inVec.x) && isEqual(y, inVec.y) && isEqual(z, inVec.z)); }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Checks if the passed in vector is not equal to the current vector
		///
		/// @param[in] inVec The vector to check against.
		/// @return True if the 2 vectors are not equal. False otherwise.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator != (const cVector3 & inVec) const { return (!isEqual(x, inVec.x) || !isEqual(y, inVec.y) || !isEqual(z, inVec.z)); }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the length of the vector.
		///
		/// @return Length of the vector
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API float Length() const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the squared length of the vector.
		///
		/// @return Squared length of the vector 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API float LengthSquared() const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Converts the Vector into a unit vector
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void Normalize();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Calculates and returns the dot product.
		///
		/// @param[in] inVec The vector with which the dot product needs to be calculated
		/// @return The dot product between this vector and the one passed as a parameter
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API float Dot(const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Calculate and returns a vector perpendicular to these vectors.
		///
		/// @param[in] inVec the vector with which the cross product needs to be calculated.
		/// @return the cross product between these 2 vectors.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cVector3 Cross( const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the distance between this vector and the one passed as a parameter.
		///
		/// @param[in] inVec The vector with which the distance needs to be calculated
		/// @return Euclidean distance 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API float Distance(const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the squared distance between this vector and the one passed as a parameter
		///
		/// @param[in] inVec The vector with which the distance needs to be calculated.
		/// @return Squared euclidean distance 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API float DistanceSquared(const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Sets the components to their absolute values.
		///
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void AbsTo();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Changes the sign of the components.
		///
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void NegTo();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Get the largest coordinate and return a signed, unit vector containing only that coordinate.
		///
		/// @return A signed, unit vector containing only the largest coordinate
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cVector3 MajorAxis() const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Get the smallest coordinate and return a signed, unit vector containing only that coordinate.
		///
		/// @return A signed, unit vector containing only the smallest coordinate
		/// 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cVector3 MinorAxis() const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Adds the passed in vector to the current vector.
		///
		/// @param[in] inVec The vector that is to be added
		/// @return The vector after the addition
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const cVector3 & operator += (const cVector3 & inVec);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Subtracts the passed in vector from the current vector.
		///
		/// @param[in] inVec The vector that is to be subtracted
		/// @return The vector after the subtraction
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const cVector3 & operator -= (const cVector3 & inVec);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Multiplies the passed in vector to the current vector.
		///
		/// @param[in] inVec The vector that is to be multiplied.
		/// @return The vector after the multiplication
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const cVector3 & operator *= (const cVector3 & inVec);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Multiplies the passed in value to each component of the current vector.
		///
		/// @param[in] Val The scalar value that is to be multiplied.
		/// @return The vector after the multiplication
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const cVector3 & operator *= (const float Val);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Divides the passed in value from each component of the current vector.
		///
		/// @param[in] Val The scalar value that is to be divided.
		/// @return The vector after the multiplication
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const cVector3 & operator /= (const float Val);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the component at the index
		///
		/// @param[in] index The index to get
		/// @return The value at the index
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API float & operator [] (const unsigned int index);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the component at the index
		///
		/// @param[in] index The index to get
		/// @return The value at the index
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const float operator [] (const unsigned int index) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns a vector between start and end which /code lerpfactor away from start.
		///
		/// @param[in] start The start vector
		/// @param[in] end The end vector
		/// @param[in] lerpFactor The percentage through which the new vector should be away from start
		/// @return Put The vector which is lerpfactor away from start
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API static cVector3 Lerp(const cVector3 & start, const cVector3 & end, float lerpFactor);

		BASE_API static const cVector3 Zero;
		BASE_API static const cVector3 One;

	public:
		union
		{
			struct 
			{ 
				float x;	///< X component of Vector2
				float y;	///< Y component of Vector2
				float z;	///< Z component of Vector2
			};
			float v[3];
		};
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Returns a vector which is the result of invec2 + invec1
	///
	/// @param[in] inVec1 The first vector that is to be added
	/// @param[in] inVec2 The second vector that is to be added
	/// @return The vector after the addition
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline cVector3 operator + (const cVector3 & inVec1, const cVector3 & inVec2);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Returns a vector which is the result of invec2 - invec1
	///
	/// @param[in] inVec1 The first vector
	/// @param[in] inVec2 The vector that is to be subtracted
	/// @return The vector after the Subtraction
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline cVector3 operator - (const cVector3 & inVec1, const cVector3 & inVec2);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Returns a vector which is the result of Multiplication of the passed in vector with the scalar value
	///
	/// @param[in] inVec1 The vector
	/// @param[in] Val The scalar value that is to be multiplied.
	/// @return The vector after the multiplication
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline cVector3 operator * (const cVector3 & inVec1, const float Val);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Returns a vector which is the result of Multiplication of of each component of the passed in vector with the 
	/// scalar value
	///
	/// @param[in] Val The scalar value that is to be multiplied.
	/// @param[in] inVec1 The vector
	/// @return The vector after the multiplication
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline cVector3 operator * (const float Val, const cVector3 & inVec1);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Returns a vector which is the result of Multiplication of of each component of the passed in vector with the 
	/// scalar value
	///
	/// @param[in] inVec1 The first vector that is to be multiplied
	/// @param[in] inVec2 The second vector that is to be multiplied
	/// @return The vector after the multiplication
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline cVector3 operator * (const cVector3 & inVec1, const cVector3 & inVec2);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Returns a vector which is the result of multiplication of the passed in vectors
	///
	/// @param[in] inVec1 The vector
	/// @param[in] Val The scalar value that is to be divided.
	/// @return The vector after the multiplication
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline cVector3 operator / (const cVector3 & inVec1, const float Val);

#include "Vector3.inl"
}
#endif // Vector3_h__
