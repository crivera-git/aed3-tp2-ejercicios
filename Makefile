CC = g++
CCFLAGS = -std=c++11
#-D_GLIBCXX_DEBUG
DEBUG = -g
CCFLAGSOPT = -O

#ejercicio-1
TARGET_1 = ejercicio_1
SOURCE_1 =  ejercicio-1/ejercicio_uno.cpp ejercicio-1/ejercicio_uno.h
MAIN_1 = ejercicio-1/main.cpp

#ejercicio_2
TARGET_2 = 	ejercicio_2
SOURCE_2 = ejercicio-2/ejercicio_dos.h ejercicio-2/ejercicio_dos.cpp
MAIN_2 = ejercicio-2/main.cpp
TARGET_2_test = ejercicio_2_test02
MAIN_2_test = ejercicio-2/tests/test_codigo.cpp
TARGET_EXP1 = gen_exp1
SOURCE_GEN1 = ejercicio-2/experimentacion/exp1_generador_instancias.cpp
TARGET_EXP2_BIPARTITO = gen_exp2_bipartito
SOURCE_GEN2_BIPARTITO = ejercicio-2/experimentacion/exp2_grafo_bipartito.cpp
TARGET_EXP2_DENSO = gen_exp2_denso
SOURCE_GEN2_DENSO = ejercicio-2/experimentacion/exp2_grafo_denso.cpp
TARGET_EXP2_ESPARZO = gen_exp2_esparzo
SOURCE_GEN2_ESPARZO = ejercicio-2/experimentacion/exp2_grafo_esparzo.cpp
TARGET_EXP2_ESTRELLA = gen_exp2_estrella
SOURCE_GEN2_ESTRELLA = ejercicio-2/experimentacion/exp2_grafo_estrella.cpp
TARGET_EXP2_TIEMPOS = gen_tiempos
SOURCE_TIEMPOS = ejercicio-2/experimentacion/tomar_tiempos.cpp
#ejercicio_3
TARGET_3 = ejercicio_3
SOURCE_3 = ejercicio-3/ejercicio_3.cpp

all: $(TARGET_1) $(TARGET_2) $(TARGET_3)

ejercicio_1:
	$(CC) $(CCFLAGSOPT) -o $(TARGET_1) $(SOURCE_1) $(MAIN_1)


ejercicio_2:
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
# ./ejercicio_2 < ejercicio-2/tests/test01.txt

ejercicio_2_tester:
	$(RM) $(TARGET_2)
	$(CC) $(CCFLAGS) -o $(TARGET_2) $(SOURCE_2) $(MAIN_2)
	./ejercicio_2 < ejercicio-2/tests/test03.txt

ej2_exp2_bipartito:
	$(CC) $(CCFLAGS) -o $(TARGET_EXP2_BIPARTITO) $(SOURCE_GEN2_BIPARTITO)

ej2_exp2_denso:
	$(CC) $(CCFLAGS) -o $(TARGET_EXP2_DENSO) $(SOURCE_GEN2_DENSO)

ej2_exp2_esparzo:
	$(CC) $(CCFLAGS) -o $(TARGET_EXP2_ESPARZO) $(SOURCE_GEN2_ESPARZO)

ej2_exp2_estrella:
	$(CC) $(CCFLAGS) -o $(TARGET_EXP2_ESTRELLA) $(SOURCE_GEN2_ESTRELLA)

ej2_tomar_tiempos:
	$(CC) $(CCFLAGS) -o $(TARGET_EXP2_TIEMPOS) $(SOURCE_TIEMPOS) $(SOURCE_2)

ejercicio_3:
	$(CC) $(CCFLAGSOPT) -o $(TARGET_3) $(SOURCE_3)

clean:
	$(RM) $(TARGET_1) $(TARGET_2) $(TARGET_3) $(TARGET_EXP2_DENSO) \
	$(TARGET_EXP2_ESPARZO) $(TARGET_EXP2_ESTRELLA) $(TARGET_EXP2_BIPARTITO)
