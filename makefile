
all : moteurJeu

clean :
	rm *.o moteurJeu


moteurJeu: Vect3D.o moteurJeu.o
	$(CXX) -o moteurJeu Vect3D.o moteurJeu.o


Vect3D.o: Vect3D.cpp
	$(CXX) -c Vect3D.cpp

moteurJeu.o: moteurJeu.cpp
	$(CXX) -c moteurJeu.cpp
