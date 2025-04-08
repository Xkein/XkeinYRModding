#pragma once
#include "yr/patch/syringe_hook.h"

void InitPatch();
void UninitPatch();

void ApplyModulePatch(HANDLE hInstance);
void RemoveModulePatch(HANDLE hInstance);
