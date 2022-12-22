#ifndef RENDERING_H
#define RENDERING_H

#include "Texture.h"
#include "Grid.h"

void RenderStartSurface();

void RenderMenu();

void RenderSelect(int[]);

void RenderSetting(bool);

void RenderGame(int);

void RenderGame(int, int);

void RenderRoles();

void RenderResult();

void RenderPause();

void RenderTutorial();

void ShowAlert();

#endif // RENDERING_H
