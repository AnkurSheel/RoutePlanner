//  ********************************************************************************************************************
cVector2 operator * (const cVector2 & inVec1, const float Val)
{
	cVector2 result(inVec1);
	result *= Val;
	return result;
}


//  *******************************************************************************************************************
cVector2 operator * (const float Val, const cVector2 & inVec1)
{
	cVector2 result(inVec1);
	result *= Val;
	return result;
}

//  *******************************************************************************************************************
cVector2 operator / (const cVector2 & inVec1, const float Val)
{
	cVector2 result(inVec1);
	result /= Val;
	return result;
}

//  *******************************************************************************************************************
cVector2 operator - (const cVector2 & inVec1, const cVector2 & inVec2)
{
	cVector2 result(inVec1);
	result -= inVec2;
	return result;
}

//  *******************************************************************************************************************
cVector2 operator + (const cVector2 & inVec1, const cVector2 & inVec2)
{
	cVector2 result(inVec1);
	result += inVec2;
	return result;
}

//  *******************************************************************************************************************
cVector2 operator * (const cVector2 & inVec1, const cVector2 & inVec2)
{
	cVector2 result(inVec1);
	result *= inVec2;
	return result;
}
