FROM debian:bullseye

# Update et install Nginx + OpenSSL
RUN apt-get update && apt-get install -y \
	nginx \
	openssl \
	&& rm -rf /var/lib/apt/lists/*

# Crée certificat SSL auto-signé
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout /etc/ssl/private/nginx-selfsigned.key \
	-out /etc/ssl/certs/nginx-selfsigned.crt \
	-subj "/C=FR/ST=Paris/L=Paris/O=42/OU=Student/CN=localhost"

# Copie config Nginx custom
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Expose port HTTPS
EXPOSE 443

# Lance Nginx en foreground
CMD ["nginx", "-g", "daemon off;"]
