#include "tlist.h"

#include <gtest.h>

TEST(tList, can_create_vector_not_parametr)
{
	ASSERT_NO_THROW(List<int> l);
}

TEST(tList, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(List<int> l(5));
}

TEST(tList, can_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(List<int> l(-2));
}

TEST(tList, can_create_vector_with_large_length)
{
	ASSERT_NO_THROW(List<long long> l(9999));
}

TEST(tList, test_operator_ravno_equal_length)
{
	List<int> l(2, 0);
	List<int> l1(2, 0);

	l[1] = 1;

	l1 = l;

	EXPECT_EQ(l, l1);
}

TEST(tList, test_operator_ravno_different_length)
{
	List<int> l(2, 0);
	List<int> l1(5, 0);

	l[1] = 1;
	l[0] = 23;

	l1 = l;

	EXPECT_EQ(l, l1);
}

TEST(tList, test_operator_ravno_equal_list)
{
	List<int> l(2, 0);
	List<int> l1(2, 0);

	l[1] = 1;
	l1[1] = 1;

	l1 = l;

	EXPECT_EQ(l, l1);
}

TEST(tList, test_operator_skobki) 
{
	List<int> l(2, 0);
	List<int> l1(2, 0);

	l[1] = 1;
	l1[1] = l[1];

	EXPECT_EQ(l, l1);
}

TEST(tList, test_operator_skobki_negative_index)
{
	List<int> l(2, 0);

	ASSERT_ANY_THROW(l[4]);
}

TEST(tList, test_get_size_equal)
{
	List<int> l(2);

	int res = l.size();

	EXPECT_EQ(2 + 1, res);
}

TEST(tList, test_get_index)
{
	List<int> l(2);

	ASSERT_ANY_THROW(l.get_index(7));
}

TEST(tList, test_insert_equal_type)
{
	List<int> l(2);
	int sz = l.size();

	l.insert(1, l.get_index(1));

	EXPECT_EQ(1, l[2]);
	EXPECT_EQ(4, sz + 1);
}

TEST(tList, test_insert_different_type)
{
	List<int> l(2, 0);

	ASSERT_ANY_THROW(l.insert(1, l.get_index(1)));
}

TEST(tList, test_insert_front)
{
	List<int> l(2);
	int sz = l.size();

	l.insert_front(1);

	EXPECT_EQ(1, l[0]);
	EXPECT_EQ(4, sz + 1);
}

TEST(tList, test_erase)
{
	List<int> l(3, 0);
	int sz = l.size();

	l[2] = 1;

	l.erase(l.get_index(1));

	EXPECT_EQ(0, l[2]);
	EXPECT_EQ(3, sz - 1);
}

TEST(tList, test_erase_front)
{
	List<int> l(3, 0);
	int sz = l.size();

	l[0] = 1;

	l.erase_front();

	EXPECT_EQ(0, l[0]);
	EXPECT_EQ(3, sz - 1);
}

TEST(tList, test_find_true)
{
	List<int> l(3, 0);
	
	l[3] = 1;

	EXPECT_EQ(l.get_index(3), l.find(1));
}

TEST(tList, test_find_false)
{
	List<int> l(3, 0);

	ASSERT_ANY_THROW(l.find(1));
}

TEST(tList, test_get_first)
{
	List<int> l(3, 0);

	EXPECT_EQ(l.get_index(0), l.get_first());
}

//TEST(tList, test_istr)
//{
//	List<int> l(2);
//	List<int> l1(2, 2);
//
//	std::cin >> l;
//	std::cout << std::endl;
//
//	EXPECT_EQ(l1, l);
//}
//
//TEST(tList, test_ostr)
//{
//	List<int> l(2);
//
//	l[1] = 2;
//
//	ASSERT_NO_THROW(std::cout << l);
//}