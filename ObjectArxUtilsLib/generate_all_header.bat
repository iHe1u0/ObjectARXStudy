# This file will generate all header of utils in "objectarxutilslib.h"
# Run this script by double click bat file

del objectarxutilslib.h
echo #pragma once >> objectarxutilslib.h
for %%h in (C*.h) do echo #include ^"%%h^" >> objectarxutilslib.h