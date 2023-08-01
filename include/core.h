#pragma once

// cpp
#include <string>
#include <map>
#include <set>
#include <optional>
#include <fstream>
#include <filesystem>
#include <map>

// plog
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Log.h>

// glad
#include <glad/glad.h>

// opengl
#include <GLFW/glfw3.h>


// Constants declaration
namespace ugly
{
	static const std::string LOG_FILENAME = "UglyEngine.log";
}