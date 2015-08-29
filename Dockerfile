FROM ubuntu
RUN apt-get -y update
RUN apt-get -y install gcc
RUN mkdir /server
ADD . /server
WORKDIR /server
RUN gcc ./server.c
RUN chmod a+x ./a.out
EXPOSE 65535
CMD ["./a.out"]

