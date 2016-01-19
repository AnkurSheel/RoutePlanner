#include "stdafx.h"
#include "Visitor.h"
#include "AutoCaptureOutput.h"

using namespace Base;

class Visitable1 
	: public BaseVisitable<>
{
public:
	VISITABLE();
};

class Visitable2 
	: public BaseVisitable<>
{
public:
	VISITABLE();
};

class VisitorDerived 
	: public BaseVisitor
	, public Visitor<Visitable1>
	, public Visitor<Visitable2>
{
public:
	void visit(Visitable1 & c)
	{
		std::cout << "Visiting 1" <<  std::endl;
	}
	void visit(Visitable2 & c)
	{
		std::cout << "Visiting 2" << std::endl;
	}
};


class VisitorTest : public ::testing::Test
{
protected:

	void SetUp()
	{
	}

	void TearDown()
	{
	}

	static AutoCaptureOutput m_Output;
};

AutoCaptureOutput VisitorTest::m_Output;

TEST_F(VisitorTest, InitialTest)
{
	VisitorDerived visitor;
	Visitable1 visitable1; 
	Visitable2 visitable2;

	visitable1.accept(visitor);
	CHECK_OUTPUT("Visiting 1\n");
	visitable2.accept(visitor);
	CHECK_OUTPUT("Visiting 2\n");
}
