#include "mesh/http/ContentHelper.h"

/**
 * @brief Replaces all occurrences of a substring with another substring in the given string.
 *
 * @param str The original string.
 * @param from The substring to be replaced.
 * @param to The substring to replace with.
 */
void replaceAll(String &str, const String &from, const String &to)
{
    int start_pos = 0;
    while ((start_pos = str.indexOf(from, start_pos)) != -1) {
        str.replace(from, to);
        start_pos += to.length();
    }
}
