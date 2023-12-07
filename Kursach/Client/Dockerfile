FROM gcc
WORKDIR /code
COPY . /code
RUN make client
EXPOSE 4001
CMD ["./client"]
