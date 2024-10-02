#include <gtest/gtest.h>

#include "u_counter_t.h"

TEST(u_counter_t, TestIncrement) {
	u_counter_t<int> counter = 5;
	++counter;
	ASSERT_EQ(counter.get(), 6);
}

TEST(u_counter_t, TestDecrement) {
	u_counter_t<int> counter = 5;
	--counter;
	ASSERT_EQ(counter.get(), 4);
}

TEST(u_counter_t, TestPostIncrement) {
	u_counter_t<int> counter = 5;
	const u_counter_t<int> result = counter++;
	ASSERT_EQ(counter.get(), 6);
	ASSERT_EQ(result.get(), 5);
}

TEST(u_counter_t, TestPostDecrement) {
	u_counter_t<int> counter = 5;
	const u_counter_t<int> result = counter--;
	ASSERT_EQ(counter.get(), 4);
	ASSERT_EQ(result.get(), 5);
}

TEST(u_counter_t, TestOverflow) {
	u_counter_t<int> counter = std::numeric_limits<int>::max();
	ASSERT_THROW(++counter, std::overflow_error);
}

TEST(u_counter_t, TestUnderflow) {
	u_counter_t<int> counter = std::numeric_limits<int>::min();
	ASSERT_THROW(--counter, std::underflow_error);
}

TEST(u_counter_t, TestLessThan) {
	u_counter_t<int> counter1 = 5;
	u_counter_t<int> counter2 = 10;
	ASSERT_TRUE(counter1 < counter2);
	ASSERT_FALSE(counter2 < counter1);
}

TEST(u_counter_t, TestEqual) {
	u_counter_t<int> counter1 = 5;
	u_counter_t<int> counter2 = 5;
	ASSERT_TRUE(counter1 == counter2);
}

TEST(u_counter_t, TestPlusEquals) {
	u_counter_t<int> counter1 = 5;
	u_counter_t<int> counter2 = 10;
	counter1 += counter2;
	ASSERT_EQ(counter1.get(), 15);
}

TEST(u_counter_t, TestMinusEquals) {
	u_counter_t<int> counter1 = 15;
	u_counter_t<int> counter2 = 5;
	counter1 -= counter2;
	ASSERT_EQ(counter1.get(), 10);
}

TEST(u_counter_t, TestConstructor) {
	u_counter_t<int> counter = 5;
	ASSERT_EQ(counter.get(), 5);
}

TEST(u_counter_t, TestCopyConstructor) {
	u_counter_t<int> counter1 = 5;
	u_counter_t<int> counter2 = counter1;
	ASSERT_EQ(counter2.get(), 5);
}

TEST(u_counter_t, TestMoveConstructor) {
	u_counter_t<int> counter1 = 5;
	u_counter_t<int> counter2 = std::move(counter1);
	ASSERT_EQ(counter2.get(), 5);
}

TEST(u_counter_t, TestAssignmentOperator) {
	u_counter_t<int> counter1 = 5;
	u_counter_t<int> counter2 = 10;
	counter2 = counter1;
	ASSERT_EQ(counter2.get(), 5);
}

TEST(u_counter_t, TestMoveAssignmentOperator) {
	u_counter_t<int> counter1 = 5;
	u_counter_t<int> counter2 = 10;
	counter2 = std::move(counter1);
	ASSERT_EQ(counter2.get(), 5);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
