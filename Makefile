#Makefile pro IJC-DU2
#Jakub Čoček (xcocek00), FIT

CC = gcc
CFLAGS = -g -O2 -std=c11 -pedantic -Wall -Wextra

all: tail wordcount libhtab.a wordcount-dynamic libhtab.so 

############## SPUSTITELNE SOUBORY ##############
tail: tail.o 
	$(CC) $(CFLAGS) tail.o -o tail

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o wordcount -static wordcount.o io.o -L. -lhtab

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.o io.o -L. -lhtab

############## KNIHOVNY ############## 
libhtab.a: htab_init.o htab_size.o htab_bucket_count.o htab_clear.o htab_hash_function.o htab_free.o htab_find.o htab_resize.o htab_lookup_add.o htab_erase.o htab_for_each.o
	ar rcs libhtab.a htab_init.o htab_size.o htab_bucket_count.o htab_clear.o htab_hash_function.o htab_free.o htab_find.o htab_resize.o htab_lookup_add.o htab_erase.o htab_for_each.o

libhtab.so: htab_init.o htab_size.o htab_bucket_count.o htab_clear.o htab_hash_function.o htab_free.o htab_find.o htab_resize.o htab_lookup_add.o htab_erase.o htab_for_each.o
	$(CC) -shared -fPIC htab_init.o htab_size.o htab_bucket_count.o htab_clear.o htab_hash_function.o htab_free.o htab_find.o htab_resize.o htab_lookup_add.o htab_erase.o htab_for_each.o -o libhtab.so

############## NEKNIHOVNI .o SOUBORY ##############
tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

############## .o SOUBORY PRO KNIHOVNY ##############
wordcount.o: wordcount.c htab.h io.h
	$(CC) $(CFLAGS) -c -fPIC wordcount.c

htab_init.o: htab_init.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_init.c

htab_size.o: htab_size.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_size.c

htab_bucket_count.o: htab_bucket_count.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_bucket_count.c

htab_clear.o: htab_clear.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_clear.c

htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS) -c -fPIC htab_hash_function.c

htab_free.o: htab_free.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_free.c

htab_find.o: htab_find.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_find.c

htab_resize.o: htab_resize.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_resize.c

htab_lookup_add.o: htab_lookup_add.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_lookup_add.c

htab_erase.o: htab_erase.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_erase.c

htab_for_each.o: htab_for_each.c htab.h htab_private.h
	$(CC) $(CFLAGS) -c -fPIC htab_for_each.c

############## CLEAN ##############
clean:
	$(RM) *.o tail wordcount libhtab.a wordcount-dynamic libhtab.so
