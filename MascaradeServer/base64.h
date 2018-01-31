#ifndef _BASE64_H_
#define _BASE64_H_
#include <string>
extern std::string base64_encode(const std::string& bindata);
extern std::string base64_decode(const std::string& ascdata);
#endif 