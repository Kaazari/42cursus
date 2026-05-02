FROM debian:bullseye

# Install PHP-FPM + extensions WordPress
RUN apt-get update && apt-get install -y \
    php-fpm \
    php-mysql \
    php-mysqli \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Télécharge WP-CLI (outil ligne de commande WordPress)
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Crée dossier WordPress
RUN mkdir -p /var/www/html

# Copie script de setup
COPY conf/setup.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/setup.sh

# Expose port PHP-FPM
EXPOSE 9000

# Lance le script
CMD ["setup.sh"]
