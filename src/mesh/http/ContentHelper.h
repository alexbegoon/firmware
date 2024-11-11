#pragma once

#include <Arduino.h>
#include <functional>

/**
 * @brief Replaces all occurrences of a substring with another substring.
 *
 * @param str The original string.
 * @param from The substring to be replaced.
 * @param to The substring to replace with.
 */
void replaceAll(String &str, const String &from, const String &to);
