#ifndef LIBTOOLS_H
#define LIBTOOLS_H

#include <string>
#include <sstream>

using namespace std;

//Converts type T to string
template<class T>
    std::string toString(const T& t)
{
     std::ostringstream stream;
     stream << t;
     return stream.str();
}

//Converts from string to type T
template<class T>
    T fromString(const std::string& s)
{
     std::istringstream stream (s);
     T t;
     stream >> t;
     return t;
}

#endif // LIBTOOLS_H
