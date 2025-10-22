#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

class NestedInteger
{
public:
    NestedInteger() : is_integer(false) {}
    NestedInteger(int value) : is_integer(true), integer_value(value) {}

    bool isInteger() const
    {
        return is_integer;
    }

    int getInteger() const
    {
        return integer_value;
    }

    const std::vector<NestedInteger> &getList() const
    {
        return list_value;
    }

    void add(const NestedInteger &ni)
    {
        list_value.push_back(ni);
    }

private:
    bool is_integer;
    int integer_value;
    std::vector<NestedInteger> list_value;
};

NestedInteger parseNestedInteger(const std::string &s, int &index)
{
    NestedInteger result;
    if (s[index] == '[')
    {
        ++index; // skip the '['
        while (s[index] != ']')
        {
            result.add(parseNestedInteger(s, index));
            if (s[index] == ',')
                ++index; // skip the ','
        }
        ++index; // skip the ']'
    }
    else
    {
        int start = index;
        while (index < s.size() && (isdigit(s[index]) || s[index] == '-'))
        {
            ++index;
        }
        int number = std::stoi(s.substr(start, index - start));
        result = NestedInteger(number);
    }
    return result;
}

std::vector<NestedInteger> buildNestedList(const std::string &input)
{
    std::vector<NestedInteger> nestedList;
    int index = 0;
    nestedList.push_back(parseNestedInteger(input, index));
    return nestedList;
}

int depthSumInverse(vector<NestedInteger> &nestedList)
{
}

int main()
{
    std::string input = "[1,[4,[6]]]";
    std::vector<NestedInteger> nestedList = buildNestedList(input);

    int result = depthSumInverse(nestedList);
    std::cout << "Depth Sum Inverse: " << result << std::endl;

    std::string input2 = "[[1,1],2,[1,1]]";
    std::vector<NestedInteger> nestedList2 = buildNestedList(input2);

    int result2 = depthSumInverse(nestedList2);
    std::cout << "Depth Sum Inverse: " << result2 << std::endl;

    return 0;
}