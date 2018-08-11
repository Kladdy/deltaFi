#pragma once
#include "LanguageController.h"

class en_US
{
public:
	LanguageController::languageStruct lang{};

	en_US()
	{
		this->lang.name = "English";
		this->lang.code = "EN";

		this->lang.particle = "Particle";
		this->lang.planetary = "Planetary";
		this->lang.pendulum = "Pendulum";
		this->lang.swing = "Swing";
		this->lang.exit = "Exit";
	}
};

