FROM debian:bullseye

# Install MariaDB server
RUN apt-get update && apt-get install -y \
    mariadb-server \
    && rm -rf /var/lib/apt/lists/*

# Copie script d'initialisation
COPY conf/init.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/init.sh

# Expose port MySQL
EXPOSE 3306

# Lance MariaDB
CMD ["init.sh"]
