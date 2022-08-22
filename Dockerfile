FROM nginx:alpine

COPY out/. /usr/share/nginx/html
COPY ./nginx.conf /etc/nginx/nginx.conf