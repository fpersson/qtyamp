#include "commandparser.h"

CommandParser::CommandParser(){
}

/**
 * @brief CommandParser::parse
 * @param string
 * @param delimiter
 * @param cmdOut
 * @return true is parse works else false.
 */
bool CommandParser::parse(const QString &string, const QString &delimiter, Command &cmdOut){
    QStringList list;
    list = string.split(delimiter);
    if(list[0] == string){
        utils::FQLog::getInstance().info("CommandParser", "ERROR: bad command string: "+string);
        return false;
    }else{
        cmdOut.cmd = list[0];
        cmdOut.value = list[1];
        return true;
    }
}
