#include "gmock/gmock.h"
#include "include/ArgsParser.hpp"

using namespace argskata::lib;
using namespace ::testing;
using namespace std;
using testing::UnorderedElementsAre;    
namespace argskata_test
{  
    class AnUnhappyTest: public testing::Test
    {
        public:
        static const vector<string> EmptyArgs;
    };
    const vector<string> AnUnhappyTest::EmptyArgs = {};

    TEST_F(AnUnhappyTest, ThrowsWhenSchemaDoesNotStartWithOpenParanthesis)
    {
        ASSERT_THROW(ArgsParser parser("f)", EmptyArgs), SchemaMustStartAndEndWithParenthesisException);
    }

    TEST_F(AnUnhappyTest, ThrowsWhenSchemaDoesNotEndWithCloseParanthesis)
    {
        ASSERT_THROW(ArgsParser parser("(f", EmptyArgs), SchemaMustStartAndEndWithParenthesisException);
    }

    /** Although empty schema is allowed, empty schema with arguments to parse is forbidden. */
    TEST_F(AnUnhappyTest, ThrowsWhenSchemaIsEmptyAndThereAreArguments)
    {
        const string ArgumentNotInSchema{"-x"};
        const string SchemaIsEmpty{"()"};

        ASSERT_THROW(ArgsParser parser(SchemaIsEmpty, { ArgumentNotInSchema }), ArgumentNotPartOfSchemaException);
    }

    TEST_F(AnUnhappyTest, ThrowsWhenArgumentIsNotPartOfSchema)
    {
        const string ArgumentNotInSchema{"-x"};
        const string Schema{"(d,f)"};

        ASSERT_THROW(ArgsParser (Schema, { ArgumentNotInSchema }), ArgumentNotPartOfSchemaException);
    }

    TEST_F(AnUnhappyTest, ThrowsOnInvalidSchemaCharacter)
    {
        const string schema{"(fd)"};
        ASSERT_THROW(ArgsParser(schema, EmptyArgs), SchemaInvalidCharacterDetectedException);
    }

    TEST_F(AnUnhappyTest, ThrowsWhenIntegerFlagIsMissingValue)
    {
        ASSERT_THROW(ArgsParser("(f#)", {"-f"}), MissingArgumentValueException);
    }
}