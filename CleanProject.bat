@echo off
echo Cleaning Project Intermediate and Binaries...

rd /s /q "Binaries"
rd /s /q "Intermediate"
rd /s /q "Saved"
rd /s /q "DerivedDataCache"

rd /s /q "Plugins\McpAutomationBridge\Binaries"
rd /s /q "Plugins\McpAutomationBridge\Intermediate"

echo.
echo Clean Finished.
echo Please right-click 'ECHO.uproject' and select 'Generate Visual Studio project files'.
echo Then open 'ECHO.sln' and build via Visual Studio (Ctrl+Shift+B).
echo OR simply launch the game again and select 'Yes' to rebuild.
pause
