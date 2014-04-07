hello: hello.c
	gcc hello.c `pkg-config --cflags --libs glib-2.0` -o hello
wordfreq: wordfreq.c
	gcc wordfreq.c `pkg-config --cflags --libs glib-2.0 gobject-2.0 gmodule-2.0` -g -Wall -o wordfreq