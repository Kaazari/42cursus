#!/bin/bash

# Script de test agressif pour forcer les morts et détecter les doubles impressions

echo "=== TEST AGRESSIF DES DOUBLES IMPRESSIONS DE MORT ==="
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

    echo "Sortie complète:"
    echo "$output"

    if [ $death_count -eq 1 ]; then
        echo "✅ SUCCESS: 1 mort détectée (correct)"
    elif [ $death_count -eq 0 ]; then
        echo "⚠️  WARNING: Aucune mort détectée"
    else
        echo "❌ ERROR: $death_count morts détectées (DOUBLE IMPRESSION!)"
        echo "Détail des morts:"
        echo "$output" | grep "died" -n
    fi

    echo "----------------------------------------"
    echo ""
}

# Tests avec des temps de mort très courts pour forcer les morts
echo "1. Test avec 1 philosophe - temps de mort très court"
test_death_count "1 10 200 200" "1 philosophe - mort rapide" 3

echo "2. Test avec 2 philosophes - temps de mort très court"
test_death_count "2 10 200 200" "2 philosophes - mort rapide" 3

echo "3. Test avec 5 philosophes - temps de mort très court"
test_death_count "5 10 200 200" "5 philosophes - mort rapide" 3

echo "4. Test avec 10 philosophes - temps de mort très court"
test_death_count "10 10 200 200" "10 philosophes - mort rapide" 3

echo "5. Test avec temps de repas très long"
test_death_count "5 50 1000 200" "Temps de repas très long" 3

echo "6. Test avec temps de sommeil très long"
test_death_count "5 50 200 1000" "Temps de sommeil très long" 3

echo "7. Test avec 1 philosophe - temps de mort extrême"
test_death_count "1 1 200 200" "1 philosophe - mort extrême" 2

echo "8. Test avec 2 philosophes - temps de mort extrême"
test_death_count "2 1 200 200" "2 philosophes - mort extrême" 2

echo "9. Test avec 5 philosophes - temps de mort extrême"
test_death_count "5 1 200 200" "5 philosophes - mort extrême" 2

echo "10. Test avec 10 philosophes - temps de mort extrême"
test_death_count "10 1 200 200" "10 philosophes - mort extrême" 2

echo "=== TESTS AGRESSIFS TERMINÉS ==="
