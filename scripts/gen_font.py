from sys import argv

from PIL import Image
ROWS = 14
COLS = 6
SRC_W = 8
SRC_H = 8
DST_W = 8
DST_H = 8

def makefont(ipath : str, opath : str):
    src = Image.open(ipath).convert("RGBA")
    glyph_count = ROWS * COLS
    dst = Image.new("RGBA", (DST_W, glyph_count * DST_H), (0, 0, 0, 0))

    for row in range(ROWS):
        for col in range(COLS):
            glyph = row * COLS + col
            srcx = col * SRC_W
            srcy = row * SRC_H

            bbox = (srcx, srcy, srcx + SRC_W, srcy + SRC_H)
            
            chari = src.crop(bbox)
            #_, _, _, alpha = chari.split()
            #char = Image.new("RGBA", chari.size, (0, 0, 0, 0));
            #char.putalpha(alpha)

            destx = 0
            desty = glyph * DST_H

            dst.paste(chari, (destx, desty))

    dst.save(opath)
    print(src)

if __name__ == "__main__":
    if len(argv) < 3:
        print("Usage: gen_font.py image_path output_image_path")
        exit(1)
    makefont(argv[1], argv[2])
