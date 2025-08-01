#!/bin/bash

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Variables
PROGRAM="./philo"
TIMEOUT=10  # Timeout en secondes pour les tests qui doivent se terminer

# Fonction pour afficher les résultats
print_result() {
	local test_name="$1"
	local exit_code="$2"
	local expected="$3"

	if [ "$exit_code" -eq "$expected" ]; then
		echo -e "${GREEN}✅ PASS${NC} - $test_name"
	else
		echo -e "${RED}❌ FAIL${NC} - $test_name (exit: $exit_code, expected: $expected)"
	fi
}

# Fonction pour tester avec timeout
test_with_timeout() {
	local test_name="$1"
	local args="$2"
	local expected_exit="$3"
	local timeout_duration="$4"

	echo -e "${BLUE}🧪 Testing: $test_name${NC}"
	echo "Command: $PROGRAM $args"

	if [ -n "$timeout_duration" ]; then
		timeout $timeout_duration $PROGRAM $args > /dev/null 2>&1
		exit_code=$?

		if [ $exit_code -eq 124 ]; then
			echo -e "${YELLOW}⏰ TIMEOUT${NC} - $test_name (timeout après ${timeout_duration}s)"
		else
			print_result "$test_name" $exit_code $expected_exit
		fi
	else
		$PROGRAM $args > /dev/null 2>&1
		print_result "$test_name" $? $expected_exit
	fi
	echo ""
}

# Nettoyage des anciens logs
echo -e "${BLUE}🧹 Nettoyage des anciens logs...${NC}"
rm -f *.log
echo ""

# Compilation
echo -e "${BLUE}🔨 Compilation...${NC}"
make fclean > /dev/null 2>&1
make > /dev/null 2>&1
if [ $? -eq 0 ]; then
	echo -e "${GREEN}✅ Compilation réussie${NC}"
else
	echo -e "${RED}❌ Erreur de compilation${NC}"
	exit 1
fi
echo ""

echo -e "${BLUE}🚀 Début des tests...${NC}"
echo "=================================="

# Tests d'arguments invalides (doivent échouer rapidement)
echo -e "${YELLOW}📋 Tests d'arguments invalides:${NC}"
test_with_timeout "Aucun argument" "" 1
test_with_timeout "1 argument" "5" 1
test_with_timeout "2 arguments" "5 800" 1
test_with_timeout "3 arguments" "5 800 200" 1
test_with_timeout "4 arguments" "5 800 200" 1
test_with_timeout "7 arguments" "5 800 200 200 3 4 5" 1

echo -e "${YELLOW}📋 Tests de valeurs invalides:${NC}"
test_with_timeout "0 philosophes" "0 800 200 200" 1
test_with_timeout "Temps négatif" "5 -800 200 200" 1
test_with_timeout "Temps zéro" "5 0 200 200" 1
test_with_timeout "Nombre de repas négatif" "5 800 200 200 -3" 1
test_with_timeout "Nombre de repas zéro" "5 800 200 200 0" 1

echo -e "${YELLOW}📋 Tests de format invalide:${NC}"
test_with_timeout "Lettres dans arguments" "5a 800 200 200" 1
test_with_timeout "Caractères spéciaux" "5@ 800 200 200" 1
test_with_timeout "Décimal" "5.5 800 200 200" 1

# Tests valides (doivent se terminer)
echo -e "${YELLOW}📋 Tests valides (avec timeout):${NC}"
test_with_timeout "5 philosophes, 3 repas" "5 800 200 200 3" 0 15
test_with_timeout "4 philosophes, 2 repas" "4 410 200 200 2" 0 15
test_with_timeout "3 philosophes, 1 repas" "3 310 200 100 1" 0 15
test_with_timeout "2 philosophes, 5 repas" "2 800 200 200 5" 0 15
test_with_timeout "1 philosophe, 1 repas" "1 800 200 200 1" 0 15

# Tests sans nombre de repas (doivent continuer indéfiniment)
echo -e "${YELLOW}📋 Tests sans limite de repas (timeout forcé):${NC}"
test_with_timeout "5 philosophes sans limite" "5 800 200 200" 0 5
test_with_timeout "4 philosophes sans limite" "4 410 200 200" 0 5
test_with_timeout "3 philosophes sans limite" "3 310 200 100" 0 5

# Tests de cas limites
echo -e "${YELLOW}📋 Tests de cas limites:${NC}"
test_with_timeout "Temps très courts" "5 100 50 50 2" 0 10
test_with_timeout "Temps très longs" "5 8000 2000 2000 1" 0 20
test_with_timeout "Beaucoup de philosophes" "10 800 200 200 2" 0 20

# Tests de mort (doivent se terminer par mort)
echo -e "${YELLOW}📋 Tests de mort (timeout court):${NC}"
test_with_timeout "Mort rapide" "5 200 200 200" 0 5
test_with_timeout "Mort avec repas" "5 200 200 200 10" 0 5

echo ""
echo -e "${BLUE}==================================${NC}"
echo -e "${BLUE}🎯 Tests terminés !${NC}"
echo ""

# Test avec Helgrind (optionnel)
echo -e "${BLUE}🔍 Test avec Helgrind (optionnel)...${NC}"
if command -v valgrind &> /dev/null; then
	echo "Test de race conditions avec Helgrind..."
	timeout 10 valgrind --tool=helgrind --log-file=helgrind.log ./philo 5 800 200 200 2 > /dev/null 2>&1
	if [ -f helgrind.log ]; then
		if grep -q "ERROR SUMMARY: 0 errors" helgrind.log; then
			echo -e "${GREEN}✅ Helgrind: Aucune erreur détectée${NC}"
		else
			echo -e "${RED}❌ Helgrind: Erreurs détectées${NC}"
			echo "Voir helgrind.log pour les détails"
		fi
	else
		echo -e "${YELLOW}⚠️  Helgrind: Timeout ou erreur${NC}"
	fi
else
	echo -e "${YELLOW}⚠️  Valgrind non installé${NC}"
fi

echo ""
echo -e "${GREEN}🎉 Script de test terminé !${NC}"
