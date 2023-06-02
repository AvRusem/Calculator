#include "pch.h"
#include "operator.h"

#include <memory>

TEST(OperatorTest, Default) {
    std::unique_ptr<Operator> functor = GetOperatorFromString("+");
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_EQ(6, (*functor)(4, 2));
    }

    functor.reset(GetOperatorFromString("-").release());
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_EQ(6, (*functor)(10, 4));
    }

    functor.reset(GetOperatorFromString("*").release());
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_EQ(6, (*functor)(2, 3));
    }

    functor.reset(GetOperatorFromString("/").release());
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_EQ(6, (*functor)(24, 4));
    }

    functor.reset(GetOperatorFromString("_").release());
    EXPECT_EQ(nullptr, functor);
}

TEST(OperatorTest, Nan) {
    std::unique_ptr<Operator> functor = GetOperatorFromString("+");
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_TRUE(std::isnan((*functor)(NAN, 2)));
    }

    functor.reset(GetOperatorFromString("-").release());
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_TRUE(std::isnan((*functor)(NAN, 4)));
    }

    functor.reset(GetOperatorFromString("*").release());
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_TRUE(std::isnan((*functor)(NAN, 3)));
    }

    functor.reset(GetOperatorFromString("/").release());
    EXPECT_NE(nullptr, functor);
    if (functor) {
        EXPECT_TRUE(std::isnan((*functor)(24, NAN)));
    }
}
