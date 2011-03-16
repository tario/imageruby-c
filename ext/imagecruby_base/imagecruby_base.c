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
ID id_to_s, id_pixel_data;
ID id_width, id_height;

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
	for (y_ = 0; y_ < image_height; y_++) {

		memcpy(self_pixel_data, image_pixel_data, image_width*3);

		self_pixel_data += (self_width * 3);
		image_pixel_data += (image_width * 3);

	}

	return self;

}

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

	self_pixel_data += (x + y * self_width) * 3;

	int y_;
	for (y_ = 0; y_ < image_height; y_++) {

		memcpy(self_pixel_data, image_pixel_data, image_width*3);

		self_pixel_data += (self_width * 3);
		image_pixel_data += (image_width * 3);

	}

	return self;
}

extern void Init_imagecruby_base() {
	m_ImageRuby = rb_define_module("ImageRuby");
	c_ImageRuby_Image = rb_define_class_under(m_ImageRuby, "Image", rb_cObject);

	rb_define_method(c_ImageRuby_Image, "c_draw", c_draw, 3);
	rb_define_method(c_ImageRuby_Image, "c_draw_with_mask", c_draw_with_mask, 4);

	id_to_s = rb_intern("to_s");
	id_pixel_data = rb_intern("pixel_data");

	id_width = rb_intern("width");
	id_height = rb_intern("height");
}
