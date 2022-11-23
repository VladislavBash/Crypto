#include <string>
#include <map>

extern std::map<std::string, int> chooseMap(std::string lang);
extern std::map<int, std::string> chooseUnMap(std::string lang);
extern int translate(std::string a, std::string lang);
extern std::string untranslate(int a, std::string lang);