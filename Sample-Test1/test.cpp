#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project1/DeviceDriver.cpp"

#include <iostream>
using namespace std;
using namespace testing;

class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

TEST(DeviceDriverTest, ReadSuccessTest)
{
	FlashMock mock;

	EXPECT_CALL(mock, read(_))
		.Times(5)
		.WillRepeatedly(Return(123));

	DeviceDriver driver(&mock);
	EXPECT_THAT(driver.read(0), Eq(123));
}

TEST(DeviceDriverTest, ReadFailTest)
{
	FlashMock mock;

	int temp = 123;
	EXPECT_CALL(mock, read(_))
		.Times(5)
		.WillRepeatedly(Return(temp++));

	DeviceDriver driver(&mock);
	EXPECT_THAT(driver.read(0), Ne(temp));
}