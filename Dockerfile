FROM ubuntu
RUN apt-get -y update
RUN mkdir /server
ADD . /server
WORKDIR /server
RUN gcc ./server.c
RUN chmod a+x ./a.out
EXPOSE 65535
CMD ["./a.out"]

