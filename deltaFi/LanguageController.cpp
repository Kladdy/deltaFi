#include "stdafx.h"
#include "LanguageController.h"
#include <map>
#include "en_US.h"
#include "sv_SE.h"

std::map<std::string, LanguageController::languageStruct> loadedLanguages;

bool LanguageController::selectLanguage(std::string languageString)
{
	for (std::string supported_language : supportedLanguages)
	{
		if (languageString == supported_language) {
			selectedLanguage = loadedLanguages[languageString];
			return true;
		}
	}

	return false;
}

LanguageController::LanguageController()
{
	sv_SE Swedish;
	loadedLanguages["sv_SE"] = Swedish.lang;
	supportedLanguages.push_back("sv_SE");

	en_US English;
	loadedLanguages["en_US"] = English.lang;
	supportedLanguages.push_back("en_US");
}


LanguageController::~LanguageController()
{
}
