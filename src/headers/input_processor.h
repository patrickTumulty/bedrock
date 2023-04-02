//
// Created by Patrick Tumulty on 5/17/22.
//

#ifndef RHC_INPUTPROCESSOR_H
#define RHC_INPUTPROCESSOR_H

#include "arg_processor.h"
#include <string>
#include <vector>
#include <queue>

class InputProcessor
{
public:
    explicit InputProcessor(std::vector<ArgProcessor> processors);
    int processInputs(int argc, char *argv[]);

    void addDefaultHelpArgProcessor();
    [[nodiscard]] int getDescriptionLineLength() const;

    void setDescriptionLineLength(int length);

    void setHelperHeader(const std::string &header);
    void setHelperFooter(const std::string &footer);

    [[nodiscard]] const std::vector<std::string> &getUnusedInputArgs() const;

private:
    std::vector<ArgProcessor> argProcessors;
    std::queue<ArgProcessor> flagQueue;
    std::queue<ArgProcessor> actionQueue;
    std::vector<std::string> unusedInputArgs;
    int descMaxLengthInCharacters;
    std::string helperHeader;
    std::string helperFooter;
    int helperTextCharacterLength;

    int processArguments();
    void addProcessorToFlagQueue(const std::string &currentArg,
                                 ArgProcessor &processor,
                                 std::vector<std::string> &clearList);

    void addProcessorToActionQueue(const std::vector<std::string> &inputArgs,
                                   int currentIndex,
                                   std::vector<std::string> &clearList,
                                   ArgProcessor &processor);
    void parseInputToArgProcessors(std::vector<std::string> &inputArgs);
    int doProcessArguments();

    void printWithWrapping(const std::string &text) const;
};


#endif //RHC_INPUTPROCESSOR_H
