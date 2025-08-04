#!/bin/bash

# Couleurs
RED='\033[0;31m'
='\033[0;32m'
YELLOW='\033[1;33m'
='\033[0;34m'
NC='\033[0m'

echo -e "${}🧪 Tests TRICKY pour Philosophers${NC}"
echo "=================================="

# Compilation
make fclean > /dev/null 2>&1
make > /dev/null 2>&1

# Tests "tricky" spécifiques
echo -e "${YELLOW}📋 Test 1: Philosophe unique${NC}"
timeout 10 ./philo 1 800 200 200
echo ""

echo -e "${YELLOW}📋 Test 2: Temps très courts (mort probable)${NC}"
timeout 5 ./philo 5 200 200 200
echo ""

echo -e "${YELLOW}📋 Test 3: Temps très longs${NC}"
timeout 15 ./philo 5 8000 2000 2000 1
echo ""

echo -e "${YELLOW}📋 Test 4: Beaucoup de philosophes${NC}"
timeout 20 ./philo 10 800 200 200 2
echo ""

echo -e "${YELLOW}📋 Test 5: Cas limite - 2 philosophes${NC}"
timeout 15 ./philo 2 800 200 200 5
echo ""

echo -e "${YELLOW}📋 Test 6: Cas limite - 3 philosophes${NC}"
timeout 15 ./philo 3 310 200 100 1
echo ""

echo -e "${YELLOW}📋 Test 7: Temps égaux (deadlock possible)${NC}"
timeout 10 ./philo 5 800 200 200 3
echo ""

echo -e "${YELLOW}📋 Test 8: Sans limite de repas (timeout)${NC}"
timeout 5 ./philo 5 800 200 200
echo ""

echo -e "${}✅ Tests tricky terminés !${NC}"
