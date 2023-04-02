//
// Created by Patrick Tumulty on 5/17/22.
//

#include "InputProcessor.h"

#include <utility>
#include "VectorUtils.h"
#include "StringUtils.h"

/**
 * Constructor
 *
 * @param processors ArgProcessor's
 */
InputProcessor::InputProcessor(std::vector<ArgProcessor> processors) : argProcessors(std::move(processors)),
                                                                       descMaxLengthInCharacters(45),
                                                                       helperTextCharacterLength(85)
{
    // Empty
}

/**
 * Process inputs
 *
 * @param argc argc
 * @param argv argv
 * @return 0 is successful
 */
int InputProcessor::processInputs(int argc, char **argv)
{
    std::vector<std::string> result;
    std::vector<std::string> inputArgs;
    for (int i = 0; i < argc; i++)
    {
        inputArgs.emplace_back(argv[i]);
    }

    parseInputToArgProcessors(inputArgs);

    return processArguments();
}

/**
 * Parse the given input arguments into ArgProcessors
 *
 * @param inputArgs input arg vectors
 */
void InputProcessor::parseInputToArgProcessors(std::vector<std::string> &inputArgs)
{
    std::vector<std::string> clearList;

    for (ArgProcessor processor : argProcessors)
    {
        for (int i = 0; i < inputArgs.size(); i++)
        {
            std::string currentArg = inputArgs[i];

            if (processor.getArgName() == currentArg ||
               (com::StringUtils::startsWith(processor.getShortArgName(), currentArg) &&
               !processor.getShortArgName().empty()))
            {
                if (processor.isFlag())
                {
                    addProcessorToFlagQueue(currentArg, processor, clearList);
                }
                else
                {
                    addProcessorToActionQueue(inputArgs, i, clearList, processor);
                }

                VectorUtils::removeCommon(&inputArgs, clearList);

                break;
            }
        }
    }

    unusedInputArgs = inputArgs;
}

/**
 * Add ArgProcessor to the action queue
 *
 * @param inputArgs input argument vector
 * @param currentIndex the current input args index
 * @param clearList vector to stored used arguments (eventually cleared from inputArgs)
 * @param processor target ArgProcessor
 */
void InputProcessor::addProcessorToActionQueue(const std::vector<std::string> &inputArgs,
                                               int currentIndex,
                                               std::vector<std::string> &clearList,
                                               ArgProcessor &processor)
{
    std::vector<std::string> values;
    int numberOfValues = processor.isFinal() ?
                         (int) (inputArgs.size() - currentIndex - 1) :
                         processor.getExpectedNumberOfArgs();
    for (int j = 1; j < numberOfValues + 1; j++)
    {
        const std::string& a = inputArgs[currentIndex + j];
        values.push_back(a);
        clearList.push_back(a);
    }
    processor.setArgumentValues(values);
    clearList.push_back(inputArgs[currentIndex]);
    actionQueue.push(processor);
}

/**
 * Add ArgProcessor to flag queue
 *
 * @param currentArg the current input argument string
 * @param processor target ArgProcessor
 * @param clearList vector to stored used arguments (eventually cleared from inputArgs)
 */
void InputProcessor::addProcessorToFlagQueue(const std::string &currentArg,
                                             ArgProcessor &processor,
                                             std::vector<std::string> &clearList)
{
    processor.setArgumentValues(std::vector<std::string>({currentArg}));
    clearList.push_back(currentArg);
    flagQueue.push(processor);
}

/**
 * Process the flag and action queues
 *
 * @return
 */
int InputProcessor::processArguments()
{
    try
    {
        return doProcessArguments();
    }
    catch (...)
    {
        return -1;
    }
}

/**
 * Do process arguments
 *
 * @return 0 is successful
 */
int InputProcessor::doProcessArguments()
{
    while (!flagQueue.empty())
    {
        int ret = flagQueue.front().process();
        if (ret != 0)
        {
            return ret;
        }
        flagQueue.pop();
    }

    while (!actionQueue.empty())
    {
        int ret = actionQueue.front().process();
        if (ret != 0)
        {
            return ret;
        }
        actionQueue.pop();
    }

    return 0;
}

/**
 * Get the unused input args. The string arguments that weren't matched to, or captured by, an ArgProcessor
 *
 * @return string vector of unused input args
 */
const std::vector<std::string> &InputProcessor::getUnusedInputArgs() const
{
    return unusedInputArgs;
}

/**
 * Get the arg processor descriptions max line length in characters before wrapping
 *
 * @return description line length characters
 */
int InputProcessor::getDescriptionLineLength() const
{
    return descMaxLengthInCharacters;
}

/**
 * Get the arg processor descriptions max line length in characters before wrapping
 *
 * @param length description line length
 */
void InputProcessor::setDescriptionLineLength(int length)
{
    InputProcessor::descMaxLengthInCharacters = length;
}

/**
 * Add the default help arg processor to the InputProcessor
 */
void InputProcessor::addDefaultHelpArgProcessor()
{
    argProcessors.emplace_back("--help", "", "Print help info", ARG_PROCESSOR_FLAG, [this](const std::vector<std::string>& values)
    {
        if (!helperHeader.empty())
        {
            printWithWrapping(helperHeader);
        }

        for (const ArgProcessor& processor : argProcessors)
        {
            int numberOfLines = (int) (processor.getDescription().length() / descMaxLengthInCharacters) + 1;
            for (int i = 0; i < numberOfLines; i++)
            {
                if (i == 0)
                {
                    printf("%7s%s %-18s : %-s\n",
                           processor.getShortArgName().c_str(),
                           processor.getShortArgName().empty() ? " " : ",",
                           processor.getArgName().c_str(),
                           processor.getDescription()
                                    .substr(descMaxLengthInCharacters * i,
                                            descMaxLengthInCharacters).c_str());
                }
                else
                {
                    printf("%27s   %-s\n", "",
                           processor.getDescription()
                                    .substr(descMaxLengthInCharacters * i,
                                            descMaxLengthInCharacters).c_str());
                }
            }
        }

        if (!helperFooter.empty())
        {
            printWithWrapping(helperFooter);
        }

        exit(0);
        return 0;
    });
}

/**
 * Print the input string with wrapping.
 *
 * @param text text
 */
void InputProcessor::printWithWrapping(const std::string &text) const
{
    for (const auto& line : com::StringUtils::split(text, "\n"))
    {
        for (int i = 0; i < (int) (line.length() / helperTextCharacterLength) + 1; i++)
        {
            printf("%s\n", line.substr(helperTextCharacterLength * i, helperTextCharacterLength).c_str());
        }
    }
}

/**
 * Header text add to the default --help arg processor. Header is printed before listing all the available args.
 *
 * @param header header text
 */
void InputProcessor::setHelperHeader(const std::string &header)
{
    InputProcessor::helperHeader = header;
}

/**
 * Footer text to add to the default --help arg processor. Footer is printed after listing all the available args.
 *
 * @param footer footer text
 */
void InputProcessor::setHelperFooter(const std::string &footer)
{
    InputProcessor::helperFooter = footer;
}
