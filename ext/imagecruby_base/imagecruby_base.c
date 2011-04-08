/*

This file is part of the imagecruby project, http://github.com/tario/imagecruby

Copyright (c) 2011 Roberto Dario Seminara <robertodarioseminara@gmail.com>

imagecruby is free software: you can redistribute it and/or modify
it under the terms of the gnu general public license as published by
the free software foundation, either version 3 of the license, or
(at your option) any later version.

imagecruby is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.  see the
gnu general public license for more details.

you should have received a copy of the gnu general public license
along with imagecruby.  if not, see <http://www.gnu.org/licenses/>.

*/
#include "ruby.h"

VALUE c_ImageRuby_Image;
VALUE m_ImageRuby;
ID id_to_s, id_pixel_data, id_alpha_data;
ID id_width, id_height, id_a;

VALUE c_color_replace(VALUE self, VALUE rb_color1, VALUE rb_color2) {
	VALUE rb_color1_string = rb_funcall(rb_color1, id_to_s, 0);
	const char* color1_string = RSTRING(rb_color1_string)->ptr;

	VALUE rb_color2_string = rb_funcall(rb_color2, id_to_s, 0);
	const char* color2_string = RSTRING(rb_color2_string)->ptr;

	int color2_alpha = INT2FIX( rb_funcall(rb_color2, id_a, 0) );

	int self_width = FIX2INT( rb_funcall(self, id_width, 0) );
	int self_height = FIX2INT( rb_funcall(self, id_height, 0) );

	VALUE rb_self_pixel_data = rb_funcall(self, id_pixel_data, 0);
	char* self_pixel_data = RSTRING(rb_self_pixel_data)->ptr;

	VALUE rb_self_alpha_data = rb_funcall(self, id_alpha_data, 0);
	char* self_alpha_data = RSTRING(rb_self_alpha_data)->ptr;

	int y_;
	int x_;
	for (y_ = 0; y_ < self_height; y_++) {

		for (x_ = 0; x_ < self_width; x_++) {

			if (
				self_pixel_data[x_*3] == color1_string[0] &&
				self_pixel_data[x_*3+1] == color1_string[1] &&
				self_pixel_data[x_*3+2] == color1_string[2]
				) {

				self_pixel_data[x_*3] = color2_string[0];
				self_pixel_data[x_*3+1] = color2_string[1];
				self_pixel_data[x_*3+2] = color2_string[2];
				self_alpha_data[x_] = color2_alpha;
			}
		}

		self_alpha_data += self_width;
		self_pixel_data += (self_width * 3);

	}

	return self;
}
/*
VALUE c_draw_with_mask(VALUE self, VALUE rb_x, VALUE rb_y, VALUE rb_image, VALUE rb_mask_color) {

	int x = FIX2INT(rb_x);
	int y = FIX2INT(rb_y);

	int image_width = FIX2INT( rb_funcall(rb_image, id_width, 0) );
	int image_height = FIX2INT( rb_funcall(rb_image, id_height, 0) );

	int self_width = FIX2INT( rb_funcall(self, id_width, 0) );
	int self_height = FIX2INT( rb_funcall(self, id_height, 0) );

	VALUE rb_color_string = rb_funcall(rb_mask_color, id_to_s, 0);
	const char* color_string = RSTRING(rb_color_string)->ptr;

	VALUE rb_image_pixel_data = rb_funcall(rb_image, id_pixel_data, 0);
	const char* image_pixel_data = RSTRING(rb_image_pixel_data)->ptr;

	VALUE rb_self_pixel_data = rb_funcall(self, id_pixel_data, 0);
	char* self_pixel_data = RSTRING(rb_self_pixel_data)->ptr;

	self_pixel_data += (x + y * self_width) * 3;

	int y_;
	int x_;
	for (y_ = 0; y_ < image_height; y_++) {

		for (x_ = 0; x_ < image_width; x_++) {

			if (
				image_pixel_data[x_*3] != color_string[0] ||
				image_pixel_data[x_*3+1] != color_string[1] ||
				image_pixel_data[x_*3+2] != color_string[2]
				) {

				self_pixel_data[x_*3] = image_pixel_data[x_*3];
				self_pixel_data[x_*3+1] = image_pixel_data[x_*3+1];
				self_pixel_data[x_*3+2] = image_pixel_data[x_*3+2];
			}
		}

		self_pixel_data += (self_width * 3);
		image_pixel_data += (image_width * 3);

	}

	return self;

}*/

VALUE c_draw(VALUE self, VALUE rb_x, VALUE rb_y, VALUE rb_image) {

	int x = FIX2INT(rb_x);
	int y = FIX2INT(rb_y);

	int image_width = FIX2INT( rb_funcall(rb_image, id_width, 0) );
	int image_height = FIX2INT( rb_funcall(rb_image, id_height, 0) );

	int self_width = FIX2INT( rb_funcall(self, id_width, 0) );
	int self_height = FIX2INT( rb_funcall(self, id_height, 0) );

	VALUE rb_image_pixel_data = rb_funcall(rb_image, id_pixel_data, 0);
	const char* image_pixel_data = RSTRING(rb_image_pixel_data)->ptr;

	VALUE rb_self_pixel_data = rb_funcall(self, id_pixel_data, 0);
	char* self_pixel_data = RSTRING(rb_self_pixel_data)->ptr;

	VALUE rb_self_alpha_data = rb_funcall(self, id_alpha_data, 0);
	char* self_alpha_data = RSTRING(rb_self_alpha_data)->ptr;

	self_alpha_data += (x + y * self.height);
	self_pixel_data += (x + y * self_width) * 3;

	int y_;
	int x_;
	for (y_ = 0; y_ < image_height; y_++) {

		for (x_ = 0; x_ < image_width; x_++) {

			int alpha = self_alpha_data[x_];
			if (alpha < 255) {
				if (alpha > 0) {
					self_pixel_data[x_*3] = ( self_pixel_data[x_*3]*(255-alpha) + image_pixel_data[x_*3]*alpha ) / 255;
					self_pixel_data[x_*3+1] = ( self_pixel_data[x_*3+1]*(255-alpha) + image_pixel_data[x_*3+1]*alpha ) / 255;
					self_pixel_data[x_*3+2] = ( self_pixel_data[x_*3+2]*(255-alpha) + image_pixel_data[x_*3+2]*alpha ) / 255;
				}
			} else {
				self_pixel_data[x_*3] = image_pixel_data[x_*3];
				self_pixel_data[x_*3+1] = image_pixel_data[x_*3+1];
				self_pixel_data[x_*3+2] = image_pixel_data[x_*3+2];
			}
		}

		self_alpha_data += self_width;
		self_pixel_data += (self_width * 3);
		image_pixel_data += (image_width * 3);

	}

	return self;
}

extern void Init_imagecruby_base() {
	m_ImageRuby = rb_define_module("ImageRuby");
	c_ImageRuby_Image = rb_define_module_under(m_ImageRuby, "ImageRubyCMixin");

	rb_define_method(c_ImageRuby_Image, "c_draw", c_draw, 3);
	rb_define_method(c_ImageRuby_Image, "c_color_replace", c_color_replace, 2);

	id_to_s = rb_intern("to_s");
	id_pixel_data = rb_intern("pixel_data");
	id_alpha_data = rb_intern("alpha_data");

	id_width = rb_intern("width");
	id_height = rb_intern("height");

	id_a = rb_intern("a");
}
