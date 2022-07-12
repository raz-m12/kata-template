#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

using namespace argskata::lib;
using namespace ::testing;
using namespace std;
using testing::UnorderedElementsAre;

// ============================================================
// ======================== Back log ==========================
// 1. Feeds parser with empty schema and throws exception
// 2. Parses one argument based on a schema with support for
//    one boolean
// 3. Throws exception when given argument not defined in the
//    schema
// 4. Gives as input arguments that do not adhere to the schema
//    which throws an exception
// [DOING] Adds schema support for: boolean, string, integer,
//    double, arrays

// Tests:
// - BooleanFlagDefaultsToFalseWhenNotInArgumentList

// TODO(RV):
// - https://stackoverflow.com/questions/39049803/google-test-cant-find-user-provided-equality-operator
// ============================================================

namespace std {
    template<typename T>
    auto operator==(const unordered_map<string, shared_ptr<T>> &lhs, const unordered_map<string, shared_ptr<T>> &rhs) -> bool
    {
        if(lhs.size() != rhs.size()) { 
            return false;
        }
        
        return ranges::all_of(lhs.cbegin(), lhs.cend(), [&rhs = as_const(rhs)](pair<string, shared_ptr<T>> pair){
            auto _it = rhs.find(pair.first);
            if(_it == rhs.end()) {
                return false;
            }

            if(*(pair.second) != *(_it->second)) {
                return false;
            }
            return true;
        });
    }
} // namespace std

namespace argskata_test
{
    class SchemaValidationFixture : public testing::Test
    {
    public:
        static const vector<string> EmptyArgs;
    };
    const vector<string> SchemaValidationFixture::EmptyArgs = {};
    

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsedBooleanArguments)
    {
        const string schema{"(f,d)"};
        ArgsParser parser{schema, EmptyArgs};

        std::unordered_map<string, shared_ptr<AbstractArgument>> expected = {
            make_pair("f", make_shared<BooleanArgument>("f")),
            make_pair("d", make_shared<BooleanArgument>("d"))
        };

        ASSERT_THAT(parser.GetSchema(), Eq(expected));
    }

    /* TODO(RV) As soon as the tests on integers are finished */
    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsedIntegerArguments)
    {
        const string schema{"(i#,o#)"};
        ArgsParser parser(schema, EmptyArgs);
        std::unordered_map<string, shared_ptr<AbstractArgument>> expected = {
            make_pair("i", make_shared<IntegerArgument>("i")),
            make_pair("o", make_shared<IntegerArgument>("o"))
        };

        ASSERT_THAT(parser.GetSchema(), Eq(expected));
    }

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsesStringArguments)
    {
        const string schema{"(i*,o*)"};
        ArgsParser parser(schema, EmptyArgs);

        std::unordered_map<string, shared_ptr<AbstractArgument>> expected = {
            make_pair("i", make_shared<StringArgument>("i")),
            make_pair("o", make_shared<StringArgument>("o"))
        };

        ASSERT_THAT(parser.GetSchema(), Eq(expected));
    }

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsesDoubleArguments)
    {
        const string schema{"(i##,o##)"};
        ArgsParser parser(schema, EmptyArgs);

        std::unordered_map<string, shared_ptr<AbstractArgument>> expected = {
            make_pair("i", make_shared<DoubleArgument>("i")),
            make_pair("o", make_shared<DoubleArgument>("o"))
        };

        ASSERT_THAT(parser.GetSchema(), Eq(expected));
    }
    

    TEST_F(SchemaValidationFixture, VerifiesResultingSchemaParsesStringArrayArguments)
    {
        const string schema{"(i[*],o[*])"};
        ArgsParser parser(schema, EmptyArgs);

        std::unordered_map<string, shared_ptr<AbstractArgument>> expected = {
            make_pair("i", make_shared<StringArrayArgument>("i")),
            make_pair("o", make_shared<StringArrayArgument>("o"))
        };

        ASSERT_THAT(parser.GetSchema(), Eq(expected));
    }

    TEST_F(SchemaValidationFixture, DISABLED_VerifiesResultingSchemaParsesStringArrayArguments)
    {
        const string schema{"(i[*],o[*])"};
        ArgsParser parser(schema, EmptyArgs);

        ASSERT_THAT(parser.GetSchema(), UnorderedElementsAre(
                                            Pair("i", make_shared<BooleanArgument>("i")),
                                            Pair("o", make_shared<BooleanArgument>("o"))));
    }
} // namespace argskata_test