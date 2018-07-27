# Questions

## What's `stdint.h`?

It is a header file for  a library that allows for programmers to write more portable code, by providing a set of typedefs that allow you to
specify exact integer size.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

By declaring these types of integers, it makes it clear that you want to utilize the data in a certain way, whether it being strictly, 8, 32, 16,
or 24 bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE is 1 bytes, DWORD is 4 bytes, LONG is 4 bytes, and WORD is 2 bytes, respectively.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

the magic numbers are '0x' which must be the first two bytes of any BMP file
Hex:    0x424d
ASCII:  BM (bitmap!)
This value is stored in "bfType"

## What's the difference between `bfSize` and `biSize`?

bfSize is a variable assigned to the size of the BITMAPFILEHEADER, while biSize is a variable set to the BITMAPINFOHEADER size in the BMP file.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB with the origin at the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount;

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

NUll is a default value for FILE if it is not able to open

## Why is the third argument to `fread` always `1` in our code?

Because it specifies how many elements you want to read, and we're always
reading a struct, so we only need 1 struct.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3, because 3 pixels * 3 bytes per pixel * 3 padding = 12,
which is a multiple of 4. 12/4 = 3;

## What does `fseek` do?

It moves to a specific location is a file, in this case skipping over the padding

// skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

## What is `SEEK_CUR`?

An integer constant which, when used as the 'whence' argument to the
fseek or fseeko function, specifies that the offset provided is relative to
the current file position.
