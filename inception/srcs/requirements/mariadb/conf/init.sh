#!/bin/bash

# Config MariaDB pour écouter sur toutes les IPs
sed -i 's/127.0.0.1/0.0.0.0/g' /etc/mysql/mariadb.conf.d/50-server.cnf

# Démarre MariaDB en background
service mariadb start

# Attend que MariaDB soit vraiment prêt
until mysqladmin ping --silent; do
    echo "Waiting for MariaDB..."
    sleep 2
done

# Crée la base de données
mysql -u root -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};"

# Crée utilisateur
mysql -u root -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"

# Donne tous les droits
mysql -u root -e "GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';"

# Change mot de passe root
mysql -u root -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('${MYSQL_ROOT_PASSWORD}');"

# Applique les changements
mysql -u root -e "FLUSH PRIVILEGES;"

# Stop MariaDB proprement
mysqladmin -u root -p${MYSQL_ROOT_PASSWORD} shutdown

# Lance MariaDB en foreground
exec mysqld --user=mysql --console
