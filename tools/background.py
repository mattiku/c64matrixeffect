#!/usr/bin/python

# A simple tool for creating two colour hexadecimal presentation from
# a given image file content. 
#
# All black (#000000) pixels in given image unsets a bit and pixels with
# any other colour value sets a bit in output data.
#
# Author: Matti Kuonanoja (2015)

import sys
from PIL import Image

CHAR_WIDTH_IN_PIXELS = 8
CHAR_HEIGHT_IN_PIXELS = 8

def get_background_bytes(file_path, table_width, table_heigth):
    image = Image.open(file_path)
    image_size_x, image_size_y = image.size

    byte_table = [[0 for i in xrange(table_heigth)] for i in xrange(table_width)]

    for byte_y in range(table_heigth):
        output_text = ""
        for byte_x in range(table_width):
            byte = 0x00;
            for bit in range(8):
                pixel_x = byte_x * 8 + bit
                pixel_y = byte_y

                is_bright_pixel = False
                if pixel_x < image_size_x and pixel_y < image_size_y:
                    rr, gg, bb = image.getpixel((pixel_x,pixel_y))
                    if rr != 0 or gg != 0 or bb != 0:
                        is_bright_pixel = True

                if is_bright_pixel:
                    output_text = output_text + "*"
                    byte = byte | (1 << bit)
                else:
                    output_text = output_text + " "

            byte_table[byte_x][byte_y] = byte
        print output_text

    return byte_table

def write_background_bytes_to_file(file_path, byte_table):
    table_width = len(byte_table)
    table_height = len(byte_table[0])

    file = open(file_path, 'w')
    file.write("static char background_image[] = {\n");
    for byte_y in range(table_height):
        file.write("    ")
        for byte_x in range(table_width):
            hexText = '0x{:02X}'.format(byte_table[byte_x][byte_y])
            file.write(hexText)
            if byte_x < table_width - 1 or byte_y < table_height - 1:
                file.write(", ")
        file.write("\n")
    file.write("};\n");
    file.close()

if __name__ == "__main__":

    if len(sys.argv) < 3:
        print "ERROR: Wrong number of arguments"
        print "usage: background.py <input_file> <output_file>"
        raise SystemExit

    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    byte_table_width = 8
    byte_table_height = 25

    bytes = get_background_bytes(input_file_name, byte_table_width, byte_table_height)
    write_background_bytes_to_file(output_file_name, bytes)
    print "Byte table written in a file: {0}".format(output_file_name)