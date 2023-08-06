#pragma once

#include "core.h"

namespace ugly
{

	class display_manager
	{
	public:

		enum class polygon_mode : uint32_t
		{
			POINT = 6912,
			LINE = 6913,
			FILL = 6914
		};

		/**
		 * @brief Constructor.
		 */
		display_manager();

		/**
		 * @brief Destructor.
		 */
		virtual ~display_manager();


		/**
		 * @brief Set the viewport.
		 * 
		 * @param x     left corner
		 * @param y     lower corner
		 * @param width     width
		 * @param height    height
		 */
		void set_viewport(int x, int y, unsigned int width, unsigned height);

		/**
		 * @brief Specify clear values for the color buffers.
		 *
		 * @param red      red value
		 * @param green    green value
		 * @param blue     blue value
		 * @param alpha    alpha value
		 */
		void set_clear_color(float red, float green, float blue, float alpha);

		/**
		 * @brief Clear buffers to preset values.
		 */
		void clear();

		/**
		 * @brief Select a polygon rasterization mode.
		 *
		 * @param mode Specifies how polygons will be rasterized
		 */
		void set_polygon_mode(polygon_mode mode);

		/**
         * @brief Render primitives from array data.
         * 
		 * @param first    Starting index
		 * @param count    Number of indices to render 
         */
		void draw_arrays(int32_t first, uint32_t count);

		/**
		 * @brief Render primitives from array data with index buffer.
		 *
		 * @param count    Number of elements to be rendered. If 0 the full index buffer is used
		 */
		void draw_elements(uint32_t count = 0);
	};

}