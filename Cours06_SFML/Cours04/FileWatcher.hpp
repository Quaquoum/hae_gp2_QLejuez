#pragma once
#include <iostream>
#include <optional>

#include "Turtle.hpp"

class FileWatcher
{
private:

	bool init = false;
	time_t lastChangedFile = 0;
	const char* filePath = nullptr;

public:

	float checktimer = 0;
	float checkCD = 0.2f;

	FileWatcher(const char* _filePath);
	~FileWatcher();

	bool checkFileModification(float dt);

	void appendCommandsFromFile(Turtle* entity);
};