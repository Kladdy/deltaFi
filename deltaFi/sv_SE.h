#pragma once
#include "LanguageController.h"

class sv_SE
{
public:
	LanguageController::languageStruct lang{};

	sv_SE()
	{
		this->lang.name = "Svenska";
		this->lang.code = "SV";

		this->lang.particle = "Partikel";
		this->lang.planetary = "Planetarium";
		this->lang.pendulum = "Pendel";
		this->lang.swing = "Gunga";
		this->lang.exit = "Avlägsna";
	}
};

