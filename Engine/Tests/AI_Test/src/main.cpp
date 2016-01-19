#include "stdafx.h"
#include "ServiceLocator.h"

int main(int argc, char **argv) 
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	Base::cServiceLocator::Destroy();
	return 0;
}
