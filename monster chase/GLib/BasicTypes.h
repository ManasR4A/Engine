#pragma once

#include <stdint.h>

namespace GLib
{
	struct Point2D
	{
		float			x;
		float			y;
		Point2D(float i_x = 0, float i_y = 0) :
			x(i_x), y(i_y) {}
	};

	struct UV
	{
		float			u, v;
		UV(float i_U = 0, float i_V = 0) :
			u(i_U), v(i_V) {}

		void Normalize(float i_TexW, float i_TexH)
		{
			u /= i_TexW;
			v /= i_TexH;
		}
	};

	struct RGBA
	{
		uint8_t			r, g, b, a;
	};

	typedef struct _SpriteEdges
	{
		float			Left;
		float			Top;
		float			Right;
		float			Bottom;
	} SpriteEdges;

	typedef struct _SpriteUVs
	{
		UV				TopLeft;
		UV				TopRight;
		UV				BottomLeft;
		UV				BottomRight;

		void Normalize(float i_TexW, float i_TexH)
		{
			TopLeft.Normalize(i_TexW, i_TexH);
			TopRight.Normalize(i_TexW, i_TexH);
			BottomLeft.Normalize(i_TexW, i_TexH);
			BottomRight.Normalize(i_TexW, i_TexH);
		}
	} SpriteUVs;
} // namespace GLib