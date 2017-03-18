lsd := build/bin/Release/lsd
elsd := build/bin/Release/elsd

all: pano.pgm.lsd.txt pano.pgm.elsd.txt
clean:
	rm -f pano.pgm.lsd.* pano.pgm.elsd.*

pano.pgm: pano.jpg
	convert $< $@

pano.pgm.lsd.txt: pano.pgm
	${lsd} -S pano.pgm.lsd.svg $< $@
pano.pgm.elsd.txt: pano.pgm
	${elsd} $<


