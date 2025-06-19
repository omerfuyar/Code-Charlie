#pragma once

#include "BaseGlobal.h"

/// @brief Initializes the application and sets up necessary resources.
/// This function is called at the start of the application lifecycle.
void App_Start();

/// @brief Performs additional setup after the main application start.
/// This function is called after `App_Start` to handle any late initialization tasks.
void App_StartLate();

/// @brief Updates the application state.
/// This function is called periodically to update the application logic.
void App_Update();

/// @brief Performs additional updates after the main application update.
/// This function is called after `App_Update` to handle any late update tasks.
void App_UpdateLate();

/// @brief Stops the application and releases resources.
/// @param exitCode The exit code to return when the application stops.
void App_Stop(int exitCode);