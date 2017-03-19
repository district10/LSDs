lsd  := build/bin/Release/lsd
elsd := build/bin/Release/elsd
svgm := build/bin/Release/svgMarker

all: pano.pgm.lsd.txt pano.pgm.elsd.txt pano.pgm.elsd.svg.marked.svg pano.pgm.lsd.svg.marked.svg
clean:
	rm -f pano.pgm.lsd.* pano.pgm.elsd.*

pano.pgm: pano.jpg
	convert $< $@

pano.pgm.lsd.txt: pano.pgm
	${lsd} -S pano.pgm.lsd.svg -W 1.0 $< $@
pano.pgm.elsd.txt: pano.pgm
	${elsd} $<

%.marked.svg: %
	${svgm} $< $@
