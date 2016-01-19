//  *******************************************************************************************************************
cVector3 operator * (const cVector3 & inVec1, const float Val)
{
	cVector3 result(inVec1);
	result *= Val;
	return result;
}

//  *******************************************************************************************************************
cVector3 operator * (const float Val, const cVector3 & inVec1)
{
	cVector3 result(inVec1);
	result *= Val;
	return result;
}

//  *******************************************************************************************************************
cVector3 operator / (const cVector3 & inVec1, const float Val)
{
	cVector3 result(inVec1);
	result /= Val;
	return result;
}

//  *******************************************************************************************************************
cVector3 operator - (const cVector3 & inVec1, const cVector3 & inVec2)
{
	cVector3 result(inVec1);
	result -= inVec2;
	return result;
}

//  *******************************************************************************************************************
cVector3 operator + (const cVector3 & inVec1, const cVector3 & inVec2)
{
	cVector3 result(inVec1);
	result += inVec2;
	return result;
}

//  *******************************************************************************************************************
cVector3 operator * (const cVector3 & inVec1, const cVector3 & inVec2)
{
	cVector3 result(inVec1);
	result *= inVec2;
	return result;
}
