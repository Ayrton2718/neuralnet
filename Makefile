CC=gcc

all: main.out

neuralnet = NN_Layer.c
neuralnet += NN_Nerve.c
neuralnet += NN_Node.c
neuralnet += SC_Random.c

$(info neuralnet = $(neuralnet))

main.out : main.c $(neuralnet)
	 $(CC) -o $@  $^ -lpthread -Wall

%.o:%c
	$(CC) -c $<

clean:
	$(RM) *.o *.gch *.out *.so

