CC=icc

MINUIT_PATH=/home/dfslezak/Minuit2/
MVAPICH_INCLUDE_PATH=/usr/local/mvapich2/include
MVAPICH_LIB_PATH=/usr/local/mvapich2/lib

# Intel compilation options
CFLAGS=-c -O2 -I$(MVAPICH_INCLUDE_PATH) -D_EM64T_ -D_SMP_ -DUSE_HEADER_CACHING -DONE_SIDED -DMPIDI_CH3_CHANNEL_RNDV -DMPID_USE_SEQUENCE_NUMBERS -DRDMA_CM
LDFLAGS=-O2 -L$(MVAPICH_LIB_PATH) -lmpichcxx -lmpich -L/usr/lib64 -lstdc++ -lrdmacm -libverbs -libumad -lpthread 


SOURCES=main.cpp Network.cpp Population.cpp PopulationDescr.cpp Protocol.cpp Neuron.cpp Event.cpp rando2.cpp Synapse.cpp SynPopDescr.cpp utils.cpp Connection.cpp Receptor.cpp randgen.cpp r250.cpp registrar.cpp rndlcg.cpp
OBJECTS=$(SOURCES:.cpp=.o)
WINDOWS_OBJECTS=$(SOURCES:.cpp=.obj)

EXEC=az.out

all: az

az: $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

.c.o:;
	$(CC) -c $<    $(CFLAGS)

.cpp.o:;
	$(CC) -c $<    $(CFLAGS)

clean:
	@rm -f $(EXEC)
	@rm -f *.o

WINDOWS_CFLAGS=-c -O2 -D__NO_MPI -DBITS=31 -Wall -w
WINDOWS_LDFLAGS=-O2 -w

windows:
	icl $(WINDOWS_CFLAGS) $(SOURCES)
	icl $(WINDOWS_LDFLAGS) $(WINDOWS_OBJECTS)
	
#gmake windows