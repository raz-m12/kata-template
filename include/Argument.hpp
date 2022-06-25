#ifndef Argument_hpp
#define Argument_hpp

#include <iostream>


namespace argskata {
   namespace lib {
      namespace impl {
         using namespace std;

         enum ArgumentType
         {
            _boolean,
            _integer,
            _string
         };

         class Argument
         {
            public:
            Argument(const string& name, ArgumentType type);
            bool operator==(const Argument& other) const;
            bool operator!=(const Argument& other) const;

            private:
            string name_;
            ArgumentType type_;
         };
      }
      using impl::ArgumentType;
      using impl::Argument;
   }
}




#endif