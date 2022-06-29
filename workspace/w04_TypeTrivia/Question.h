
#ifndef QUESTION_H_
#define QUESTION_H_

#include <string>


struct Question
{
    bool checkTypeT(std::string const & answer) const;
    bool checkTypeP(std::string const & answer) const;

    std::string const callingCode;
    std::string const calledCode;
    std::string const typeT;
    std::string const typeParamType;
};



#endif /* QUESTION_H_ */
