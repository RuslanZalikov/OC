sudo docker rm client_container
sudo docker run --name client_container --network="host" -it client
