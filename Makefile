CC = gcc
CFLAGS = -W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`
INCLUDE = -Iinclude

all : main gen_fic_alea_donnees

main : main.o allocation.o gest_err.o etape1.o etape2.o etape3.o etape5.o arbre_kd.o
			 $(CC) $(INCLUDE) $(CFLAGS) $(LDFLAGS) main.o allocation.o gest_err.o etape1.o etape2.o etape3.o etape5.o arbre_kd.o $(LDLIBS) -o exec/main

gen_fic_alea_donnees : gen_fic_alea_donnees.o gest_err.o
											 $(CC) $(CFLAGS) gen_fic_alea_donnees.o gest_err.o -o exec/gen_fic_alea_donnees

gen_fic_alea_donnees.o : gen_fic_alea_donnees.c
												 $(CC) $(INCLUDE) $(CFLAGS) gen_fic_alea_donnees.c -c

arbre_kd.o : arbre_kd.c
						 $(CC) $(INCLUDE) $(CFLAGS) arbre_kd.c -c

main.o : main.c
				 $(CC) $(INCLUDE) $(CFLAGS) main.c -c

etape5.o : etape5.c
					 $(CC) $(INCLUDE) $(CFLAGS) etape5.c -c

etape3.o : etape3.c
					 $(CC) $(INCLUDE) $(CFLAGS) -lm etape3.c -c

etape2.o : etape2.c
					 $(CC) $(INCLUDE) $(CFLAGS) -lm etape2.c -c

etape1.o : etape1.c
					 $(CC) $(INCLUDE) $(CFLAGS) etape1.c -c

allocation.o : allocation.c
							 $(CC) $(INCLUDE) $(CFLAGS) allocation.c -c

gest_err.o : gest_err.c
						 $(CC) $(INCLUDE) $(CFLAGS) gest_err.c -c

clean :
			 rm -f *~ *.o exec/*
