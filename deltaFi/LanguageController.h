#pragma once
#include <string>
#include <vector>

using namespace std;

class LanguageController
{
public:
	struct languageStruct
	{
		string name;
		string code;

		string particle;
		string planetary;
		string pendulum;
		string swing;

		string exit;
	};
	bool selectLanguage(std::string languageString);
	vector<string> supportedLanguages;
	languageStruct selectedLanguage;
	LanguageController();
	~LanguageController();
};
