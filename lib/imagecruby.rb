=begin

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

=end
require "imagecruby_base"

module ImageRuby
  class Image
    def draw(x,y,image,mask_color=nil)
      if mask_color
        c_draw_with_mask(x,y,image,mask_color)
      else
        c_draw(x,y,image)
      end
    end

    def color_replace!(color1, color2)
      c_color_replace(color1, color2)
    end
  end
end
