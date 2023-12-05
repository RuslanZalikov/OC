for i in {1..1000}
do
	echo "Client $i up"
	./client
	sleep 0.1
done
