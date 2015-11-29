#!/bin/bash

token=$1

curl -i \
-H "Authorization: CloudSight DhJLTpx-xP1qYKq75WIhvQ" \
https://api.cloudsightapi.com/image_responses/$token
