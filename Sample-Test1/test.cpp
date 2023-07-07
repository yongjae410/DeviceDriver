#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project1/DeviceDriver.cpp"

using namespace std;
using namespace testing;

class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

class DeviceDriverFixture : public Test
{
public:
	DeviceDriverFixture()
	{
		driver = new DeviceDriver(&mock);
	}

	FlashMock mock;
	DeviceDriver* driver;
};

TEST_F(DeviceDriverFixture, ReadSuccessTest)
{
	EXPECT_CALL(mock, read(_))
		.Times(5)
		.WillRepeatedly(Return(123));

	EXPECT_THAT(driver->read(0), Eq(123));
}

TEST_F(DeviceDriverFixture, ReadFailTest)
{
	EXPECT_CALL(mock, read(_))
		.WillOnce(Return(123))
		.WillRepeatedly(Return(456));
	
	EXPECT_THROW(driver->read(0), ReadFailException);
}

TEST_F(DeviceDriverFixture, WriteSuccessTest)
{
	EXPECT_CALL(mock, read(0x1000))
		.Times(1)
		.WillOnce(Return(0xFF));
	
	driver->write(0x1000, 0x10);
}

TEST_F(DeviceDriverFixture, WriteFailTest)
{
	EXPECT_CALL(mock, read(0x1000))
		.WillRepeatedly(Return(0x00));
	
	EXPECT_THROW(driver->write(0x1000, 0x10), WriteFailException);
}