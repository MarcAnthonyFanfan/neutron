FROM alpine:latest
COPY . /neutron/
WORKDIR /neutron
RUN apk update
RUN apk add build-base
RUN apk add ncurses-dev
RUN gcc neutron.c -lncurses -o neutron
RUN cp ./neutron /bin/neutron

CMD ["/bin/neutron"]