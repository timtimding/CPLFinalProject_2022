#ifndef RENDERING_H
#define RENDERING_H

#include "Texture.h"
#include "Grid.h"

void RenderStartSurface();

void RenderMenu();

void RenderSelect(int[]);

void RenderSetting(bool);

void RenderGame(int, uint32_t);

void RenderGame(int, int, uint32_t);

void RenderRoles();

void RenderResult(bool);

void RenderPause();

void RenderTutorial();

void ShowAlert();

#endif // RENDERING_H
