CC		= g++
C		= cpp
H		= h
CFLAGS		= -g

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -ltiff -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lGLU -ltiff -lm
  endif
endif

OBJS 		= main.o

PROJECT		= rgbcube

${PROJECT} : ${OBJS} 
	${CC} ${CFLAGS} -o ${PROJECT} ${OBJS}  ${LDFLAGS} 

${PROJECT}.o    : main.${C}
	${CC} ${CFLAGS} -c main.${C}


clean:
	rm -f core.* *.o *~ ${PROJECT}
