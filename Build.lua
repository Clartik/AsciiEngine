-- premake5.lua
workspace "AsciiEngine"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Sandbox"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "AsciiEngine"
	include "AsciiEngine/Build-Engine.lua"
group ""

include "Sandbox/Build-Sandbox.lua"