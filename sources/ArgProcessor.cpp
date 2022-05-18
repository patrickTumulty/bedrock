//
// Created by Patrick Tumulty on 5/17/22.
//

#include "ArgProcessor.h"

#include <utility>

/**
 * Constructor
 *
 * @Info An ArgProcessor is used to process a single command line argument. This class provides the option to set both
 * a regular and short form of the string argument. An ArgProcessor can be normal, flag or final. These behaviors are
 * determined by the number of args that the ArgProcessor expects. Passing 0 (ARG_PROCESSOR_FLAG) for numberOfArgs
 * defines this ArgProcessor as a flag. It will not evaluate any values and will be processed first. Additionally, flag
 * arguments only get matched to the beginning of the input string. Example: Flag '--flag' will be matched with input
 * arg '--flag=1'. Flags are ideal for setting global variables before the normal, and final ArgProcessors are
 * processed. Passing -1 (ARG_PROCESSOR_FINAL) for the numberOfArgs defines this ArgProcessor as final. This means that
 * the processor will evaluate an undefined number of argument values. All string values that come after a final
 * ArgProcessor will be passed as values to the ArgProcessor action.
 *
 * @param arg argument name
 * @param shortArg short argument name. Can be an empty string
 * @param numberOfArgs the number of args that this ArgProcessor expects. (See Info)
 * @param action the action to perform for this arg processor. Action should return 0 if successful.
 */
ArgProcessor::ArgProcessor(std::string arg,
                           std::string shortArg,
                           int numberOfArgs,
                           std::function<int(std::vector<std::string>)> action) : argName(std::move(arg)),
                                                                                  shortArgName(std::move(shortArg)),
                                                                                  expectedNumberOfArgs(numberOfArgs),
                                                                                  action(std::move(action))
{
    // Empty
}

/**
 * @return The argument name
 */
const std::string &ArgProcessor::getArgName() const
{
    return argName;
}

/**
 * @return The short argument name
 */
const std::string &ArgProcessor::getShortArgName() const
{
    return shortArgName;
}

/**
 * @return true if this ArgProcessor is final
 */
bool ArgProcessor::isFinal() const
{
    return expectedNumberOfArgs == ARG_PROCESSOR_FINAL;
}

/**
 * @return true if this ArgProcessor is a flag
 */
bool ArgProcessor::isFlag() const
{
    return expectedNumberOfArgs == ARG_PROCESSOR_FLAG;
}

/**
 * Set the argument values. These values are passed to the ArgProcessor action
 *
 * @param values values to process
 */
void ArgProcessor::setArgumentValues(const std::vector<std::string> &values)
{
    argumentValues = values;
}

/**
 * Do process
 *
 * @return 0 if successful
 */
int ArgProcessor::process()
{
    return action(argumentValues);
}

/**
 * @return the expected number of arguments
 */
int ArgProcessor::getExpectedNumberOfArgs() const
{
    return expectedNumberOfArgs;
}






