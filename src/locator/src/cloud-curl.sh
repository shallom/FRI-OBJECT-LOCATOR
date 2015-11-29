#!/bin/bash

img_url=$1
key=DhJLTpx-xP1qYKq75WIhvQ

curl -i -X POST \
-H "Authorization: CloudSight $key" \
-F "image_request[image]=@$img_url" \
-F "image_request[locale]=en-US" \
https://api.cloudsightapi.com/image_requests
<<<<<<< HEAD
=======



>>>>>>> ae970284b0628773f528b5ac7a9ad9b1a7b74f45
