//
// Created by Patrick Tumulty on 5/17/22.
//

#ifndef RHC_ARGPROCESSOR_H
#define RHC_ARGPROCESSOR_H

#include <string>
#include <vector>

#define ARG_PROCESSOR_FLAG 0
#define ARG_PROCESSOR_FINAL (-1)

class ArgProcessor
{
public:
    ArgProcessor(std::string arg, std::string shortArg, std::string description, int numberOfArgs, std::function<int(std::vector<std::string>)> action);
    int process();
    void setArgumentValues(const std::vector<std::string> &values);

    [[nodiscard]] const std::string &getArgName() const;
    [[nodiscard]] const std::string &getShortArgName() const;
    [[nodiscard]] bool isFinal() const;
    [[nodiscard]] bool isFlag() const;
    [[nodiscard]] int getExpectedNumberOfArgs() const;
    [[nodiscard]] const std::string &getDescription() const;

private:
    std::function<int(std::vector<std::string>)> action;
    std::vector<std::string> argumentValues;
    std::string argName;
    std::string shortArgName;
    std::string description;
    int expectedNumberOfArgs;
};


#endif //RHC_ARGPROCESSOR_H
