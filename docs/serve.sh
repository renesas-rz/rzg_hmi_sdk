#!/usr/bin/env bash

# serve.sh
# To serve webpage at yours local ip with port=8000

ip=$(hostname -I | awk '{print $1}')
port=8000

address=$ip:$port

mkdocs serve -a $address
