#!/bin/bash

# Script de test pour vérifier les doubles impressions de mort
# Utilise timeout pour éviter les boucles infinies

echo "=== TEST DES DOUBLES IMPRESSIONS DE MORT ==="
echo ""

# Fonction pour tester et compter les morts
test_death_count() {
    local args="$1"
    local test_name="$2"
    local timeout_seconds="$3"

    echo "Test: $test_name"
    echo "Args: $args"
    echo "Timeout: ${timeout_seconds}s"

    # Exécuter avec timeout et capturer la sortie
    output=$(timeout $timeout_seconds ./philo $args 2>&1)
    exit_code=$?

    if [ $exit_code -eq 124 ]; then
        echo "❌ TIMEOUT - Programme arrêté après ${timeout_seconds}s"
        echo ""
        return
    fi

    # Compter les occurrences de "died"
    death_count=$(echo "$output" | grep -c "died")

    echo "Sortie:"
    echo "$output" | tail -20  # Afficher les 20 dernières lignes

    if [ $death_count -eq 1 ]; then
        echo "✅ SUCCESS: 1 mort détectée (correct)"
    elif [ $death_count -eq 0 ]; then
        echo "⚠️  WARNING: Aucune mort détectée"
    else
        echo "❌ ERROR: $death_count morts détectées (DOUBLE IMPRESSION!)"
    fi

    echo "----------------------------------------"
    echo ""
}

# Tests avec des cas où les philosophes meurent rapidement
echo "1. Test avec 1 philosophe (doit mourir rapidement)"
test_death_count "1 800 200 200" "1 philosophe" 5

echo "2. Test avec 2 philosophes (peuvent mourir)"
test_death_count "2 800 200 200" "2 philosophes" 5

echo "3. Test avec 5 philosophes (cas classique)"
test_death_count "5 800 200 200" "5 philosophes" 5

echo "4. Test avec 10 philosophes"
test_death_count "10 800 200 200" "10 philosophes" 5

echo "5. Test avec 50 philosophes"
test_death_count "50 800 200 200" "50 philosophes" 5

echo "6. Test avec 100 philosophes"
test_death_count "100 800 200 200" "100 philosophes" 5

echo "7. Test avec 200 philosophes (maximum)"
test_death_count "200 800 200 200" "200 philosophes" 5

echo "8. Test avec temps de mort très court"
test_death_count "5 100 200 200" "Temps de mort court" 5

echo "9. Test avec temps de mort extrêmement court"
test_death_count "5 50 200 200" "Temps de mort très court" 5

echo "10. Test avec temps de repas long"
test_death_count "5 800 500 200" "Temps de repas long" 5

echo "11. Test avec temps de sommeil long"
test_death_count "5 800 200 500" "Temps de sommeil long" 5

echo "12. Test avec nombre de repas obligatoire"
test_death_count "5 800 200 200 1" "Avec repas obligatoire" 5

echo "=== TESTS TERMINÉS ==="
