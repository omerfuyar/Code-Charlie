#pragma once

#include "Maths/Vectors.h"

//
typedef struct TFTDisplay TFTDisplay;

//
TFTDisplay* TFTDisplay_Create(int DC_PIN, int CS_PIN, int RST_PIN);

//
void TFTDisplay_Clear(TFTDisplay* display);

//
void TFTDisplay_DrawPixel(TFTDisplay* display, Vector2Int position, Vector3 color);

//
void TFTDisplay_DrawTriangle(TFTDisplay* display, Vector2Int point1, Vector2Int point2, Vector2Int point3);

//
void TFTDisplay_DrawText(TFTDisplay* display, Vector2Int position, Vector3 color);

