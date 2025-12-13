#ifndef STRINGBUILDER_HPP
# define STRINGBUILDER_HPP

# include <string>
# include <sstream>

class StringBuilder {
private:
    std::string _str;

public:
    StringBuilder();
    ~StringBuilder();

    StringBuilder& append(std::string text);
    StringBuilder& appendInt(int num);
    StringBuilder& clear();
    std::string    toString() const;
};

#endif
